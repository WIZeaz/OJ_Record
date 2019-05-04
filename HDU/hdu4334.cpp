#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define N 500000
int Next[N];
char str[N];
char tmp[N];
void getNext(char s2[],int Next[])
{
    int len=strlen(s2);
    int j=0;
    Next[0]=Next[1]=0;
    for (int i=1;i<len;i++){
		while (j>0 && s2[j]!=s2[i]) j=Next[j];
		if (s2[j]==s2[i]) ++j;
		Next[i+1]=j;
	}
}
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
}
int main()
{
    int len;
    int T;
    scanf("%d",&T);
    for (int ca=1;ca<=T;++ca){

        scanf("%s",tmp);

        len=strlen(tmp);
        getNext(tmp,Next);
        int repeat=len/(len-Next[len]);

        strcpy(str,"\0");
        strcat(str,tmp);
        strcat(str,tmp);


        Next[0]=2*len;
        exkmp(str+1,str,Next,Next+1);
        int l,e,g;
        l=e=g=0;
        for (int i=0;i<len;++i){
            if (Next[i]>=len) ++e;
            else if (str[Next[i]]<str[i+Next[i]]) ++g;
            else ++l;
        }
        printf("Case %d: %d %d %d\n",ca,l/repeat,e/repeat,g/repeat);
    }
}