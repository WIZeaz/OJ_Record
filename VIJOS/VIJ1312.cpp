#include <iostream>
using namespace std;
int h[1001];
int dp[1001][1001];
int main(){
    int n;
    scanf("%d",&n);
    for (int i=0;i<n;++i){
        scanf("%d",&h[i]);
        h[i+n]=h[i];
    }
    for (int t=1;t<n;++t)
        for (int i=0;i<2*n-t-1;++i){
            int j=i+t;
            for (int k=i;k<j;++k)
                dp[i][j]=max(dp[i][j],dp[i][k]+dp[k+1][j]+h[i]*h[k+1]*h[j+1]);
        }
    int ans=0;
    for (int i=0;i<n;++i)
        ans=max(ans,dp[i][i+n-1]);
    printf("%d",ans);
}