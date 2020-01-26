#include <bits/stdc++.h>
using namespace std;
int dp[4001][4001][2]; //0:left 1:right
int d[20][10000];
int query(int l,int r){
    if (l>r) return 0;
    int t=log2(r-l+1);
    return max(d[t][l],d[t][r-(1<<t)+1]);
}
int maxval(int l,int r,int n){
    if (l+n-1<2*n) return query(r+1,l+n-1);
    return query(r-n+1,l-1);
}
void init(int a[],int len){
    for (int i=0;i<len;++i){
        d[0][i]=a[i];
    }
    int t=1;
    for (int i=1;t<=len;++i){
        for (int j=0;j+t<len;++j)
            d[i][j]=max(d[i-1][j],d[i-1][j+t]);
        t<<=1;
    }
}
int a[4001];
int main(){
    int n,k;
    int sum=0;
    scanf("%d%d",&n,&k);
    for (int i=0;i<n;++i){
        scanf("%d",&a[i]);
        sum+=a[i];
        a[i+n]=a[i];
    }
    init(a,2*n);
    memset(dp,0x3f,sizeof(dp));
    if (2*k<n) dp[n-k][n+k][0]=dp[n-k][n+k][1]=0;
    else dp[0][n-1][0]=dp[0][n-1][1]=0;
    for (int l=2*k+1;l<n;++l){
        for (int i=0;i+l<2*n;++i){
            int j=i+l;
            //cout<<i<<','<<j<<'='<<maxval(i+1,j,n)<<' '<<maxval(i,j-1,n)<<endl;
            dp[i][j][0]=min(dp[i+1][j][1]+maxval(i+1,j,n)*(j-2*k-i),dp[i+1][j][0]+maxval(i+1,j,n));
            dp[i][j][1]=min(dp[i][j-1][1]+maxval(i,j-1,n),dp[i][j-1][0]+maxval(i,j-1,n)*(j-i-2*k));
        }
    }
    int ans=0x3f3f3f3f;
    for (int i=0;i<n;++i)
        ans=min(ans,min(dp[i][i+n-1][0],dp[i][i+n-1][1]));
    //cout<<ans<<' '<<sum<<endl;
    printf("%d",ans+sum);
}