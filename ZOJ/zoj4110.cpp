#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXSTRLEN 2000000
long long ans;
char ch[2*MAXSTRLEN+3];
int p[2*MAXSTRLEN+3];
void manacher(char str[]){
    int len=strlen(str);
    for (int i=0;i<len;++i){
        ch[2*i+1]='#';
        ch[2*i+2]=str[i];
    }
    ch[0]='$';
    ch[2*len+1]='#';
    ch[2*len+2]='\0';
    len=len*2+2;
    p[0]=p[1]=1;
    int id,mx;
    id=1; mx=2;
    ans=0;
    for (int i=2;i<len;++i){
        int j;
        if (i<mx) j=min(p[2*id-i],mx-i);
        else j=1;
        while (ch[i-j]==ch[i+j]) ++j;
        p[i]=j;
        if (j+p[j]>mx) {id=j; mx=j+p[j];}
        ans+=p[i]/2;
    }
}
char s[MAXSTRLEN+1],t[MAXSTRLEN+1];
bool check(int l,int r){
    for (int i=0;i<=r-l;++i)
        if (s[l+i]!=t[r-i]) return false;
    return true;
}
int main()
{
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%s%s",s,t);
        int l,r,num=0;
        int len=strlen(s);
        for (l=0;l<len && s[l]==t[l];++l);
        ans=0;
        if (l<len){
            for (r=len-1;r>=0 && s[r]==t[r];--r);
            if (check(l,r)){
                ans=1;
                for (int i=1;l-i>=0 && r+i<len && s[l-i]==s[r+i];++i) ++ans;
            }
        } else {
            manacher(s);
        }
        printf("%lld\n",ans);
    }
}