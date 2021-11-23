#include<bits/stdc++.h>
using namespace std;
#define double long double
const double PI = acos(-1);
int mod;
const int N = 5e5 + 5;
#define int long long
int pos[N];
struct Complex {
    double x, y; //实部和虚部 x+yi
    Complex(double _x = 0.0, double _y = 0.0) {
        x = _x;
        y = _y;
    }
    Complex operator - (const Complex &b)const {
        return Complex(x - b.x, y - b.y);
    }
    Complex operator + (const Complex &b)const {
        return Complex(x + b.x, y + b.y);
    }
    Complex operator * (const Complex &b)const {
        return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
    }
    Complex conj() {
        return Complex(x, -y);
    }
};

void change(Complex y[], int len) {
    int i, j, k;
    for(i = 1, j = len / 2; i < len - 1; i++) {
        if(i < j) {
            swap(y[i], y[j]);
        }
        k = len / 2;
        while(j >= k) {
            j -= k;
            k /= 2;
        }
        if(j < k) {
            j += k;
        }
    }
}

void fft(Complex y[], int len, int on) {
    change(y, len);
    Complex u,t;
    for(int h = 1; h < len; h <<= 1) {
        for(int j = 0; j < len; j += h<<1) {
            for(int k = j; k < j + h; k++) {
                Complex w(cos(PI / h * (k-j)), on * sin(PI / h * (k-j))); // 这里ON一定要放外面 加速 50+%
                u = y[k];
                t = w * y[k + h];
                y[k] = u + t;
                y[k + h] = u - t;
            }
        }
    }
    if(on == -1)
        for(int i = 0; i < len; i++) {
            y[i].x /= len;
            y[i].y /= len;
        }
}
//calc g'(x)=c(x) + d(x)i f'(x)=a(x) + b(x)i
// g(x)=Pd(x)+c(x)  f(x)=Pb(x)+a(x)
// ans = P^2db + ca + P(ad + cb)
//     = (Pd + c)a + (Pd + c)bP
//     = (g*a).y * P + (g*b).x * P + (g*a).x + P^2 * (g*b).y
Complex q[N], a[N], b[N], f[N], g[N];
void any_mod_mul(int len, int f[], int g[], int h[]) {
    const int P = 1 << 15;
    for(int i = 0; i < len; i++) {
        int tmpf = f[i], tmpg = g[i];
        ::f[i] = {tmpf & (P - 1), tmpf >> 15};
        ::g[i] = {tmpg & (P - 1), tmpg >> 15};
    }
    fft(::f, len, 1);
    fft(::g, len, 1);
    for(int i = 0; i < len; i++) {

        q[i] = ::f[(len - i) & (len - 1)].conj();
        a[i] = (q[i] + ::f[i]) * Complex(0.5, 0);
        b[i] = (::f[i] - q[i]) * Complex(0, -0.5);
        a[i] = ::g[i] * a[i];
        b[i] = ::g[i] * b[i];
    }
    
    fft(a, len, -1);
    fft(b, len, -1);
    for(int i = 0; i < len; i++) {
        h[i] = ((((long long)(a[i].y + 0.5) % mod << 15) % mod
                 + (long long)(a[i].x + 0.5) % mod) % mod
                 + ((long long)(b[i].x + 0.5) % mod << 15) % mod) % mod
                 + ((long long)(b[i].y + 0.5) % mod << 30) % mod;
        h[i] = (h[i] % mod + mod) % mod;
    }
}


int a1[N];
int a2[N];
int ans[N];
int read() {
    int ret = 0, fl = 1;
    char ch = getchar();
    while(!isdigit(ch)) {
        (ch == '-') &&(fl = -1), ch = getchar();
    }
    while(isdigit(ch)) {
        ret = ret * 10 + ch - '0', ch = getchar();
    }
    return ret * fl;
}
signed main() {
    #ifdef _KHORAY
        freopen("test.in","r",stdin);
        freopen("testout.out","w",stdout);
    #endif
    int n, m;
    cin >> n >> m >> mod;
    n++, m++;
    for(int i = 0; i < n; i++) {
        a1[i] = read();
    }
    for(int i = 0; i < m; i++) {
        a2[i] = read();
    }
    int lim = 1;
    // int mx = 2 * max(n,m);
    while(lim < (n+m)) {
        lim <<= 1;
    }
    // mul
    any_mod_mul(lim, a1, a2, ans);
    for(int i = 0; i < n + m - 1; i++) {
        cout << ans[i] << ' ';
    }
    return 0;
}