
#include "page.h"

#include <algorithm>

Page::Page(){
}


Page::~Page() {
}

int Page::GetPageSize() {
    return nums_.size();
}


int Page::GetAndPopFront() {
    if (Empty()) {
        return -1;
    }

    int begin = nums_[0];
    nums_.erase(nums_.begin());

    return begin;
}

void Page::Sort() {
    std::sort(nums_.begin(), nums_.end());
}

bool Page::Empty() {
    return nums_.empty();
}

void Page::Clear() {
    nums_.clear();
}

bool Page::Push(int a) {
    if (nums_.size() >= Page::PAGE_NUM) {
        return false;
    }

    nums_.push_back(a);

    return true;
}

bool Page::Full() {
    return nums_.size() >= Page::PAGE_NUM;
}
