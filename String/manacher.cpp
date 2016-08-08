// s = 12212321; str = $#1#2#2#1#2#3#2#1#;
// str: $  #  1  #  2  #  2  #  1  #  2  #  3  #  2  #  1  #
// p  :    1  2  1  2  5  2  1  4  1  2  1  6  1  2  1  2  1
// p.s. 可以看出，P[i]-1正好是原字符串中回文串的总长度
// p[i]记录以字符str[i]为中心的最长回文子串向左(右)扩张的长度(半径)(包括str[i])

char s[1100], str[3300];
int p[3300], pos, how;

void pre() {
    memset(str, 0, sizeof(str));
    str[0] = '$';
    int tot = 1;
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        str[tot++] = '#';
        str[tot++] = s[i];
    }
    str[tot] = '#';
}

void manacher() {
    pos = -1; how = 0;
    memset(p, 0, sizeof(p));
    int len = strlen(str);
    int mid = -1, mx = -1;
    for (int i = 0; i < len; i++) {
        int j = -1;
        if (i < mx) {
            j = 2*mid-i;
            p[i] = min(p[j], mx-i);
        }
        else p[i] = 1;
        while (i+p[i] < len && str[i+p[i]] == str[i-p[i]]) {
            p[i]++;
        }
        if(p[i]+i > mx) {
            mx = p[i]+i; mid = i;
        }
        if(p[i] > how) {
            how = p[i]; pos = i;
        }
    }
}
