#include<bits/stdc++.h>
using namespace std;
#define double long double
#define int long long
const int mod = 1e9+7;
const double PI = acosl(-1);

void change(int y[], int len) {
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

int qpow(int a, int b = mod - 2) {
    int ret = 1;
    while(b) {
        if(b&1) ret=ret*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ret;
}

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
const int N=5e5+5;
Complex Wn[N];

void fft(Complex y[], int len, int on) {
    for(int i=1;i<len;i<<=1)
		for(int k=0;k<i;++k)Wn[len/i*k]=(Complex){cos(k*PI/i),sin(k*PI/i)}; //先算Wn更快
    change(y, len);
    Complex u,t;
    for(int h = 1; h < len; h <<= 1) {
        for(int j = 0; j < len; j += h<<1) {
            for(int k = j; k < j + h; k++) {
                Complex w={Wn[len/h*(k-j)].x,Wn[len/h*(k-j)].y * on};
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


//G(x)=2H(x)-F(x)H(x)^2

int tmp[N];
int n;
void inv(int y[], int len, int ans[]) {
    memset(tmp, 0, sizeof(tmp));
    memset(ans, 0, sizeof(ans));
    ans[0] = qpow(y[0]);
    tmp[0] = y[0];
    for(int i=2;i<=len;i<<=1) {
        for(int j=0;j<i;j++) {
            tmp[j] = y[j];
        }        
        // clock_t _START_TIME = clock();
        
        any_mod_mul(i<<1, tmp, ans, tmp);
        any_mod_mul(i<<1, tmp, ans, tmp);
        // clock_t _END_TIME = clock();
        // cerr << "\ni="<<i<<"total time: " << (double)(_END_TIME - _START_TIME) / CLOCKS_PER_SEC << "s\n";

        for(int j=0;j<i;j++) {
            ans[j] = ((ans[j]*2 - tmp[j]) % mod + mod) % mod;
        }
        for(int j=i;j<len;j++) {
            ans[j]=0;
            tmp[j] = 0;
        }
    }
}

int a1[N],ans[N];
int read() {
    int ret=0,fl=1;char ch=getchar();
    while(!isdigit(ch)) (ch=='-')&&(fl=-1), ch=getchar();
    while(isdigit(ch)) ret=ret*10+ch-'0',ch=getchar();
    return ret*fl;
}
Complex test[N];
signed main() {
    // freopen("test.in","r",stdin);
    // freopen("testout.out","w",stdout);
    n = read();
    int stop = 1;
    for(int i = 0; i < n; i++) {
        a1[i] = read();
    }
    int lim = 1;
    while(lim < n) lim <<= 1;
    // clock_t _START_TIME = clock();
    
    inv(a1, lim, ans);
    // clock_t _END_TIME = clock();
    // cerr << "\ntotal time: " << (double)(_END_TIME - _START_TIME) / CLOCKS_PER_SEC << "s\n";
    for(int i=0;i<n;i++) {
        cout<<ans[i]<<' ';
    }
    return 0;
}