#include <bits/stdc++.h>
using namespace std;
long long dp[5001][5001];
char a[5001],b[5001];
int main(){
    int k;
    scanf("%s%s%d",a+1,b+1,&k);
    int lena=strlen(a+1);
    int lenb=strlen(b+1);
    memset(dp,0x3f,sizeof(dp));
    dp[0][0]=0;
    for (int i=1;i<=lena;++i) dp[i][0]=i*k;
    for (int i=1;i<=lenb;++i) dp[0][i]=i*k;
    
    for (int i=1;i<=lena;++i)
        for (int j=1;j<=lenb;++j)
            dp[i][j]=min(dp[i-1][j-1]+abs(a[i]-b[j]),min(dp[i-1][j],dp[i][j-1])+k);
    /*for (int i=1;i<=lena;++i){
        for (int j=1;j<=lenb;++j)
            cout<<dp[i][j]<<' ';
        cout<<endl;
    }*/
    printf("%lld",dp[lena][lenb]);

}