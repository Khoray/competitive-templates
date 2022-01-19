const int N = 1e7 + 5;
const int mod = 1e9 + 7;
int facinv[N], inv[N], fac[N];
void init_fac_inv() {
    facinv[0] = facinv[1] = inv[0] = inv[1] = fac[0] = fac[1] = 1;
    for(int i = 2; i < N; i++) {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
        facinv[i] = facinv[i - 1] * inv[i] % mod;
    }
}

int bio(int n, int k) {
    if(n < 0 || k < 0 || k > n) { return 0; }
    return fac[n] * facinv[n - k] % mod * facinv[k] % mod;
}

