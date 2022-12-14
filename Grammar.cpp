//
// Created by memor on 05.12.2022.
//

#include "Grammar.h"

Grammar::Grammar(vector<string> s)
{
    left.resize(s.size());
    right.resize(s.size());
    int i, j;
    for(i = 0; i < s.size(); i++)
    {
        left[i] = int(s[i][0]);
        right[i].resize(s[i].size() - 1);
        for (j = 0; j < s[i].size() - 1; j++)
        {
            right[i][j] = int(s[i][j + 1]);
        }
    }
}

Grammar::Grammar(const string& ss)
{
    int i = 0, j, num_rules = 0;
    while (i < ss.size())
    {
        left.push_back(int(ss[i]));
        right.push_back(vector<int>(0));

        j = 2;
        while(j < ss.size() && ss[j] != '\n')
        {
            right[num_rules].push_back(int(ss[i+j]));
            ++j;
        }
        i += (j+1);
        ++num_rules;
    }
}

size_t Grammar::size()
{
    return left.size();
}

void Grammar::add_rule(int symbol, vector<int> right_side)
{
    left.push_back(symbol);
    right.push_back(right_side);
}

bool Grammar::check()
{
    if (left.size() != right.size()) return false;
    int i;
    for (i = 0; i < left.size(); i++)
    {
        if (left[i] > 122) return false;
    }
    return true;
}

void Grammar::print()
{
    int i, j;
    for (i = 0; i < left.size(); i++)
    {
        cout << endl << char(left[i]) << " -> ";
        for (j = 0; j < right[i].size(); j++)
        {
            cout << char(right[i][j]);
        }
    }
    cout << endl;
}

bool letter(int a, int eps)
{
    return a >= 97 && a <= 122 || a == eps;
}
