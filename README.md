# Formal-languages
Tasks for formal languages class

![image](https://user-images.githubusercontent.com/67891965/195706145-d8bdcc7a-00ab-4d2a-a57c-685efa2208c6.png)


My solution:

n -- length of u

f_L (i, j) = 0 or 1 depending on whether u[i...j-1] suits L or not.

f_(L1 + L2) can be calculated from f_L1 and f_L2 in O(n^2)

f_(L1 * L2) can be calculated from f_L1 and f_L2 in O(n^3)

f_(L1^*) can be calculated from f_L1 in O(n^4).

Таким образом, находим для альфа значение f за O(длина альфа * n^4)
