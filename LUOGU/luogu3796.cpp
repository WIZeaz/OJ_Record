#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;
#define N 100000
struct ACAM_node{
    int k[26];
    int fail;
    int no;
};
int cnt[200];
struct ACAM{
    ACAM_node tr[N];
    int num;
    void clear(){
        memset(tr,0,sizeof(tr));
        num=0;
    }
    void insert(char ch[],int no){
        int len=strlen(ch);
        int now=0;
        for (int i=0;i<len;++i){
            int t=ch[i]-'a';
            if (tr[now].k[t]==0){
                ++num;
                tr[now].k[t]=num;
            }
            now=tr[now].k[t];
        }
        tr[now].no=no;
    }
    void build(){
        int que[N];
        int q,p;
        p=0; q=0;
        for (int i=0;i<26;++i)
            if (tr[0].k[i]!=0){
                tr[tr[0].k[i]].fail=0;
                que[q]=tr[0].k[i];
                ++q;
            }
        
        while (p<q){
            int now=que[p];
            ++p;
            for (int i=0;i<26;++i){
                if (tr[now].k[i]!=0){
                    tr[tr[now].k[i]].fail=tr[tr[now].fail].k[i];
                    que[q]=tr[now].k[i];
                    ++q;
                } else {
                    tr[now].k[i]=tr[tr[now].fail].k[i];
                }
            }
        }
    }
    int query(char ch[],int n){

        memset(cnt,0,sizeof(cnt));
        int len=strlen(ch);
        int now=0;
        for (int i=0;i<len;++i){
            int t=ch[i]-'a';
            now=tr[now].k[t];
            int tmp=now;
            while (tmp!=0){
                cnt[tr[tmp].no]++;
                tmp=tr[tmp].fail;
            }
        }
        int ans=0;
        for (int i=1;i<=n;++i)
            if (ans<cnt[i]) {ans=cnt[i];}
        return ans;
    }
};
ACAM map;
char ch[1500000];
char patterns[200][1000];
int main()
{
    //freopen("output.txt","w",stdout);
    while (1){
        map.clear();
        int n;
        scanf("%d",&n);
        if (n==0) return 0;
        for (int i=1;i<=n;++i){
            scanf("%s",patterns[i]);
            map.insert(patterns[i],i);
        }
        map.build();
        scanf("%s",ch);
        int ans=map.query(ch,n);
        printf("%d\n",ans);
        for (int i=1;i<=n;++i)
            if (cnt[i]==ans) printf("%s\n",patterns[i]);
    }
    return 0;

}