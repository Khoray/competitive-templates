const int mod = 998244353, inv2 = mod + 1 >> 1;
const int maxn = 400007; // 4 times of N
inline int add(int a, int b) {
    return a + b >= mod ? a + b - mod : a + b;
}
inline int dec(int a, int b) {
    return a < b ? a - b + mod : a - b;
}
inline int mul(int a, int b) {
    return (ll)a * b % mod;
}
inline int pown(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) {
            res = mul(res, a);
        }
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

struct cn {
    int x, y, w;
    cn operator * (cn a) {
        cn ans;
        ans.x = (1LL * x * a.x % mod + 1LL * y * a.y % mod * w % mod) % mod;
        ans.y = (1LL * x * a.y % mod + 1LL * y * a.x % mod) % mod;
        ans.w = w;
        return ans;
    }
    int operator ^ (int b) {
        cn ans, x = *this;
        ans.x = 1;
        ans.y = 0;
        ans.w = w;
        while(b) {
            if(b & 1) {
                ans = ans * x;
            }
            x = x * x;
            b >>= 1;
        }
        return ans.x;
    }
};
int sqrt_mod(int n) {
    if(n == 0) {
        return 0;
    }
    if(pown(n, (mod - 1) / 2) == mod - 1) {
        return -1;
    }
    int a, w;
    while(1) {
        a = rand() % mod;
        w = (1LL * a * a - n + mod) % mod;
        if(pown(w, (mod - 1) / 2) == mod - 1) {
            break;
        }
    }
    cn x;
    x.x = a;
    x.y = 1;
    x.w = w;
    return x ^ ((mod + 1) / 2);
}
typedef vector<int> Poly;
inline void print(const Poly &a, char c = ' ') {
    for(int i = 0; i < a.size(); ++i) {
        cout << a[i] << c;
    }
}
int rev[maxn], inv[maxn];
inline void ntt(Poly &a, int n, int dft) {
    for(int i = 0; i < n; ++i)
        if(i < rev[i]) {
            swap(a[i], a[rev[i]]);
        }
    for(int i = 1; i < n; i <<= 1) {
        int wn = pown(dft == -1 ? (mod + 1) / 3 : 3, (mod - 1) / i / 2);
        for(int j = 0; j < n; j += i << 1)
            for(int k = 0, x, y, w = 1; k < i; ++k, w = mul(w, wn)) {
                x = a[j + k], y = mul(w, a[j + k + i]);
                a[j + k] = add(x, y);
                a[j + k + i] = dec(x, y);
            }
    }
    if(dft == -1)
        for(int i = 0; i < n; ++i) {
            a[i] = mul(a[i], inv[n]);
        }
}
inline void init_rev(int len) {
    for(int i = 0; i < len; ++i) {
        rev[i] = rev[i >> 1] >> 1 | ((i & 1) * (len >> 1));
    }
}
inline Poly operator + (const Poly &a, const Poly &b) {
    Poly c = a;
    c.resize(max(a.size(), b.size()));
    for(int i = 0; i < b.size(); ++i) {
        c[i] = add(c[i], b[i]);
    }
    return c;
}
inline Poly operator - (const Poly &a, const Poly &b) {
    Poly c = a;
    c.resize(max(a.size(), b.size()));
    for(int i = 0; i < b.size(); ++i) {
        c[i] = dec(c[i], b[i]);
    }
    return c;
}
inline Poly operator * (Poly a, Poly b) {
    int n = a.size(), m = b.size(), l = 1;
    while(l < n + m - 1) {
        l <<= 1;
    }
    init_rev(l);
    a.resize(l), ntt(a, l, 1);
    b.resize(l), ntt(b, l, 1);
    for(int i = 0; i < l; ++i) {
        a[i] = mul(a[i], b[i]);
    }
    ntt(a, l, -1);
    a.resize(n + m - 1);
    return a;
}
inline Poly operator * (Poly a, int b) {
    for(int i = 0; i < a.size(); ++i) {
        a[i] = mul(a[i], b);
    }
    return a;
}
inline Poly Deriv(Poly a) {
    for(int i = 0; i + 1 < a.size(); ++i) {
        a[i] = mul(a[i + 1], i + 1);
    }
    a.pop_back();
    return a;
}
inline Poly Integ(Poly a) {
    a.push_back(0);
    for(int i = a.size() - 1; i; --i) {
        a[i] = mul(a[i - 1], inv[i]);
    }
    a[0] = 0;
    return a;
}
inline Poly Inv(const Poly &a, int lim) {
    Poly c, b(1, pown(a[0], mod - 2));
    for(int l = 4; (l >> 2) < lim; l <<= 1) {
        init_rev(l);
        c = a, c.resize(l >> 1);
        c.resize(l), ntt(c, l, 1);
        b.resize(l), ntt(b, l, 1);
        for(int i = 0; i < l; ++i) {
            b[i] = mul(b[i], dec(2, mul(c[i], b[i])));
        }
        ntt(b, l, -1);
        b.resize(l >> 1);
    }
    b.resize(lim);
    return b;
}
inline Poly Inv(const Poly &a) {
    return Inv(a, a.size());
}
inline Poly Ln(Poly a, int lim) {
    a = Integ(Deriv(a) * Inv(a, lim));
    a.resize(lim);
    return a;
}
inline Poly Ln(const Poly &a) {
    return Ln(a, a.size());
}
inline Poly Exp(const Poly &a, int lim) {
    Poly c, b(1, 1);
    int n = a.size();
    for(int i = 2; (i >> 1) < lim; i <<= 1) {
        c = Ln(b, i);
        for(int j = 0; j < i; ++j) {
            c[j] = dec(j < n ? a[j] : 0, c[j]);
        }
        c[0] = add(c[0], 1);
        b = b * c;
        b.resize(i);
    }
    b.resize(lim);
    return b;
}
inline Poly Exp(const Poly &a) {
    return Exp(a, a.size());
}
const int w4 = pown(3, (mod - 1) / 4);
inline Poly Cos(const Poly &a, int lim) {
    Poly c = a;
    c.resize(lim);
    c = (Exp(c * w4) + Exp(c * (mod - w4))) * inv2;
    return c;
}
inline Poly Cos(const Poly &a) {
    return Cos(a, a.size());
}

