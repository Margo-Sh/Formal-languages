//
// Created by memor on 05.12.2022.
//

#include "Chomsky.h"

bool Chomsky::symbol_in_rule(int A, int B, int t)
{
    for (int i = 0; i < rules[B][t].size(); i++)
    {
        if (rules[B][t][i] == A) return true;
    }
    return false;
}

bool Chomsky::is_letter(int a)
{
    return letter(a, epsilon);
}

bool Chomsky::term_rule(int A, int t)
{
    for (int i = 0; i < rules[A][t].size(); i++)
    {
        if (!is_letter(rules[A][t][i])) return false;
    }
    return true;
}

bool Chomsky::epsilon_rule(int A, int t)
{
    return rules[A][t].size() == 1 && rules[A][t][0] == epsilon;
}

bool Chomsky::term_symbol(int A)
{
    for (int t = 0; t < rules[A].size(); t++)
    {
        if (term_rule(A, t)) return true;
    }
    return false;
}

bool Chomsky::epsilon_gen_symbol(int A, vector<bool>& eps_symbol)
{
    if (eps_symbol[A]) return true;
    int i;
    bool all_eps_gen;
    for (int t = 0; t < rules[A].size(); t++)
    {
        if (epsilon_rule(A, t)){
            eps_symbol[A] = true;
            return true;
        }
        all_eps_gen = true;
        for (i = 0; i < rules[A][t].size(); i++)
        {
            if (is_letter(rules[A][t][i]) || !eps_symbol[rules[A][t][i]])
            {
                all_eps_gen = false;
                break;
            }
        }
        if (all_eps_gen){
            eps_symbol[A] = true;
            return true;
        }
    }
    return false;
}

void Chomsky::add_rule(int A, vector<int> rule_a)
{
    if (A > max_symbols){
        max_symbols = A;
        rules.resize(max_symbols +2);
    }
    if (!rule_a.empty()) rules[A].push_back(rule_a);

    if (term.find(A) == term.end() && term_rule(A, rules[A].size()-1)) term.insert(A);
}

int Chomsky::add_new_symbol(vector<int> rule_a)
{
    max_symbols++;
    if (max_symbols > rules.size()-1) rules.resize(max_symbols * 2);
    rules[max_symbols].push_back(rule_a);
    symbols.insert(max_symbols);
    if (term_rule(max_symbols, 0)) term.insert(max_symbols);
    return max_symbols;
}

bool Chomsky::remove_rule(int A, int t)
{
    if (rules[A].size() == 1 && t == 0){
        if (term.find(A) != term.end()) term.erase(A);
        remove_symbol(A);
        return true;
    }

    rules[A].erase(rules[A].begin() + t);

    if (term.find(A) != term.end() && !term_symbol(A)) term.erase(A);
}

void Chomsky::remove_symbol(int A)
{
    if (A == max_symbols) --max_symbols;
    if (A <= max_symbols)
    {
        rules[A] = vector<vector<int>>(0);
        term.erase(A);
    }
}

void Chomsky::remove_symbol_list(vector<bool>& remain)
{
    set<int>::iterator i=symbols.begin();
    while (i!= symbols.end())
    {
        i = (!remain[*i]) ? symbols.erase(i) : std::next(i);
    }
    /*
    for (set<int>::iterator i=symbols.begin(), e=symbols.end(); i != e; )
    {
        if (!remain[*i])
        {
            remove_symbol(*i);
            i = symbols.erase(i);
        }
        else
        {
            i++;
        }
    }
    */
}

Chomsky::Chomsky(Grammar g)
{
    start_symbol = g.start_symbol;
    epsilon = g.epsilon; //'''
    rules.resize(max_symbols+1);
    int i, j;
    for (i = 0; i < g.size(); i++)
    {
        symbols.insert(g.left[i]);
        add_rule(g.left[i], g.right[i]);
    }
}

bool Chomsky::two_symbols_rule(int A, int t)
{
    return rules[A][t].size() == 2 && !is_letter(rules[A][t][0]) && !is_letter(rules[A][t][1]);
}

bool Chomsky::epsilon_symbol_rule(int A, int t){
    for (int i =0; i < rules[A][t].size(); i++){
        if (is_letter(rules[A][t][i]) ) continue;
        if (rules[A][t][i] == (epsilon + letter_to_symbol) || symbols.find(rules[A][t][i]) == symbols.end()) return true;
    }
    return false;
}

bool Chomsky::unit_rule(int A, int t)
{
    return rules[A][t].size() == 1 && !is_letter(rules[A][t][0]);
}
/*
bool Chomsky::dfs_generates(int cur, vector<bool>& used, vector<bool>& remain)
{
    used[cur] = true;
    if (!remain[cur] && term.find(cur) != term.end()){
        remain[cur] = true;
        //return;
    }

    int t, i;
    for(t = 0; t < rules[cur].size(); t++)
    {
        for (i = 0; i < rules[cur][t].size(); i++)
        {
            if (!)
        }
            if (!used[rules[cur][t][0]]) dfs_unit(rules[cur][t][0], root, used);


    }

}
*/

