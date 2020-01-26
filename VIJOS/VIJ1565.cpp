#include <bits/stdc++.h>
using namespace std;
char ops[500];
long long dpmax[501][501];
long long dpmin[501][501];
long long operate(char ch,long long a,long long b){
    if (ch=='+') return a+b;
    return a*b;
}
int main(){
    int n;
    scanf("%d%s",&n,ops);
    memset(dpmax,0x8f,sizeof(dpmax));
    memset(dpmin,0x3f,sizeof(dpmin));
    for (int i=0;i<n;++i){
        scanf("%lld",&dpmin[i][i]);
        dpmax[i][i]=dpmax[i+n][i+n]=dpmin[i+n][i+n]=dpmin[i][i];
        ops[i+n]=ops[i];
    }
    
    for (int l=1;l<n;++l){
        for (int i=0;i+l<2*n;++i){
            int j=i+l;
            for (int k=i;k<j;++k){
                dpmin[i][j]=min(
                    dpmin[i][j],
                    min(
                        min(operate(ops[k],dpmin[i][k],dpmin[k+1][j]),operate(ops[k],dpmax[i][k],dpmax[k+1][j])),
                        min(operate(ops[k],dpmin[i][k],dpmax[k+1][j]),operate(ops[k],dpmax[i][k],dpmin[k+1][j]))
                    )
                );
                dpmax[i][j]=max(
                    dpmax[i][j],
                    max(
                        operate(ops[k],dpmax[i][k],dpmax[k+1][j]),
                        operate(ops[k],dpmin[i][k],dpmin[k+1][j])
                    )
                );
            }
        }
    }
    long long ans=0x8f8f8f8f8f8f8f8f;
    for (int i=0;i<n;++i) ans=max(ans,dpmax[i][i+n-1]);
    printf("%lld\n",ans);
    ans=0x3f3f3f3f3f3f3f3f;
    for (int i=0;i<n;++i) ans=min(ans,dpmin[i][i+n-1]); 
    printf("%lld\n",ans);
}