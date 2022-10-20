#include "formal_1.h"

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