void Chomsky::remove_null()
{
    //delete unreachable symbols
    vector<bool> remain(max_symbols +1, false);

    int v, i, t;
    stack<int> visit;
    visit.push(start_symbol);
    while(!visit.empty())
    {
        v = visit.top();
        visit.pop();
        if (!remain[v])
        {
            remain[v] = true;
            for (t = 0; t < rules[v].size(); t++) {
                for (i = 0; i < rules[v][t].size(); i++) {
                    if (!is_letter(rules[v][t][i])){
                        if (!remain[rules[v][t][i]]) visit.push(rules[v][t][i]);
                    }

                }
            }
        }
    }

    remove_symbol_list(remain);

    //delete non-generating symbols
    remain.assign(max_symbols +1, false);

    for (auto A: term)
    {
        remain[A] =true;
    }

    bool change = true, state;

    while (change)
    {
        change = false;
        for (auto A: symbols)
        {
            if (remain[A]) continue;
            for (t = 0; t < rules[A].size(); t++)
            {
                state = true;
                for (i = 0; i < rules[A][t].size(); i++)
                {
                    if (!is_letter(rules[A][t][i]) && !remain[rules[A][t][i]])
                    {
                        state = false;
                        break;
                    }
                }
                if (state){
                    change = true;
                    remain[A] =true;
                }

                if (remain[A]) break;
            }
        }
    }

    remove_symbol_list(remain);

}

void Chomsky::remove_mixed() //'a' -> 'a' + letter_to_symbol
{
    int t, i;
    set<int> all_letters;
    for (auto A : symbols)
    {
        for (t = 0; t < rules[A].size(); t++) {
            for (i = 0; i < rules[A][t].size(); i++) {
                if (is_letter(rules[A][t][i])){
                    all_letters.insert(rules[A][t][i]);
                    rules[A][t][i] += letter_to_symbol;
                }
            }
        }
    }
    term.clear();
    for (auto a: all_letters)
    {
        add_rule(a+ letter_to_symbol, {a});
        term.insert(a + letter_to_symbol);
        symbols.insert(a + letter_to_symbol);
    }

}

void Chomsky::remove_long()
{
    int i, j, t, sz, cur;
    for (auto A : symbols)
    {
        sz = rules[A].size();
        for (t = 0; t < sz; t++) {
            if (rules[A][t].size() < 3) continue; // A BCD

            cur = add_new_symbol({rules[A][t][rules[A][t].size() - 2], rules[A][t][rules[A][t].size() - 1]});

            for (i = rules[A][t].size() - 3; i > 0; i--)
            {
                cur = add_new_symbol({rules[A][t][i], cur});
            }
            rules[A][t].resize(2);
            rules[A][t][1] = cur;
        }

    }
}

void Chomsky::remove_epsilon_rules(){
    int t;

    bool removed_symbol;
    set<int>::iterator A = symbols.begin();
    while (A != symbols.end())
    {
        t = 0;
        removed_symbol = false;
        while(t < rules[*A].size())
        {
            if (epsilon_rule(*A, t) || epsilon_symbol_rule(*A, t))
            {
                if (rules[*A].size() == 1)
                {
                    if (term.find(*A) != term.end()) term.erase(*A);
                    A = symbols.erase(A);
                    removed_symbol = true;
                    break;
                }
                else
                {
                    remove_rule(*A, t);
                }
            }
            else ++t;
        }
        if (!removed_symbol) A = std::next(A);
    }
}

void Chomsky::remove_epsilon_generating_symbols()
{
    int t, sz, B, C;

    vector<bool> eps_symbol(max_symbols+1, false);

    bool change = true;
    while (change)
    {
        change = false;
        for (auto A: symbols)
        {
            if (!eps_symbol[A]){
                if (epsilon_gen_symbol(A, eps_symbol)) change = true;
            }
        }
    }


    for (auto A: symbols)
    {
        sz = rules[A].size();
        t = 0;

        while(t < sz)
        {
            if (two_symbols_rule(A, t))
            {
                B = rules[A][t][0];
                C = rules[A][t][1];

                if (eps_symbol[B]){
                    add_rule(A, {C});
                }
                if (eps_symbol[C]) {
                    add_rule(A, {B});
                }
            }
            ++t;
        }
    }

    //delete epsilon rules
    remove_epsilon_rules();

    // add S -> epsilon if needed
    if (eps_symbol[start_symbol]) {
        add_rule(start_symbol, {epsilon});
        symbols.insert(start_symbol);
        term.insert(start_symbol);
    }

}


void Chomsky::dfs_unit(int cur, int root, vector<bool>& used)
{
    int t;
    used[cur] = true;
    int sz = rules[cur].size();
    for(t = 0; t < sz; t++)
    {
        if (unit_rule(cur, t))
        {
            if (!used[rules[cur][t][0]]) dfs_unit(rules[cur][t][0], root, used);
        }
        else
        {
            if (cur != root) add_rule(root, rules[cur][t]);
        }
    }
}

void Chomsky::remove_unit_rules()
{
    int i, j, t, B;
    vector<bool> used(max_symbols+1);

    for (auto A: symbols)
    {
        used.assign(max_symbols+1, false);
        dfs_unit(A, A, used);
    }

    for (auto A: symbols)
    {
        t = 0;
        while(t < rules[A].size())
        {
            if (!unit_rule(A, t)){
                ++t;
                continue;
            }
            remove_rule(A, t);
        }
    }

}


void Chomsky::print()
{
    int i, t;
    cout << endl;
    for (auto A : symbols) {
        for (t = 0; t < rules[A].size(); t++) {
            cout << A;
            for (i = 0; i < rules[A][t].size(); i++) {
                if (is_letter(rules[A][t][i])) cout << " " << char(rules[A][t][i]);
                else cout << " " << rules[A][t][i];
            }
            cout << endl;
        }
    }
    cout << "term: ";
    for (auto A : term) cout << A << ' ';
    cout << endl;
}

void Chomsky::convert_to_normal_form()
{
    remove_null();

    remove_mixed();

    remove_long();

    remove_epsilon_generating_symbols();

    remove_unit_rules();

}