树状数组在区间求和问题上有大用，其三种复杂度都比线段树要低很多……
有关区间求和的问题主要有以下三个模型
（以下设A[1..N]为一个长为N的序列，初始值为全0）：

（1）“改点求段”型，即对于序列A有以下操作：
【1】修改操作：将A[x]的值加上c；
【2】求和操作：求此时A[l..r]的和。
void ADD(int x, int c) {
     for (int i = x; i <= n; i+=i&(-i)) a[i] += c;
}
int SUM(int x) {
    int s = 0;
    for (int i = x; i > 0; i-=i&(-i)) s += a[i];
    return s;
}
操作【1】：ADD(x, c);
操作【2】：SUM(r)-SUM(l-1)。


（2）“改段求点”型，即对于序列A有以下操作：
【1】修改操作：将A[l..r]之间的全部元素值加上c；
【2】求和操作：求此时A[x]的值。
void ADD(int x, int c)　{
     for (int i　=　x; i　>　0; i-=i&(-i)) b[i] += c;
}
int SUM(int x)　{
    int s = 0;
    for (int i　=　x; i　<=　n; i+=i&(-i)) s += b[i];
    return s;
}
操作【1】：ADD(l-1, -c); ADD(r, c);
操作【2】：SUM(x)。


（3）“改段求段”型，即对于序列A有以下操作：
【1】修改操作：将A[l..r]之间的全部元素值加上c；
【2】求和操作：求此时A[l..r]的和。
void ADD_B(int x, int c) {
     for (int i = x; i > 0; i-=i&(-i)) B[i] += c;
}
void ADD_C(int x, int c) {
     for (int i = x; i <= n; i+=i&(-i)) C[i] += x * c;
}
int SUM_B(int x) {
    int s = 0;
    for (int i = x; i <= n; i+=i&(-i)) s += B[i];
    return s;
}
int SUM_C(int x) {
    int s = 0;
    for (int i = x; i > 0; i-=i&(-i)) s += C[i];
    return s;
}
int SUM(int x) {
    if (x) return SUM_B(x)*x + SUM_C(x-1); 
    else return 0;
}
操作【1】：
ADD_B(r, c); ADD_C(r, c);
if (l > 1) {　ADD_B(l-1, -c); ADD_C(l-1, -c);　}
操作【2】：SUM(r) - SUM(l-1)。