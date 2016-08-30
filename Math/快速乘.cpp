// a*b%mod  O(1)
LL mult_mod(LL a, LL b, LL mod) {
    return (a*b-(LL)(a/(long double)mod*b+1e-3)*mod+mod)%mod;
}
