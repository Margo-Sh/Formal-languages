//
// Created by memor on 05.12.2022.
//

#pragma once
#include "Grammar.h"
#include <set>
#include <stack>
using std::set; using std::stack;

class Chomsky
{
public:
    set<int> symbols;
    set<int> term; // symbols which convert to letters
    int start_symbol = 83; //'S'
    int epsilon = 96; //'''
    int max_symbols = 153; //max index of used symbol
    int letter_to_symbol = 30;

    vector<vector<vector<int>>> rules;

    Chomsky(Grammar g);

    //check if letter
    bool is_letter(int a);

    bool symbol_in_rule(int A, int B, int t);

    //adding symbols and rules

    void add_rule(int A, vector<int> rule_a);

    int add_new_symbol(vector<int> rule_a); //returns the index of the new symbol

    //removing symbols and rules
    void remove_symbol(int A);

    bool remove_rule(int A, int t); // true if symbol is also removed

    void remove_symbol_list(vector<bool>& remain);

    //check rule
    bool two_symbols_rule(int A, int t);

    bool term_rule(int A, int t);

    bool epsilon_rule(int A, int t);

    bool epsilon_symbol_rule(int A, int t);

    bool unit_rule(int A, int t);

    //check symbol
    bool term_symbol(int A);

    bool epsilon_gen_symbol(int A, vector<bool>& eps_symbol);


    //dfs variations
    //bool dfs_generates(int cur, vector<bool>& used, vector<bool>& remain);

    void dfs_unit(int cur, int root, vector<bool>& used);

    void dfs_epsilon(int cur, vector<bool>& used, vector<bool>& state);

    //steps of Chomsky convertion
    void remove_null();

    void remove_mixed();

    void remove_long();

    void remove_epsilon_generating_symbols();

    void remove_epsilon_rules();

    void remove_unit_rules();

    void convert_to_normal_form();

    void print();
};
