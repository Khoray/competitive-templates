#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<queue>
using namespace std;
#define ll long long
#define ull unsigned long long
#define RG register
#define MAX 444444
#define MOD (1000000007)
const double Pi=acos(-1);
const int m=sqrt(MOD);
inline int read()
{
    RG int x=0,t=1;RG char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}
int fpow(int a,int b){int s=1;while(b){if(b&1)s=1ll*s*a%MOD;a=1ll*a*a%MOD;b>>=1;}return s;}
struct Complex{double a,b;}W[MAX],A[MAX],B[MAX],C[MAX],D[MAX];
Complex operator+(Complex a,Complex b){return (Complex){a.a+b.a,a.b+b.b};}
Complex operator-(Complex a,Complex b){return (Complex){a.a-b.a,a.b-b.b};}
Complex operator*(Complex a,Complex b){return (Complex){a.a*b.a-a.b*b.b,a.a*b.b+a.b*b.a};}
int r[MAX];
void FFT(Complex *P,int N,int opt)
{
	for(int i=0;i<N;++i)if(i<r[i])swap(P[i],P[r[i]]);
	for(int i=1;i<N;i<<=1)
		for(int p=i<<1,j=0;j<N;j+=p)
			for(int k=0;k<i;++k)
			{
				Complex w=(Complex){W[N/i*k].a,W[N/i*k].b*opt};
				Complex X=P[j+k],Y=P[i+j+k]*w;
				P[j+k]=X+Y;P[i+j+k]=X-Y;
			}
	if(opt==-1)for(int i=0;i<N;++i)P[i].a/=1.0*N;
}
void Multi(int *a,int *b,int len,int *ret)
{
	for(int i=0;i<(len<<1);++i)A[i]=B[i]=C[i]=D[i]=(Complex){0,0};
	for(int i=0;i<len;++i)
	{
		a[i]%=MOD;b[i]%=MOD;
		A[i]=(Complex){(a[i]/m)*1.0,0};
		B[i]=(Complex){(a[i]%m)*1.0,0};
		C[i]=(Complex){(b[i]/m)*1.0,0};
		D[i]=(Complex){(b[i]%m)*1.0,0};
	}
	int N,l=0;
	for(N=1;N<=len;N<<=1)++l;
	for(int i=0;i<N;++i)r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	for(int i=1;i<N;i<<=1)
		for(int k=0;k<i;++k)W[N/i*k]=(Complex){cos(k*Pi/i),sin(k*Pi/i)};
	FFT(A,N,1);FFT(B,N,1);FFT(C,N,1);FFT(D,N,1);
	for(int i=0;i<N;++i)
	{
		Complex tmp=A[i]*C[i];
		C[i]=B[i]*C[i],B[i]=B[i]*D[i],D[i]=D[i]*A[i];
		A[i]=tmp;C[i]=C[i]+D[i];
	}
	FFT(A,N,-1);FFT(B,N,-1);FFT(C,N,-1);
	for(int i=0;i<len;++i)
	{
		ret[i]=0;
		ret[i]=(ret[i]+1ll*(ll)(A[i].a+0.5)%MOD*m%MOD*m%MOD)%MOD;
		ret[i]=(ret[i]+1ll*(ll)(C[i].a+0.5)%MOD*m%MOD)%MOD;
		ret[i]=(ret[i]+1ll*(ll)(B[i].a+0.5)%MOD)%MOD;
		ret[i]=(ret[i]+MOD)%MOD;
	}
}
int c[MAX],d[MAX];
#include<ctime>
void Inv(int *a,int *b,int len)
{
	if(len==1){b[0]=fpow(a[0],MOD-2);return;}
	Inv(a,b,len>>1);
    clock_t _START_TIME = clock();
	Multi(a,b,len,c);
	Multi(c,b,len,d);
    clock_t _END_TIME = clock();
    cerr << "\nlen="<<len<<"total time: " << (double)(_END_TIME - _START_TIME) / CLOCKS_PER_SEC << "s\n";
	for(int i=0;i<len;++i)b[i]=(b[i]+b[i])%MOD;
	for(int i=0;i<len;++i)b[i]=(b[i]+MOD-d[i])%MOD;
}
int n,a[MAX],b[MAX];
Complex test[MAX];
int main()
{
    freopen("test.in","r",stdin);
    freopen("ans.out","w",stdout);
	n=read();int N;
	for(int i=0;i<n;++i)test[i]={(double)read(),0};
	for(N=1;N<n;N<<=1);
    clock_t _START_TIME = clock();
    for(int i=1;i<N;i<<=1)
		for(int k=0;k<i;++k)W[N/i*k]=(Complex){cos(k*Pi/i),sin(k*Pi/i)};
	FFT(test,N,1);
    clock_t _END_TIME = clock();
    cerr << "\ntotal time: " << (double)(_END_TIME - _START_TIME) / CLOCKS_PER_SEC << "s\n";
	for(int i=0;i<n;++i)printf("%d ",b[i]);
	return 0;
}