
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "page.h"
#include "file_sort.h"

using namespace std;

FileSort::FileSort() {
}

FileSort::~FileSort() {
}


bool FileSort::Init(const char* fn1, const char* fn2) {
    FILE *f1 = fopen(fn1, "r");
    FILE *f2 = fopen(fn2, "r");

    File file("temp", "wb+");
    Page page;
    char buffer[20];
    int page_count = 1;

    while (NULL != fgets(buffer, 20, f1)) {
        int a = atoi(buffer);
        page.Push(a);
        if (page.Full()) {
            page.Sort();
            file.WritePage(page);
            page_count ++;
        }

    }

    while (NULL != fgets(buffer, 20, f2)) {
        int a = atoi(buffer);
        page.Push(a);
        if (page.Full()) {
            page.Sort();
            file.WritePage(page);
            page_count ++;
        }

    }

    if (!page.Empty()) {
        page.Sort();
        file.WritePage(page);
        page_count ++;
    }

    total_page_ = page_count - 1;

    cout << "total page : " << total_page_ << endl;

    fclose(f1);
    fclose(f2);
    file.Close();
}



bool FileSort::Sort() {
    int step = 1;

    while (step <= total_page_) {
        File file("temp", "rb",  total_page_);
        MergeSort(step, file);
        file.Close();
        rename("result", "temp");
        cout << "Finished One Round." << endl;
        step *= 2;
    }

    FormatResult();

    return true;

}



bool FileSort::MergeSort(int step, File &file) {
    File result("result", "wb+");

    Page page1;
    Page page2;
    Page page3;

    int f_index = 1;
    int s_index = f_index+step;


    while (f_index <= total_page_) {
        cout << ">>>>>>>>>>>" << f_index << "\t:\t" << s_index << ">>>>>>>>>>>>>>>>>>>" << endl;

        int i = 0, j = 0; // record nth page of index
        int a = -1, b = -1; // two road merge

        while (!page1.Empty() || 
               !page2.Empty() ||
               i < step       ||
               j < step) {

            if (page1.Empty()) {
                if (i < step) {
                    file.GetPage(f_index + i, page1);
                    i ++;
                }
            }
            if (page2.Empty()) {
                if (j < step) {
                    file.GetPage(s_index + j, page2);
                    j ++;
                }
            }

            if (a < 0) {
                a = page1.GetAndPopFront();
            }

            if (b < 0) {
                b = page2.GetAndPopFront();
            }

            if (a >= 0 && b >= 0) {
                if (a > b) {
                    page3.Push(b);
                    b = -1;
                } else {
                    page3.Push(a);
                    a = -1;
                }
            } else if (a >= 0 && b < 0) {
                page3.Push(a);
                a = -1;
            } else if (a < 0 && b >= 0) {
                page3.Push(b);
                b = -1;
            } else {
                if (!page3.Empty()) {
                    result.WritePage(page3);
                    break;
                }
            }

            if (page3.Full()) {
                result.WritePage(page3);
            }

            
        }

        if (a >= 0) {
            page3.Push(a);
        }

        if (b >= 0) {
            page3.Push(b);
        }

        if (!page3.Empty()) {
            result.WritePage(page3);
        }


        f_index += 2*step;
        s_index += 2*step;
    }

    result.Close();
}


void FileSort::FormatResult() {
    File file("temp", "rb",  total_page_);
    FILE *fp = fopen("result.txt", "w+");

    for (int i = 1; i <= total_page_; i ++) {
        Page page;
        file.GetPage(i, page);
        while (!page.Empty()) {
            char buffer[20];
            int a = page.GetAndPopFront();
            snprintf(buffer, sizeof(buffer), "%d\n", a);
            fputs(buffer, fp);
        }
    }

    fclose(fp);
    file.Close();
}














