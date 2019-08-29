#include <bits/stdc++.h>
using namespace std;
long long h[50001];
long long p[50001];
const long long M=1000000007;
char str[50001];
int getHash(int l,int r){
    return (h[r]-h[l-1]*p[r-l+1]%M+M)%M;
}
int main(){
    p[0]=1;
    for (int i=1;i<=30000;++i) p[i]=p[i-1]*29%M;
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%s",str+1);
        int len=strlen(str+1);
        if (len&1) {printf("0\n"); continue;}
        h[0]=0;
        for (int i=1;i<=len;++i){
            h[i]=(h[i-1]*29%M+str[i]-'a'+1)%M;
        }
        long long ans=0;
        for (int i=2;i<=len;i+=2){
            int l1=i>>1;
            int l2=len-i>>1;
            if (getHash(1,l1)==getHash(l1+1,i) && getHash(i+1,i+l2)==getHash(i+l2+1,len)) ++ans;
        }
        printf("%lld\n",ans);
    }
}