#include<bits/stdc++.h>
using namespace std;

#define int long long
const int mod = 998244353;

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
int a1[16];
int a2[16];
signed main() {
    for(int i = 0; i < 8; i++) {
        a1[i] = i;
        a2[i] = i;
    }
    int lim = 16;


    // mul
    ntt(a1, lim, 1);
    ntt(a2, lim, 1);
    for(int i=0;i<lim;i++) {
        a1[i] = a1[i] * a2[i] % mod;
    }
    ntt(a1, lim, -1);


    for(int i=0;i<lim;i++) {
        cout<<a1[i]<<' ';
    }
    return 0;
}