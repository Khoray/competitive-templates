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
// y不会改变
void inv(int y[], int len, int ans[]) { 
    memset(tmp, 0, sizeof(tmp));
    memset(ans, 0, sizeof(ans));
    ans[0] = qpow(y[0]);
    tmp[0] = y[0];
    for(int i=2;i<=len;i<<=1) {
        for(int j=0;j<i;j++) {
            tmp[j] = y[j];
        }        
        ntt(ans, i<<1, 1),ntt(tmp, i<<1, 1);
        for(int j=0;j<i<<1;j++) {
            ans[j] = (((ans[j]*2%mod-tmp[j]*ans[j]%mod*ans[j]%mod) % mod) + mod) % mod;
        }
        ntt(ans, i<<1, -1);
        for(int j=i;j<len<<1;j++) {
            ans[j]=0;
        }
    }
}

// y不会改变
int ln_tmp[N], inv_tmp[N];
void LN(int y[], int len, int ans[]) {
    memset(ln_tmp, 0, sizeof(ln_tmp));
    memset(inv_tmp, 0, sizeof(inv_tmp));
    for(int i=0;i<len - 1;i++) {
        ln_tmp[i] = y[i + 1] * (i + 1) % mod;
    }
    inv(y, len, inv_tmp);
    ntt(inv_tmp, len<<1, 1);
    ntt(ln_tmp, len<<1, 1);
    for(int i=0;i<len<<1;i++) {
        ans[i] = inv_tmp[i] * ln_tmp[i] % mod;
    }
    ntt(ans, len<<1, -1);
    for(int i=len-1;i;i--) {
        ans[i] = ans[i - 1] * qpow(i) % mod;
    }
    for(int i=len;i<len<<1;i++) {
        ans[i]=0;
    }
    ans[0] = 0;
}

// y不变 f(x) = f0(x)(1-lnf0(x)+A(x))
int lnf[N], tmpa[N];
void exp(int y[], int len, int ans[]) {
    memset(lnf, 0, sizeof(lnf));
    memset(ans, 0, sizeof(ans));
    ans[0] = 1;
    for(int i=2;i<=len;i<<=1) {
        LN(ans ,i, lnf);
        lnf[0] = (y[0] + 1 - lnf[0] + mod) % mod;
        for(int j=1;j<i;j++) {
            lnf[j] = (y[j] - lnf[j] + mod) % mod;
        }     
        ntt(ans, i<<1, 1),ntt(lnf, i<<1, 1);
        for(int j=0;j<i<<1;j++) {
            ans[j] = ((ans[j] *  lnf[j] % mod) + mod) % mod;
        }
        ntt(ans, i<<1, -1);
        for(int j=i;j<len<<1;j++) {
            ans[j]=0;
            lnf[j]=0; //?
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
signed main() {
    #ifdef _KHORAY
        freopen("test.in","r",stdin);
        freopen("test.out","w",stdout);
    #endif
    n = read();
    int stop = 1;
    for(int i = 0; i < n; i++) {
        a1[i] = read();
    }
    int lim = 1;
    while(lim < n) lim <<= 1;

    exp(a1, lim, ans);

    for(int i=0;i<n;i++) {
        cout<<ans[i]<<' ';
    }
    return 0;
}