#include <bits/stdc++.h>
using namespace std;
char a[1001],b[1001];
int dp[501][501];
int main(){

    while (~scanf("%s%s",a+1,b+1)){
        int lena=strlen(a+1);
        int lenb=strlen(b+1);
        memset(dp,0,sizeof(dp));
        for (int i=1;i<=lena;++i)
            for (int j=1;j<=lenb;++j){
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                if (a[i]==b[j]) dp[i][j]=max(dp[i][j],dp[i-1][j-1]+1);
            }
        printf("%d\n",lena+lenb-dp[lena][lenb]);
    }
}