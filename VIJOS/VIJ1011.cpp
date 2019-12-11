#include <bits/stdc++.h>
using namespace std;
int dp[501][501];
int h[501][501];
int mx[]={0,1,0,-1};
int my[]={1,0,-1,0};
int n,m;
int solve(int x,int y){
    if (~dp[x][y]) return dp[x][y];
    int ans=1;
    for (int i=0;i<4;++i){
        int dx=x+mx[i];
        int dy=y+my[i];
        if (dx>=0 && dx<n && dy>=0 && dy<m && h[dx][dy]<h[x][y]) ans=max(ans,solve(dx,dy)+1);
    }
    dp[x][y]=ans;
    return ans;
}
int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d%d",&n,&m);
    for (int i=0;i<n;++i)
        for (int j=0;j<m;++j) scanf("%d",&h[i][j]);
    int ans=0;
    for (int i=0;i<n;++i)
        for (int j=0;j<m;++j) ans=max(ans,solve(i,j));
    printf("%d",ans);
}