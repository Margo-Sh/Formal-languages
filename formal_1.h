
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include<algorithm>

using std::cout; using std::cin; using std::endl;
using std::string; using std::vector; using std::stack; using std::queue; using std::deque;
using std::pair;
using std::make_pair; using std::swap;

string u;
//opeations: +, ., * -- Klini sign

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
        if (c == '+' || c == '*' || c == '.' ) operations.push(c);
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
    int N; //length of string
    vector<vector<bool>> table; //table[i][j] = true if u[i...j-1] fits regular expression
    //constructors:
    Matrix(int n): N(n), table(N, vector<bool>(N + 1, false))
    {

    }

    Matrix(int n, char c): N(n), table(N, vector<bool>(N + 1, false))
    {
        for (int i = 0; i < N; i++)
        {
            if (u[i] == c) table[i][i+1] = true;
        }
    }


    pair<int, int> get_max_true()
    {
        int len = 0;
        int beg = -1, en = -1;
        for (len = N; len > -1; len--) {
            for (int i = 0; i < N - len + 1; i++) {

                if (table[i][i + len])
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

    void print_matrix()
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N + 1; j++)
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
        for (int j = 0; j < n + 1; j++)
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
    //A, B: (u[i] ... u[j-1])(u[j] ... u[k-1]) i <= j <= k
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            for (int k = j; k < n + 1; k++) {
                if (A.table[i][j] && B.table[j][k]) C.table[i][k] = true;
            }
        }
    }
    return C;
}

Matrix klini(Matrix A) // O(N^4)
{
    int n = A.N;
    Matrix C(n), C_deg(n);
    for (int i = 0; i < n; i++)
    {
        C.table[i][i] = true; // epsilon
        C_deg.table[i][i] = true; // epsilon
    }

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

    void print_top_matrix()
    {
        (matrix_stack.top()).print_matrix();
    }

    void add_operation(char oper)
    {

        Matrix A = matrix_stack.top();
        matrix_stack.pop();

        if (oper == '*')
        {
            matrix_stack.push(klini(A));
        }
        if (oper == '+')
        {
            Matrix B = matrix_stack.top();
            matrix_stack.pop();
            matrix_stack.push(plus(A, B));
        }
        if (oper == '.')
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
            if (c == '+' || c == '*' || c == '.' ){
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
                    cout << "Error: only symbols +, *, ., a, b, c allowed. bad symbol: " << c - 0 << endl;
                }
            }
            // cout << "symbol " << c << ": " << endl;
            // print_top_matrix();
        }
        // cout << "matrixes left: " << matrix_stack.size() << endl;
        return (matrix_stack.top()).get_max_true();
    }



};

int get_max_substring(string reg, string uu)
{
    u = uu;
    reg.erase(std::remove_if(reg.begin(), reg.end(), ::isspace), reg.end());
    Solution sol(u.size());
    pair<int, int> interval = sol.solve(reg);
    return interval.second + 1 - interval.first;
}


