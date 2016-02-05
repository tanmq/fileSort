
#ifndef FILE_SORT_H_
#define FILE_SORT_H_

#include "file.h"

class FileSort {
public:
    FileSort();
    ~FileSort();

    bool Init(const char* f1, const char* f2);

    bool Sort();

private:
    bool MergeSort(int step, File &file);

    void FormatResult();

private:
    int total_page_;

};



#endif
