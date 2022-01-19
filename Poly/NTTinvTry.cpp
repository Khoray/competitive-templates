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


//G(x)=2H(x)-F(x)H(x)^2
const int N=1e6+5;
int tmp[N],n;
void inv(int y[], int len, int ans[]) {
    memset(tmp, 0, sizeof(tmp));
    memset(ans, 0, sizeof(ans));
    ans[0] = qpow(y[0]);
    tmp[0] = y[0];
    ntt(y, len, 1);
    for(int i=0;i<len;i++) {
        ans[i]=1ll*qpow(y[i]);
    }
    ntt(y, len, -1);
    ntt(ans, len, -1);
}

int a1[N],ans[N];
int read() {
    int ret=0,fl=1;char ch=getchar();
    while(!isdigit(ch)) (ch=='-')&&(fl=-1), ch=getchar();
    while(isdigit(ch)) ret=ret*10+ch-'0',ch=getchar();
    return ret*fl;
}
signed main() {
    n = read();
    int stop = 1;
    for(int i = 0; i < n; i++) {
        a1[i] = read();
    }
    int lim = 1;
    while(lim < n) lim <<= 1;

    inv(a1, lim, ans);

    for(int i=0;i<n;i++) {
        cout<<ans[i]<<' ';
    }
    return 0;
}