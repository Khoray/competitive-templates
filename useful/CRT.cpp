int exgcd(int &x, int &y, int a, int b) {
    if(!b) {
        x = 1;
        y = 0;
        return a;
    }
    int ret = exgcd(x, y, b, a % b);
    int t = x;
    x = y;
    y = t - a / b * y;
    return ret;
}


// lcm{p1,...,pn}<1e18, r<p<1e12
pair<int, int> excrt(vector<int> &p, vector<int> &r) {
    int x = r[1], lcm = p[1];
    int n = p.size() - 1;
    for(int i = 2; i <= n; i++) {
        // x' = x (mod lcm)
        // x' = r[i] (mod p[i])
        // a*lcm + b*p[i] = r[i] - x = c
        // at*lcm + bt*p[i] = (lcm, p[i])
        // a = k*at, k = c / gcd
        // x' = x + a*lcm (mod lcm'), lcm' = [lcm, p[i]]
        int at, bt;
        int gcd = exgcd(at, bt, lcm, p[i]);
        if((r[i] - x) % gcd != 0) {
            return {-1, -1};
        }
        int nlcm = lcm / __gcd(p[i], lcm) * p[i];
        x = ((__int128) x + (__int128) (r[i] - x) / gcd * at % nlcm * lcm % nlcm + nlcm) % nlcm;
        lcm = nlcm;
    }
    return {x, lcm};
}
