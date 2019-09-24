/*
Suffix-Automation author:WIZeaz
luogu3804
*/
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
struct edge{
    int v,next;
    edge(){}
    edge(int _v,int _next){v=_v; next=_next;}
} rds[2000001];
int head[2000001];

int ecnt=0;
void addedge(int u,int v){
    rds[++ecnt]=edge(v,head[u]);
    head[u]=ecnt;
}
struct SAM{
    struct node{
        int parent,next[26],len;
        int cnt;
        int ans[2];
    };
    node tr[2000001];
    bool vis[2000001];
    int last=0;
    int num=0;
    void init(){
        last=0;
        num=0;
        tr[0].parent=-1;
    }
    void add(char ch){
        int p=last;
        int t=ch-'a';
        int now=++num;
        tr[now].len=tr[last].len+1;
        tr[now].cnt=1;
        while (p!=-1 && tr[p].next[t]==0){
            tr[p].next[t]=now; 
            p=tr[p].parent;
        }
        if (p!=-1){
            int q=tr[p].next[t];
            if (tr[p].len+1==tr[q].len){
                tr[num].parent=q;
            } else {
                tr[++num].parent=tr[q].parent;
                memcpy(tr[num].next,tr[q].next,sizeof(tr[num].next));
                tr[num].len=tr[p].len+1;
                while (p!=-1 && tr[p].next[t]==q){
                    tr[p].next[t]=num;
                    p=tr[p].parent;
                }
                tr[now].parent=tr[q].parent=num;
            }
        } else tr[now].parent=0;
        last=now;
    }
    void getSons(){
        for (int i=1;i<=num;++i)
            addedge(tr[i].parent,i);
    }
    void dfs(int x){
        //tr[x].cnt=0;
        for (int i=head[x];i!=0;i=rds[i].next){
            dfs(rds[i].v);
            tr[x].cnt+=tr[rds[i].v].cnt;
        }
        
    }
    void dfs2(int x){
        if (vis[x]) return;
        tr[x].ans[0]=1;
        tr[x].ans[1]=tr[x].cnt;
        vis[x]=true;
        for (int i=0;i<26;++i)
            if (tr[x].next[i]){
                dfs2(tr[x].next[i]);
                tr[x].ans[0]+=tr[tr[x].next[i]].ans[0];
                tr[x].ans[1]+=tr[tr[x].next[i]].ans[1];
            }
    }
    void getAns(int k,int t){
        memset(vis,false,sizeof(vis));
        getSons();
        dfs(0);
        dfs2(0);
        int now=0;
        int size=(t)?tr[now].cnt:1;
        k+=size;
        if (k>tr[now].ans[t]){
            puts("-1");
            return;
        }
        while (k>size){
            k-=size;
            for (int i=0;i<26;++i){
                if (!tr[now].next[i]) continue;
                if (tr[tr[now].next[i]].ans[t]<k) k-=tr[tr[now].next[i]].ans[t];
                else {
                    now=tr[now].next[i];
                    size=(t)?tr[now].cnt:1;
                    putchar('a'+i);
                    break;
                }
            }
        }
    }
};
SAM sam;
char str[2000001];
int main(){
    scanf("%s",str);
    sam.init();
    int len=strlen(str);
    for (int i=0;i<len;++i) sam.add(str[i]);
    int k,t;
    scanf("%d%d",&t,&k);
    sam.getAns(k,t);
}