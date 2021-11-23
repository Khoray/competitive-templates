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
int ans[N],ans_pr;
int main() {
    string a, b;
    cin>>a>>b;

    for(int i = 0; i < a.length(); i++) {
        a1[i] = a[a.length() - i - 1] - '0';
    }

    for(int i = 0; i < b.length(); i++) {
        a2[i] = b[b.length() - i - 1] - '0';
    }

    int ma = max(a.length(), b.length()) * 2;
    int lim = 1;
    while(lim < ma) lim <<= 1;

    // mul
    fft(a1, lim, 1);
    fft(a2, lim, 1);
    for(int i=0;i<lim;i++) {
        a1[i] = a1[i] * a2[i];
    }
    fft(a1, lim, -1);

    // for(int i=0;i<lim;i++) {
    //     cout<<a1[i].x<<' ';
    // }
    // cout<<'\n';

    int zero = 1;
    for(int i=lim-1;~i;i--) {
        if((int)(a1[i].x+0.5) != 0) {
            zero = 0;
        }
        if(!zero) {
            ans[++ans_pr] = (int)(a1[i].x+0.5);
        }
    }
    for(int i=ans_pr;~i;i--) {
        if(ans[i] >= 10) {
            ans[i-1] += ans[i] / 10;
            ans[i] %= 10;
        }
    }

    if(ans[0]) cout<<ans[0];
    for(int i=1;i<=ans_pr;i++) cout<<ans[i];
    return 0;
}