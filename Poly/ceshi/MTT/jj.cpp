#include<algorithm>
#include<iostream>
#include<cstring>
#include<climits>
#include<cstdlib>
#include<utility>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#include<map>
#include<set>
#define ri register int

using namespace std;

inline char gch()
{
    static char buf[100010], *h = buf, *t = buf;
    return h == t && (t = (h = buf) + fread(buf, 1, 100000, stdin), h == t) ? EOF : *h ++;
}

typedef long long lo;

typedef long double ld;

inline void re(lo &x)
{
    x = 0;
    char a; bool b = 0;
    while(!isdigit(a = getchar()))
        b = a == '-';
    while(isdigit(a))
        x = x * 10 + a - '0', a = getchar();
    if(b == 1)
        x = - x;
}

const lo ms = 3e5;

const lo mo = (1 << 15) - 1;

const ld pi = acosl(-1.0); 

struct in
{
	ld r, i;
	in(ld rr = 0.0, ld ii = 0.0)
	{
		r = rr, i = ii;
	}
	inline in conj()
	{
		return (in){r, -i};
	}
}a[ms], p[ms], q[ms], e[ms], f[ms], ae[ms], af[ms];

inline in operator + (in a, in b)
{
	return (in){a.r + b.r, a.i + b.i};
}

inline in operator - (in a, in b)
{
	return (in){a.r - b.r, a.i - b.i};
}

inline in operator * (in a, in b)
{
	return (in){a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r};
}

inline in operator / (in a, in b)
{
	return (in){(a.r * b.r + a.i * b.i) / (pow(b.r, 2) + pow(b.i, 2)), (a.i * b.r - a.r * b.i) / (pow(b.r, 2) + pow(b.i, 2))};
}

lo n, m, pp, ax[ms], bx[ms], pos[ms];

// inline void fft(in *a, lo len, ld tp)
// {
// 	for(ri i = 1; i < len; i ++)
// 		if(i < pos[i])
// 			swap(a[i], a[pos[i]]);
// 	in la, lb;
// 	for(ri i = 1; i < len; i <<= 1)
// 	{
// 		for(ri j = 0; j < len; j += (i << 1))
// 		{
// 			for(ri k = 0; k < i; k ++)
// 			{
// 				in w(cos(pi / i * k), tp * sin(pi / i * k));
// 				la = a[j + k], lb = w * a[j + k + i];
// 				a[j + k] = la + lb, a[j + k + i] = la - lb;
// 			}
// 		}
// 	}
// }
void change(in y[], int len) {
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

void fft(in y[], int len, int on) {
    change(y, len);
    for(int h = 2; h <= len; h <<= 1) {
        
        for(int j = 0; j < len; j += h) {
            for(int k = j; k < j + h / 2; k++) {
                in w(cos(-on * 2 * pi * (k - j) / h), sin(on * 2 * pi * (k - j) / h));
                in u = y[k];
                in t = w * y[k + h / 2];
                y[k] = u + t;
                y[k + h / 2] = u - t;
            }
        }
    }
    if(on == -1)
        for(int i = 0; i < len; i++) {
            y[i].r /= len;
        }
}

int main()
{
	freopen("test.in", "r", stdin);
	freopen("a.out", "w", stdout);
	re(n), re(m), re(pp);
	for(ri i = 0; i <= n; i ++)	
		re(ax[i]), ax[i] %= pp;
	for(ri i = 0; i <= m; i ++)
		re(bx[i]), bx[i] %= pp;
	lo len = 1, num = 0;
	while(len <= (n + m))
		len <<= 1, num ++;
	for(ri i = 0; i < len; i ++)
	{
		a[i] = (in){ax[i] & mo, ax[i] >> 15};//拆成复数 
		p[i] = (in){bx[i] & mo, bx[i] >> 15};
		// cout<<"i="<<i<<"  "<<::p[i].r<<'\n';
		pos[i] = ((pos[i >> 1] >> 1) | ((i & 1) << (num - 1)));
	}
	fft(a, len, 1), fft(p, len, 1);
	for(ri i = 0; i < len; i ++)//通过p求q 
		q[i] = p[(len - i) & (len - 1)].conj(),
		cout<<"i="<<i<<"  "<<p[i].r<<'\n';
	
	in g1(0, 2), g2(2, 0);
	for(ri i = 0; i < len; i ++)//e是博客里面整理出来的a，f是b 
		e[i] = (p[i] + q[i]) / g2, f[i] = (p[i] - q[i]) / g1;
	for(ri i = 0; i < len; i ++)//然后如5倍dft所说，将两个式子分别乘起来 
		ae[i] = a[i] * e[i], af[i] = a[i] * f[i];
	fft(ae, len, -1), fft(af, len, -1);
	for(ri i = 0; i <= n + m; i ++)//最后把系数带进去，注意除完要膜，不膜会炸（滑稽） 
		printf("%lld ", ((((lo)(ae[i].r / len + 0.5)) % pp 
					+ (((lo)(ae[i].i / len + 0.5) % pp) << 15) % pp
					+ (((lo)(af[i].r / len + 0.5) % pp) << 15) % pp
					+ (((lo)(af[i].i / len + 0.5) % pp) << 30) % pp) % pp + pp) % pp);
}