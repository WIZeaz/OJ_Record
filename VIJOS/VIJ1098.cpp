#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int t[1001];
int ansl[1001],ansr[1001];
int num=0;
int ans[1001];
int main(){
    int n;
    scanf("%d",&n);
    for (int i=0;i<n;++i) scanf("%d",&t[i]);
    for (int i=0;i<n;++i){
        if (num==0 || ans[num-1]<t[i]){
            ans[num]=t[i];
            ++num;
        } else {
            int pos=lower_bound(ans,ans+num,t[i])-ans;
            ans[pos]=t[i];
        }
        ansl[i]=num;

    }

    memset(ans,0,sizeof(ans));
    num=0;
    for (int i=n-1;i>=0;--i){
        if (num==0 || ans[num-1]<t[i]){
            ans[num]=t[i];
            ++num;

        } else {
            int pos=lower_bound(ans,ans+num,t[i])-ans;
            ans[pos]=t[i];
        }
        ansr[i]=num;
    }
    int m=0;
    for (int i=0;i<n;++i) m=max(m,ansl[i]+ansr[i]-1);
    printf("%d",n-m);
}