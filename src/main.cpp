
#include <iostream>
#include <cstdlib>
#include "file_sort.h"

using namespace std;


int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "ErrorL parameter wrong." << endl;
        exit(-1);
    }

    FileSort file_sort;

    file_sort.Init("1.txt", "2.txt");
    cout << "Finished Init." << endl;

    file_sort.Sort();

    return 0;
}
