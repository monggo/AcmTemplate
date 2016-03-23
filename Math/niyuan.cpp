逆元:(b/a)(mod m) = (b*x)(mod m)
x表示a的逆元，并且a*x=1(mod m) 注意:只有当a与n互质的时候才存在逆元
求逆元方法：
1.费马小定理
因为a^phi(m)＝1(mod m)，所以逆元为a^(phi(m)-1)(mod m)
特别地，如果m为质数，逆元为a^(m-2)(mod m)

2.扩展欧几里德
 //返回d=gcd(a,b);和对应于等式ax+by=d中的x,y
long long extend_gcd(long long a, long long b, long long &x, long long &y) {
    if (a==0 && b==0) return -1;//无最大公约数
    if (b == 0) { x = 1; y = 0; return a; }
    long long d = extend_gcd(b, a%b , y, x);
    y -= a/b*x;
    return d;
}
//求逆元素
//ax = 1(mod n)
long long mod_reverse(long long a, long long n) {
    long long x, y;
    long long d = extend_gcd(a, n, x, y);
    if (d == 1) return (x%n+n)%n;
    else return -1;
}

3.O(n)时间求逆的代码(MOD必须是素数)
long long inv[MAXN];
inv[1] = 1;
for (long long i = 2; i < MAXN; i++) {
	inv[i] = inv[MOD%i]*(MOD-MOD/i)%MOD;
}

4.有一种通用的求逆元方法，适合所有情况。公式如下:
(b/a)%m = b%(m*a)/a