#include <bits/stdc++.h>
using namespace std;
int w[101][101];
int dp[101][101][101][101];
int solve(int n,int m){
    for (int i=1;i<=n;++i)
        for (int j=1;j<=m;++j)
            for (int k=1;k<=n;++k)
                for (int l=1;l<=m;++l)
                if ((i!=k && j!=l) || (i==n && j==m && k==n && l==m)){
                    dp[i][j][k][l]=max(max(dp[i-1][j][k-1][l],dp[i-1][j][k][l-1]),max(dp[i][j-1][k-1][l],dp[i][j-1][k][l-1]))+w[i][j]+w[k][l];
                }
    return dp[n][m][n][m];
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i)
        for (int j=1;j<=m;++j) scanf("%d",&w[i][j]);
    printf("%d",solve(n,m));
}