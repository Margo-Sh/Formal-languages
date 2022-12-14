//
// Created by memor on 05.12.2022.
//
#include "CYK.h"

bool CYK(string& w, vector<string>& rules_string) {
    Grammar G(rules_string);
    Chomsky g(G);
    g.convert_to_normal_form();

    int n = w.size(), i, j, k, t, m, A, B, C;
    vector<vector<vector<bool>>> d(g.max_symbols+1, vector<vector<bool>>(n, vector<bool>(n, false)));

    for (auto A: g.term) {
        for (i = 0; i < n; i++) {
            for (t = 0; t < g.rules[A].size(); t++) {
                if (g.rules[A][t].size() != 1 || g.epsilon_rule(A, t)) continue;
                if (g.rules[A][t][0] == w[i])
                {
                    d[A][i][i] = true;
                }
            }
        }
    }

    for (m = 1; m < n; m++) {
        for (i = 0; i < n - m; i++) {
            j = i + m;

            for (auto A: g.symbols) {
                for (t = 0; t < g.rules[A].size(); t++) {
                    if (g.two_symbols_rule(A, t)) {
                        B = g.rules[A][t][0];
                        C = g.rules[A][t][1];
                        for (k = i; k < j; k++) {
                            if (d[A][i][j]) break;

                            if (d[B][i][k] && d[C][k + 1][j]) d[A][i][j] = true;

                        }
                    }
                }

            }

        }

    }

    return d[g.start_symbol][0][n - 1];
}
