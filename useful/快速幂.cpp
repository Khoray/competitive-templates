int ksm(int a, int b, int MOD_KSM = mod) {
    int ret = 1;
    while(b) {
        if(b & 1) {
            ret = ret * a % MOD_KSM;
        }
        a = a * a % MOD_KSM;
        b >>= 1;
    }
    return ret;
}
