
#include <iostream>
#include "file.h"

using namespace std;

File::File(char* file_name, char* mode, int page_num) {
    file_name_ = file_name;
    f_ = fopen(file_name, mode);
    if (f_ == NULL) {
        cout << "Error to open file." << endl;
    }

    page_num_ = page_num;
}

File::~File() {
}

bool File::GetPage(int index, Page &page) {
    if (index > page_num_) {
        return false;
    }

    fseek(f_, (index-1)*Page::PAGE_NUM*sizeof(int), SEEK_SET);
    int buffer[Page::PAGE_NUM];
    int result = fread(buffer, sizeof(int), Page::PAGE_NUM, f_);
    for (int i = 0; i < result; i ++) {
        page.Push((int)buffer[i]);
    }

    return true;
}

void File::WritePage(Page &page) {
    int buffer[Page::PAGE_NUM];
    int count = 0;
    int tmp = page.GetAndPopFront();
    while (tmp != -1) {
        buffer[count] = tmp;
        count ++;
        tmp = page.GetAndPopFront();
    }

   fwrite(buffer, sizeof(int), count, f_);
}

void File::Close() {
    fclose(f_);
}


