/*
hash�����Ľ������һ��׼ȷ,hash��ֵ���ܻ��г�ͻ���½������(�������������Ի�hash������).
����һ����ַ���,���hash����׼ȷ�Ժܸ�. �����е���Ŀ����⹹�����ʹhash����ʧЧ���ַ���,
���ۻ�ʲô����hash����������,��ʱ����Ҫ��hash���������޸�,����ʹ����Ȼ����ķ�ʽ����hashֵ,
����ѡȡ����������,����һ���ַ�����¼����hashֵ������������mod.
�����ַ������Թ�������ȫ����hash��������
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
