#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define N 10000
int Next[N],ex[N];
void exkmp(char s1[],char s2[],int Next[],int ex[]){
    int i,j,k;
    int len1=strlen(s1);
    int len2=strlen(s2);
    i=0; j=0; k=-1;
    while (i<len1){
        if (k==-1){
            k=0; j=0;
            while (s1[i+k]==s2[j+k] && i+k<len1 && j+k<len2) ++k;
            ex[i]=k;
        } else if (Next[j]<k){
            ex[i]=Next[j];
        } else if (Next[j]>k){
            ex[i]=k;
        } else {
            j=0;
            while (s1[i+k]==s2[j+k] && i+k<len1 && j+k<len2) ++k;
            ex[i]=k;
        }
        ++i; ++j; --k;
    }
    ex[len1]=0;
}
char s1[10000],s2[10000];
int main()
{
    while (~scanf("%s",s1)){
        if (strcmp(s1,"#")==0) return 0;
        scanf("%s",s2);
        Next[0]=0;
        exkmp(s2+1,s2,Next,Next+1);
        exkmp(s1,s2,Next,ex);
        int len=strlen(s1);
        int tlen=strlen(s2);
        int ans=0;
        for (int i=0;i<len;++i){
            if (ex[i]==tlen){++ans; i+=tlen-1;}
        }
        printf("%d\n",ans);
    }
}