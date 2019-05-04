#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
#define N 10000
#define V 100000
int dp[V+1];
int w[N],val[N];
int num;
int c1[N],v1[N];
int dp2[V+1];
void Knapsack(int v){
    memset(dp,0x3f,sizeof(dp));
    dp[0]=0;
    for (int i=0;i<num;++i)
        for (int j=v;j>=w[i];--j)
            dp[j]=min(dp[j],dp[j-w[i]]+val[i]);
}
int main()
{
    int n,t;
    int maxv=0;

    scanf("%d%d",&n,&t);
    for (int i=0;i<n;++i){
        scanf("%d",&v1[i]);
        maxv=max(maxv,v1[i]);
    }
    for (int i=0;i<n;++i) scanf("%d",&c1[i]);
    
    num=0;
    for (int i=0;i<n;++i){
        for (int j=1;c1[i]>0;j=j<<1){
            int x=min(c1[i],j);
            c1[i]-=x;
            w[num]=x*v1[i];
            val[num]=x;
            ++num;
        }
    }
    Knapsack(t+maxv*maxv);

    memset(dp2,0x3f,sizeof(dp2));
    dp2[0]=0;
    for (int i=0;i<n;++i)
        for (int j=v1[i];j<=maxv*maxv;++j)
            dp2[j]=min(dp2[j],dp2[j-v1[i]]+1);
    
    int ans=0x3f3f3f3f;
    for (int i=0;i<=maxv*maxv;++i)
        ans=min(ans,dp[t+i]+dp2[i]);
    if (ans>=0x3f3f3f3f) printf("-1\n");
    else printf("%d\n",ans);
    return 0;
}