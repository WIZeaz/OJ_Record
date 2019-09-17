#include <bits/stdc++.h>
using namespace std;
#define MAXSTRLEN 300000
int maxlen=0;
char ch[MAXSTRLEN];
int p[MAXSTRLEN];
void manacher(char str[],int len){
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
    for (int i=2;i<len;++i){
        int j;
        j=min(p[2*id-i],mx-i);
        while (ch[i-j]==ch[i+j]) ++j;
        p[i]=j;
        if (i+p[i]>mx) {id=i; mx=i+p[i];}
        maxlen=max(maxlen,p[i]-1);
    }
}
char str[MAXSTRLEN+1];
int rnk[MAXSTRLEN];
int buckets[MAXSTRLEN];
int sa[MAXSTRLEN]; //the start position of rank i suffix, rank is starting from one, index start from one as well
int tsa[MAXSTRLEN]; //temporary suffix array
int height[MAXSTRLEN];

int bucketSort(int len,int charnum,int k){
    for (int i=0;i<=charnum;++i) buckets[i]=0;
    for (int i=0;i<len;++i) buckets[rnk[i]]++;
    for (int i=1;i<=charnum;++i) buckets[i]+=buckets[i-1];
    for (int i=len;i>=1;--i) sa[buckets[rnk[tsa[i]]]--]=tsa[i];
    swap(tsa,rnk); //sheng shu zu
    charnum=1;
    rnk[sa[1]]=1;
    for (int i=2;i<=len;++i){
        if (tsa[sa[i]]!=tsa[sa[i-1]]) ++charnum;
        else if ((sa[i]+k>=len) != (sa[i-1]+k>=len)) ++charnum;
        else if ((sa[i]+k<len && sa[i-1]+k<len) && tsa[sa[i]+k]!=tsa[sa[i-1]+k]) ++charnum;
        rnk[sa[i]]=charnum;
    }
    return charnum;
}
void SuffixSort(char str[],int len){
    for (int i=0;i<len;++i){
        rnk[i]=int(str[i]);
        tsa[i+1]=i;
    }
    int charnum=bucketSort(len,256,0);
    for (int k=1;k<len && charnum<len;k<<=1){
        int t=0;
        for (int i=0;i<k;++i) tsa[++t]=len-k+i;
        for (int i=1;i<=len;++i) if (sa[i]-k>=0) tsa[++t]=sa[i]-k;
        charnum=bucketSort(len,charnum,k);
    }
}
void getHeight(char str[],int len){
    int j=0;
    for (int i=0;i<len;++i){
        if (rnk[i]-1>0) while (str[i+j]==str[sa[rnk[i]-1]+j]) ++j;
        height[rnk[i]]=j;
        if (j>0) --j;
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    for (int C=1;C<=T;++C){
        scanf("%s",str);
        int len=strlen(str);
        manacher(str,len);
        len=strlen(ch);
        SuffixSort(ch,len);
        getHeight(ch,len);
        //printf("%s\n",ch);
        long long ans=p[sa[1]]/2;
        height[1]=0;
        int pre=0;
        for (int i=1;i<=len;++i){
            pre=min(pre,height[i]);
            if (p[sa[i]]<=pre) continue;
            ans+=(p[sa[i]]-pre)/2;
            //printf("pos=%d p=%d overlay=%d tot=%lld\n",sa[i],p[sa[i]],min(pre,height[i]),ans);
            pre=p[sa[i]];
        }
        printf("Case #%d: %lld\n",C,ans);
    }
}