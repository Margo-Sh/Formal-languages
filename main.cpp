
#include "CYK.h"

int main() {
    int n, i;
    string s1, s2;

    cin >> n;
    vector<string> input(n);
    for (i = 0; i < n; i++)
    {
        cin >> s1 >> s2;
        input[i] = s1 + s2;
    }



    /*
    Grammar g(input);
    g.print();
    Chomsky gg(g);
    gg.convert_to_normal_form();
    //gg.print();
    */

    string w;
    cin >> w;

    if (CYK(w, input)) cout << "Yes";
    else cout << "No";


    return 0;
}
//epsilon?
/*
4
A a
B b
C B
S AB
 */
/*
5
S ABbA
B BB
B b
A C
C c
cbbbbbc
*/
/*
4
S ABc
B bbab
A a
C c
abbabc
 */
/*
7
S ABbA
S SS
B bb
B '
C c
A C
A a
cbacbbbc
 */
/*
7
S A
S SS
B bb
B `
S B`
A `
A a
`
 */
/*
7
S A
S SS
B bb
B `
S B``
A `
A B
bbbb
 */
/*
8
S `
S SS
B bb
B `
S B``
A `
B A
A a
bba
 */
/*
4
S AAA
A AAA
A a
A '
 */