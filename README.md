# Formal-languages
Tasks for formal languages class

My solution:
Мое решение:

n -- length of u

f_L (i, j) = 0 or 1 depending on whether u[i...j-1] suits L or not.

f_(L1 + L2) can be calculated from f_L1 and f_L2 in O(n^2)

f_(L1 * L2) can be calculated from f_L1 and f_L2 in O(n^3)

f_(L1^*) can be calculated from f_L1 in O(n^4).

Таким образом, находим для альфа значение f за O(длина альфа * n^3)
