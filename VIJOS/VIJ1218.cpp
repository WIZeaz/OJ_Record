#include <bits/stdc++.h>
using namespace std;
int a[10001];
int dpMax[101][101][101];
int dpMin[101][101][101];
int sum(int l,int r){
    return ((a[r]-a[l-1])%10+10)%10;
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i){
        scanf("%d",&a[i]);
        a[i+n]=a[i];
    }
    for (int i=1;i<=2*n;++i) a[i]+=a[i-1];
    memset(dpMin,0x3f,sizeof(dpMin));
    for (int i=1;i<=2*n;++i)
        for (int j=i;j<=2*n;++j) dpMax[i][j][1]=dpMin[i][j][1]=sum(i,j);
    for (int t=2;t<=m;++t)
        for (int i=1;i<=2*n-t+1;++i)
            for (int j=i+t-1;j<=2*n;++j)
                for (int k=i+t-2;k<j;++k){
                    dpMax[i][j][t]=max(dpMax[i][j][t],dpMax[i][k][t-1]*sum(k+1,j));
                    dpMin[i][j][t]=min(dpMin[i][j][t],dpMin[i][k][t-1]*sum(k+1,j));
                }
    int Min,Max;
    Min=0x3f3f3f3f;
    Max=0;
    for (int i=1;i<=n;++i){
        Min=min(Min,dpMin[i][i+n-1][m]);
        Max=max(Max,dpMax[i][i+n-1][m]);
    }
    printf("%d\n%d",Min,Max);
}