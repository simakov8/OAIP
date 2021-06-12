#include <iostream>
#include <algorithm>
#include <list>
#include <memory>
#include <random>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <list>
#include <random>
#include <cassert>
#include "list.h"

using StudentList = BidirectionalList<int>;

bool equal(std::list<int> valid, StudentList test) {
    std::vector<int> arr1;
    std::vector<int> arr2;
    for (auto item : valid) {
        arr1.push_back(item);
    }
    for (auto item : test) {
        arr2.push_back(item);
    }
    return arr1 == arr2;
}

int main() {

    StudentList arr = {1, 2, 3};

    //arr.pop_back();
    //arr.pop_back();
    //arr.pop_back();

    //StudentList arr;
    //arr.push_back(1);
    //arr.push_back(2);
    //arr.push_back(3);

    assert(3 == *(--arr.end()));
    assert(3 == *(--arr.end()));
    assert(1 == *arr.begin());
    assert(1 == *arr.begin());

    auto carr = arr;
    *(++carr.begin()) = 100500;

    for (auto item : arr) {
        std::cerr << item << ' '; // 1 2 3
    }
    std::cerr << '\n';
    for (auto item : carr) {
        std::cerr << item << ' '; // 1 100500 3
    }

    std::list<int> valid = {1, 2, 3};

    std::mt19937 gen(1488);
    std::uniform_int_distribution<int> dist(-1000, 1000);

    assert(equal(valid, arr));

    for (int i = 0; i < 1024; i++) {
        int value = dist(gen);
        auto key = gen();
        if (key % 16 < 4) {
            valid.push_back(value);
            arr.push_back(value);
        } else if (key % 16 < 8) {
            valid.push_front(value);
            arr.push_front(value);
        } else if (key % 16 < 12) {
            valid.pop_front();
            arr.pop_front();
        } else {
            valid.pop_back();
            arr.pop_back();
        }
        assert(equal(valid, arr));
    }

    return 0;
}
