#pragma once

#include <climits>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

template <class ForwardIt>
void PrintRange(ForwardIt first, ForwardIt last, std::string delim = "->") {
    if (first == last) {
        return;
    }
    --last;
    for (; first != last; ++first) {
        std::cout << *first << delim;
    }
    std::cout << *first;
}

struct Road {
    std::pair<int, int> buildings;
    int time;
    Road(std::pair<int, int> bs, int t) : buildings(bs), time(t) {}
};

void CanCatch(int n, std::vector<Road> roads, int s, int d, int x, int y, int l, int printPath);