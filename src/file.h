
#ifndef FILE_H_
#define FILE_H_

#include <stdio.h>

#include "page.h"

class File {

public:
    File(char* file_name, char* mode, int page_num = 0);
    ~File();

    bool GetPage(int index, Page &page);

    void WritePage(Page& page);

    void Close();

private:
    char *file_name_;
    FILE *f_;
    int page_num_;
};



#endif
