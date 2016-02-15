
#ifndef PAGE_H_
#define PAGE_H_

#include <vector>

using namespace std;


class Page {

public:

    Page();
    ~Page();

    int GetPageSize();

    int GetAndPopFront();

    void Sort();

    bool Empty();

    void Clear();

    bool Push(int a);

    bool Full();


public:
    static const int PAGE_NUM = 1000;

private:
    vector<int> nums_;
};



#endif
