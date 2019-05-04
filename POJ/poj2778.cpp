/*
AC自动机 多模式匹配算法
By:WIZeaz
O(m)建图
O(n)查询转移
*/

#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;
#define N 100
#define MatrixN 110
const long long M=100000;
struct matrix{
    long long arr[MatrixN][MatrixN];
    static int n;
    matrix(){
        memset(arr,0,sizeof(arr));
    }
    static matrix unit(){
        matrix tmp;
        for (int i=0;i<MatrixN;++i)
            tmp.arr[i][i]=1;
        return tmp;
    }
    matrix operator * (const matrix &b) const{
        matrix tmp;
        for (int i=0;i<n;++i)
            for (int j=0;j<n;++j)
                for (int k=0;k<n;++k)
                    tmp.arr[i][j]=(tmp.arr[i][j]+arr[i][k]*b.arr[k][j])%M;
        return tmp;
    }
    matrix set(const long long b[MatrixN][MatrixN]){
        memcpy(arr,b,sizeof(arr));
    }
};
int matrix::n=MatrixN;

template<typename T>
T QuickPower(T x,int y,T unit) //unit*x=x
{
    if (y==0) return unit;
    T tmp=x;
    T ans=unit;
    while (y>0){
        if (y&1) ans=ans*tmp;
        tmp=tmp*tmp;
        y=y>>1;
    }
    return ans;
}

struct ACAM_node{
    int k[4];
    int fail;
    bool flag;
    int sum;
};
struct ACAM{
    ACAM_node tr[2*N];
    int num;
    void clear(){
        memset(tr,0,sizeof(tr));
        num=0;
        tr[num].flag=true;
    }
    void insert(char ch[]){
        int len=strlen(ch);
        int now=0;
        for (int i=0;i<len;++i){
            tr[now].flag=true;
            int t;
            if (ch[i]=='A') t=0;
            else if (ch[i]=='C') t=1;
            else if (ch[i]=='T') t=2;
            else if (ch[i]=='G') t=3;
            if (tr[now].k[t]==0){
                ++num;
                tr[now].k[t]=num;
            }
            now=tr[now].k[t];
        }
        ++tr[now].sum;
        tr[now].flag=false;
    }
    void build(){
        int que[2*N];
        int q,p;
        p=0; q=0;
        for (int i=0;i<4;++i)
            if (tr[0].k[i]!=0){
                tr[tr[0].k[i]].fail=0;
                que[q]=tr[0].k[i];
                ++q;
            }
        
        while (p<q){
            int now=que[p];
            ++p;
            for (int i=0;i<4;++i){
                if (tr[now].k[i]!=0){
                    tr[tr[now].k[i]].fail=tr[tr[now].fail].k[i];
                    tr[tr[now].k[i]].flag=tr[tr[now].k[i]].flag&&tr[tr[tr[now].fail].k[i]].flag;
                    que[q]=tr[now].k[i];
                    ++q;
                } else {
                    tr[now].k[i]=tr[tr[now].fail].k[i];
                }
            }
        }
    }
};

ACAM map;
long long dp[MatrixN][MatrixN]; 
bool flag[2*N];
matrix a;
int main()
{
    int m;
    long long n;
    char ch[1000];
    scanf("%d%lld",&m,&n);
    map.clear();
    memset(dp,0,sizeof(dp));
    for (int i=0;i<m;++i){
        scanf("%s",ch);
        map.insert(ch);
    }
    map.build();
    memset(flag,false,sizeof(flag));
    for (int i=0;i<=map.num;++i){
        int tmp=i;
        while (map.tr[tmp].sum==0 && tmp>0)  tmp=map.tr[tmp].fail;
        if (tmp==0) flag[i]=true;
    }

    for (int i=0;i<=map.num;++i)
        if (flag[i])
            for (int j=0;j<4;++j)
                if (flag[map.tr[i].k[j]]) dp[map.tr[i].k[j]][i]+=1;
                
    matrix::n=map.num+1;
    a.set(dp);
    a=QuickPower(a,n,matrix::unit());
    long long ans=0;
    for (int i=0;i<=map.num;++i)
        ans=(ans+a.arr[i][0])%M;
    printf("%lld\n",ans);
    return 0;
}