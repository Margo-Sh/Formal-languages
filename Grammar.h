//
// Created by memor on 05.12.2022.
//
#pragma once
#include <iostream>
#include <vector>

using std::vector; using std::min;
using std::max; using std::swap;
using std::make_pair; using std::pair;
using std::string;
using std::cin; using std::cout; using std::endl;


// terminal symbols -- non-capital letters which have ascii index 97-122
class Grammar {
public:
    explicit Grammar(vector<string> s); // A asB

    vector<int> left; //left side of rules
    vector<vector<int>> right; //right side of rules
    int start_symbol = 83; //'S'
    int epsilon = 96; //'`'

    Grammar(const string& s);

    size_t size();

    void add_rule(int symbol, vector<int> right_side);

    bool check();

    void print();

};

bool letter(int a, int eps);

