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
#define N 10000
#define MatrixN 10000
#define M 10007

template<typename T>
T QuickPower(T x,int y,T unit) //unit*x=x
{
    if (y==0) return unit;
    T tmp=x;
    T ans=unit;
    while (y>0){
        if (y&1) ans=ans*tmp%M;
        tmp=tmp*tmp%M;
        y=y>>1;
    }
    return ans;
}

struct ACAM_node{
    int k[26];
    int fail;
    int sum;
};
struct ACAM{
    ACAM_node tr[N];
    int num;
    void clear(){
        memset(tr,0,sizeof(tr));
        num=0;
    }
    void insert(char ch[]){
        int len=strlen(ch);
        int now=0;
        for (int i=0;i<len;++i){
            int t=ch[i]-'A';
            if (tr[now].k[t]==0){
                ++num;
                tr[now].k[t]=num;
            }
            now=tr[now].k[t];
        }
        ++tr[now].sum;
    }
    void build(){
        int que[N];
        int q,p;
        p=0; q=0;
        for (int i=0;i<26;++i)
            if (tr[0].k[i]!=0){
                tr[tr[0].k[i]].fail=0;
                que[q]=tr[0].k[i];
                ++q;
            }
        
        while (p<q){
            int now=que[p];
            ++p;
            for (int i=0;i<26;++i){
                if (tr[now].k[i]!=0){
                    tr[tr[now].k[i]].fail=tr[tr[now].fail].k[i];
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
long long dp[200][MatrixN];
bool flag[N];
int main()
{
    int m;
    int n;
    char ch[1000];
    scanf("%d%d",&m,&n);
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
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    for (int k=1;k<=n;++k){
        for (int i=0;i<=map.num;++i)
            if (flag[i])
                for (int j=0;j<26;++j)
                    if (flag[map.tr[i].k[j]])
                        dp[k][map.tr[i].k[j]]=(dp[k][map.tr[i].k[j]]+dp[k-1][i])%M;
    }
    long long ans=QuickPower(26,n,1);
    for (int i=0;i<=map.num;++i)
        if (flag[i]) ans=(ans+M-dp[n][i])%M;
    printf("%lld\n",ans);
    return 0;
}