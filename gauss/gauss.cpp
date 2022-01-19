#include<iostream>
#include<cmath>

using namespace std;

const int N=110;
const double eps=1e-6;

int n;
double a[N][N];

int gauss()
{
    int c,r;
    for(c=0,r=0;c<n;c++)
    {
        int t=r;
        for(int i=r;i<n;i++)
            if(a[i][c]>a[t][c]) 
                t=i;
                
        if(a[t][c]==0) continue;   //若该列已全0，则无需操作
        
        for(int i=c;i<=n;i++) swap(a[t][i],a[r][i]);
        for(int i=n;i>=c;i--) a[r][i]/=a[r][c];   //该列第一个数变成1，整行都缩小a[r][c]倍，从后向前推
        
        for(int i=r+1;i<n;i++)
            if(fabs(a[i][c])>eps)   //将该列其他行的数清0
                for(int j=n;j>=c;j--)
                    a[i][j]-=a[r][j]*a[i][c];
        
        r++;
    }
    
    if(r<n)   //上三角矩阵的行数小于n，系数矩阵不满秩，不是唯一解
    {
        for(int i=r;i<n;i++)
            if(fabs(a[i][n])>eps) return 2;   //此时r行以后的系数矩阵部分全0，若增广矩阵的最后一列对应的值非0，说明矛盾，即无解
        return 1;
    }
    
    for(int i=n-1;i>=0;i--)
        for(int j=i+1;j<n;j++)
            a[i][n]-=a[j][n]*a[i][j];  //从后往前把每一列只消除了剩下一个1
            
    return 0;
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        for(int j=0;j<=n;j++) 
            cin>>a[i][j];
            
    int t=gauss();
    
    if(t==0) 
        for(int i=0;i<n;i++) printf("%.2lf\n",a[i][n]);
        
    else if (t == 1) puts("Infinite group solutions");
    else puts("No solution");
    
    return 0;
}