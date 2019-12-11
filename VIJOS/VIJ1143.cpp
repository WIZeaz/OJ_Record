#include <bits/stdc++.h>
using namespace std;
int w[101][101];
int dp[101][31][31][31];
int solve(int n){
    int x[3],y[3];
    for (int i=2;i<=2*n;++i)
        for (x[0]=1;x[0]<=min(i-1,n);++x[0])
            for (x[1]=1;x[1]<=min(i-1,n);++x[1])
                for (x[2]=1;x[2]<=min(i-1,n);++x[2]){
                    int s=0;
                    for (int j=0;j<3;++j){
                        y[j]=i-x[j];
                        s+=w[x[j]][y[j]];
                        for (int k=0;k<j;++k)
                            if (x[k]==x[j] && y[k]==y[j]) {s-=w[x[j]][y[j]]; break;}
                    }
                    dp[i][x[0]][x[1]][x[2]]=max(
                        max(max(dp[i-1][x[0]][x[1]][x[2]],dp[i-1][x[0]][x[1]][x[2]-1]),
                            max(dp[i-1][x[0]][x[1]-1][x[2]],dp[i-1][x[0]][x[1]-1][x[2]-1])
                        ),
                        max(max(dp[i-1][x[0]-1][x[1]][x[2]],dp[i-1][x[0]-1][x[1]][x[2]-1]),
                            max(dp[i-1][x[0]-1][x[1]-1][x[2]],dp[i-1][x[0]-1][x[1]-1][x[2]-1])
                        )
                    )+s;
                }
            
    return dp[2*n][n][n][n];
}
int main(){
    int n;
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j) scanf("%d",&w[i][j]);
    printf("%d",solve(n));
}