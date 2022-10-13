#include <iostream>
#include <typeinfo>
#include <vector>
#include <string.h>
#include <stack>
#include <queue>
#include <deque>

using std::cout; using std::cin; using std::endl;
using std::string; using std::vector; using std::stack; using std::queue; using std::deque;
using std::pair;
using std::make_pair; using std::swap;

string u;
//opeations: +, *, ^ -- Klini sign

/*
void get_input()
{
    cout << "Please input string u:" << endl;
    cin >> u;
    n = u.size();

    cout << "Please input regular expression using reverse Polish method." << endl;
    cout << "Only symbols +, *, ^, a, b, c allowed." << endl;

    char c;
    while (cin >> c)
    {
        if (c == '+' || c == '*' || c == '^' ) operations.push(c);
        else
        {
            if (c == 'a' || c == 'b' || c == 'c')
            {
                symbols.push(c);
            }
            else
            {
                cout << "Error: only symbols +, *, ^, a, b, c allowed.";
            }
        }
    }
}
*/


class Matrix
{
public:
    int N;
    vector<vector<bool>> table; //table[i][j] = true if u[i...j] fits regular expression
    //constructors:
    Matrix(int n): N(n), table(N, vector<bool>(N, false))
    {
    }

    Matrix(int n, char c): N(n), table(N, vector<bool>(N, false))
    {
        for (int i = 0; i < N; i++)
        {
            if (u[i] == c) table[i][i] = true;
        }
    }

    pair<int, int> get_max_true()
    {
        int len = 0;
        int beg = -1, en = -1;
        for (len = N-1; len > -1; len--) {
            for (int i = 0; i < N - len + 1; i++) {

                if (table[i][i + len - 1])
                {
                    beg = i;
                    en = i + len - 1;
                    break;
                }
            }
            if (beg != -1) break;
        }
        return pair<int, int>(beg, en);
    }
    //print_matrix
    void print_matrix()
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cout << table[i][j];
            }
            cout << endl;
        }
    }

    // operations:
    Matrix plus(Matrix& A, Matrix& B);
    Matrix mult(Matrix& A, Matrix& B);
    Matrix klini(Matrix A);
};


Matrix plus(Matrix& A, Matrix& B) // O(N^2)
{
    int n = A.N;
    Matrix C(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C.table[i][j] = (A.table[i][j] || B.table[i][j]);
        }
    }
    return C;
}

Matrix mult(Matrix& A, Matrix& B) // O(N^3)
{
    int n = A.N;
    Matrix C(n);
    //A, B: (u[i] ... u[j-1])(u[j] ... u[k]) i < j <= k
    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            for (int k = j; k < n; k++) {
                if (A.table[i][j-1] && B.table[j][k]) C.table[i][k] = true;
            }
        }
    }
    return C;
}

Matrix klini(Matrix A) // O(N^4)
{
    int n = A.N;
    Matrix C(n), C_deg(n);

    for (int k = 1; k < n+1; k++) // there is no point in considering klini sign beyond degree u.size()
    {
        C_deg = mult(C_deg, A);
        C = plus(C_deg, C);
    }

    return C;
}


class Solution
{
    int N;
    stack<Matrix> matrix_stack;
    //queue<char> operations;
public:

    Solution(int n): N(n)
    {

    }

    void print_solution()
    {

        stack<Matrix> copy_matrix_stack = matrix_stack;
        while(!copy_matrix_stack.empty())
        {
            (copy_matrix_stack.top()).print_matrix();
            cout << endl;
            copy_matrix_stack.pop();
        }

    }

    void add_operation(char oper)
    {

        Matrix A = matrix_stack.top();
        matrix_stack.pop();

        if (oper == '^')
        {
            matrix_stack.push(klini(A));
        }
        if (oper == '+')
        {
            Matrix B = matrix_stack.top();
            matrix_stack.pop();
            matrix_stack.push(plus(A, B));
        }
        if (oper == '*')
        {
            Matrix B = matrix_stack.top();
            matrix_stack.pop();
            matrix_stack.push(mult(B, A));
        }

    }

    pair<int, int> solve(string reg)
    {
        char c;
        for (int i =0; i < reg.size(); i++)
        {
            c = reg[i];
            if (c == '+' || c == '*' || c == '^' ){
                add_operation(c);
            }
            else
            {
                if (c == 'a' || c == 'b' || c == 'c')
                {
                    matrix_stack.push(Matrix(N, c));
                }
                else
                {
                    cout << "Error: only symbols +, *, ^, a, b, c allowed.";
                }
            }
        }

        return (matrix_stack.top()).get_max_true();
    }



};

string get_max_substring(string uu, string reg)
{
    u = uu;
    Solution sol(u.size());
    pair<int, int> interval = sol.solve(reg);
    string ans_str = "";
    for (int i = interval.first; i <= interval.second; i++) ans_str += u[i];
    return ans_str;
}


int main() {
    std:: ios_base::sync_with_stdio(false);
    std:: cin.tie(0);
    std:: cout.tie(0);

    //creating tests

    vector<vector<string>> tests;
    vector<string> test(3); // test[0] -- u, test[1] -- reg, test[2] --
    test[0] = "babcb";
    test[1] = "bc^+";
    test[2] = "b";
    tests.push_back(test);
    test[0] = "babc";
    test[1] = "abc*+"; // a + b* c
    test[2] = "bc";
    tests.push_back(test);
    test[0] = "cbbc";
    test[1] = "bbc+^+"; //b + (b + c)^
    test[2] = "cbbc";
    tests.push_back(test);
    test[0] = "bbcacbcb";
    test[1] = "bbc+^+"; //b + (b + c)^
    test[2] = "cbcb";
    tests.push_back(test);
    test[0] = "babccc";
    test[1] = "abc*+"; //(a + b)*b + c^
    test[2] = "ccc";
    tests.push_back(test);

    // running tests

    for (int i = 0; i < tests.size(); i++)
    {
        cout <<"solution for " << ' ' << tests[i][1] << ":" << endl;
//        u = tests[i][0];
//        Solution ss(tests[i][0].size(), tests[i][1]);
//        ss.print_solution();
        cout << get_max_substring(tests[i][0], tests[i][1])
        << ' ' << tests[i][2] << endl;
    }





    return 0;
}
