#include<bits/stdc++.h>
using namespace std;

#define int long long
const int mod = 1004535809;

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

void ntt(int y[], int len, int on) {
    change(y, len);
    for(int h = 2; h <= len; h <<= 1) {
        int gn = qpow(3, (mod - 1) / h)  % mod;
        if(on == -1) gn = qpow(gn); //这里把gn倒过来加
        for(int j = 0; j < len; j += h) {
            int g = 1;
            for(int k = j; k < j + h / 2; k++) {
                int u = y[k];
                int t = g * y[k + h / 2] % mod;
                y[k] = (u + t) % mod;
                y[k + h / 2] = (u - t + mod) % mod;
                g = g * gn % mod;
            }
        }
    }
    if(on == -1) //reverse(y+1,y+len); 或者这里反过来(不要共存)
        for(int i = 0; i < len; i++) {
            y[i] = y[i] * qpow(len) % mod;
        }
}
const int N=4e5+5;
int a[N];
int b[N];

int read() {
    int ret=0,fl=1;char ch=getchar();
    while(!isdigit(ch)) (ch=='-')&&(fl=-1), ch=getchar();
    while(isdigit(ch)) ret=(ret*10+ch-'0')%mod,ch=getchar();
    return ret*fl;
}

signed main() {
    int n = read(), k = read(), op = read();
    for(int i=1;i<=n;i++) {
        a[i] = read();
    }
    if(op == 0) {
        int nowfac = 1, nowfenzi = 1;
        b[0] = 1;
        for(int i=1;i<=n;i++) {
            (nowfac *= i) %= mod;
            (nowfenzi *= (k - 1 + i) % mod) %= mod;
            b[i] = nowfenzi * qpow(nowfac) % mod;
            // cout<<b[i]<<' ';
        }
        // cout<<'\n';

        
    } else {
        b[0] = 1;
        int nowk = 1, nowif = 1;
        for(int i=1;i<=n;i++) {
            if(i > k) break;
            nowif = nowif * i % mod;
            nowk = nowk * (k - i + 1) % mod;
            
            b[i] = qpow(nowif) * nowk % mod;
            if(i & 1) b[i] = mod - b[i];
            // cout<<nowk<<" "<<b[i]<<'\n';
        }
        // cout<<'\n';

    }
    int lim = 1;
    while(lim <= n + n) lim <<= 1;

    // mul
    ntt(a, lim, 1);
    ntt(b, lim, 1);
    for(int i=0;i<lim;i++) {
        a[i] = a[i] * b[i] % mod;
    }
    ntt(a, lim, -1);


    for(int i=1;i<=n;i++) {
        cout<<a[i]<<' ';
    }
    return 0;
}