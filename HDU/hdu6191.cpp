#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
#define N 3500000
struct trie{
    struct node{
        int k[2];
        int c;
    };
    node tr[N];
    int vernum=0;
    int roots[N];
    int num;
    void clear(){
        //memset(tr,0,sizeof(tr));
        //memset(roots,0,sizeof(roots));
        for (int i=0;i<=num;++i) tr[i].c=tr[i].k[0]=tr[i].k[1]=0;
        vernum=0;
        num=0;
    }
    void insert(int val,int version){
        roots[++vernum]=++num;
        int now=num;
        int now2=roots[version];
        tr[now]=tr[now2];
        for (int i=30;i>=0;--i){
            int t=(1<<i)&(val);
            if (t!=0) t=1;
            ++num;
            tr[now].k[t]=num;
            if (tr[now2].k[t]){ tr[num]=tr[tr[now2].k[t]]; }
            tr[num].c+=1;
            now=tr[now].k[t]; now2=tr[now2].k[t]; 
        }
    }
    int query(int val,int l,int r){
        int nowr=roots[r];
        int nowl=roots[l-1];
        int ans=0;
        for (int i=30;i>=0;--i){
            int t=(1<<i)&(val);
            if (t!=0) t=1;
            t=1-t;
            if (tr[tr[nowr].k[t]].c-tr[tr[nowl].k[t]].c<=0) t=1-t;
            ans=(ans<<1)+t;
            nowr=tr[nowr].k[t]; nowl=tr[nowl].k[t];   
        }
        return ans;
    }
};
trie map;
struct path{
    int v,next;
    path(int _v,int _next){v=_v; next=_next;}
    path(){}
};
path rds[200001];
int list[200001];
int num=0;
void addedge(int u,int v){
    rds[++num]=path(v,list[u]);
    list[u]=num;
}
int first[200001],last[200001],timestamp;
int val[200001];
void dfs(int x){
    first[x]=++timestamp;
    map.insert(val[x],map.vernum);
    for (int i=list[x];i!=0;i=rds[i].next){
        int v=rds[i].v;
        dfs(v);
    }
    last[x]=timestamp;
}
int main()
{
    int n,q;
    while (~scanf("%d%d",&n,&q)){
        map.clear();
        memset(list,0,sizeof(list));
        num=0;

        for (int i=0;i<n;++i){
            scanf("%d",&val[i]);
        }
        for (int i=1;i<n;++i){
            int f;
            scanf("%d",&f);
            --f;
            addedge(f,i);
        }
        timestamp=0;
        dfs(0);
        for (int i=0;i<q;++i){
            int u,x;
            scanf("%d%d",&u,&x);
            --u;
            printf("%d\n",x^map.query(x,first[u],last[u]));
        }
    }
}