inline Poly Sin(const Poly &a, int lim) {
    Poly c = a;
    c.resize(lim);
    c = (Exp(c * w4) - Exp(c * (mod - w4))) * mul(inv2, pown(w4, mod - 2));
    return c;
}
inline Poly Sin(const Poly &a) {
    return Sin(a, a.size());
}

inline Poly Sqrt(const Poly &a, int lim) {
    Poly c, d, b(1, sqrt_mod(a[0]));
    for(int l = 4; (l >> 2) < lim; l <<= 1) {
        init_rev(l);
        c = a, c.resize(l >> 1);
        d = Inv(b, l >> 1);
        c.resize(l), ntt(c, l, 1);
        d.resize(l), ntt(d, l, 1);
        for(int j = 0; j < l; ++j) {
            c[j] = mul(c[j], d[j]);
        }
        ntt(c, l, -1);
        b.resize(l >> 1);
        for(int j = 0; j < (l >> 1); ++j) {
            b[j] = mul(add(c[j], b[j]), inv2);
        }
    }
    b.resize(lim);
    return b;
}
inline void Strip(Poly &a) {
    while(a.back() == 0) {
        a.pop_back();
    }
}
inline Poly Sqrt(const Poly &a) {
    return Sqrt(a, a.size());
}

inline Poly Ksm(Poly a, int k, int lim) {
    a = Exp(Ln(a) * k);
    a.resize(lim);
    return a;
}
inline Poly Ksm(const Poly &a, int k) {
    return Ksm(a, k, a.size());
}
inline Poly operator / (Poly a, Poly b) {
    int len = 1, deg = a.size() - b.size() + 1;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    while(len <= deg) {
        len <<= 1;
    }
    b = Inv(b, len);
    b.resize(deg);
    a = a * b;
    a.resize(deg);
    reverse(a.begin(), a.end());
    return a;
}
inline Poly operator % (const Poly &a, const Poly &b) {
    Poly c = a - (a / b) * b;
    c.resize(b.size() - 1);
    Strip(c);
    return c;
}
inline void init_inv() {
    inv[0] = inv[1] = 1;
    for(int i = 2; i < maxn; ++i) {
        inv[i] = mul(inv[mod % i], mod - mod / i);
    }
}