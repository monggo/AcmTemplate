/*
hash函数的结果并不一定准确,hash的值可能会有冲突导致结果错误(但不常遇到可以换hash数即可).
对于一般的字符串,这个hash函数准确性很高. 但是有的题目会刻意构造可以使hash函数失效的字符串,
无论换什么样的hash数都过不了,这时就需要对hash函数进行修改,不能使用自然溢出的方式储存hash值,
可以选取两个大质数,对用一个字符串记录它的hash值和这两个数的mod.
用这种方法可以过掉几乎全部卡hash函数的题
*/

ull long long mod1=1000000007, mod2=1000000003;
ull base = 123;
ull xp[maxn], Hash[maxn];
void init() {
	xp[0] = 1;
	for (int i = 1; i < maxn; i++)
		xp[i] = xp[i-1]*base;
}
ull get_Hash(int i, int L) {
	return Hash[i]-Hash[i+L]*xp[L];
}
/*
scanf("%s", str);
int n = strlen(str);
Hash[n] = 0;
for (int i = n-1; i >= 0; i--) {
	Hash[i] = Hash[i+1]*base+(str[i]-'a'+1);
}
*/
