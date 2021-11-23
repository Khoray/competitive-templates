#include<bits/stdc++.h>
using namespace std;
const double PI = acos(-1);

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
    for(int h = 2; h <= len; h <<= 1) {
        Complex wn(cos(-on * 2 * PI / h), sin(-on * 2 * PI / h));
        for(int j = 0; j < len; j += h) {
            Complex w(1, 0);
            for(int k = j; k < j + h / 2; k++) {
                Complex u = y[k];
                Complex t = w * y[k + h / 2];
                y[k] = u + t;
                y[k + h / 2] = u - t;
                w = w * wn;
            }
        }
    }
    if(on == -1)
        for(int i = 0; i < len; i++) {
            y[i].x /= len;
        }
}
const int N = 4e6+5;
Complex a1[N];
Complex a2[N];
int read() {
    int ret=0,fl=1;char ch=getchar();
    while(!isdigit(ch)) (ch=='-')&&(fl=-1), ch=getchar();
    while(isdigit(ch)) ret=ret*10+ch-'0',ch=getchar();
    return ret*fl;
}
int main() {
    
    int n,m;cin>>n>>m;
    n++,m++;
    for(int i=0;i<n;i++) {
        a1[i] = read();
    }
    for(int i=0;i<m;i++) {
        a2[i] = read();
    }
    int lim = 1,mx=2*max(n,m);
    while(lim < mx) lim<<=1;
    // mul
    fft(a1, lim, 1);
    fft(a2, lim, 1);
    for(int i=0;i<lim;i++) {
        a1[i] = a1[i] * a2[i];
    }
    fft(a1, lim, -1);


    for(int i=0;i<n+m-1;i++) {
        cout<<int(a1[i].x+0.5)<<' ';
    }
    return 0;
}