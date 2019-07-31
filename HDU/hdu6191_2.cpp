#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
#define N 3000000
struct trie{
    struct node{
        int k[2];
    };
    node tr[N];
    int num;
    void clear(){
        //memset(tr,0,sizeof(tr));
        //memset(roots,0,sizeof(roots));
        for (int i=0;i<=num;++i) tr[i].k[0]=tr[i].k[1]=0;
        num=0;
    }
    void insert(int val){
        int now=0;
        for (int i=30;i>=0;--i){
            int t=(1<<i)&val;
            if (t!=0) t=1;
            if (tr[now].k[t]==0){
                ++num;
                tr[now].k[t]=num;
            }
            now=tr[now].k[t];
        }
    }
    int query(int val){
        int now=0;
        int ans=0;
        for (int i=30;i>=0;--i){
            int t=(1<<i)&val;
            if (t!=0) t=1;
            t=1-t;
            if (!tr[now].k[t]) t=1-t;
            ans=(ans<<1)+t;
            now=tr[now].k[t];
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
struct query{
    int x,id;
    query(){}
    query(int _id,int _x){x=_x; id=_id;}
};
vector<query> qu[200001];
int ans[200001];
int ssize[200001];
int hson[200001];
int val[200001];
void dfs1(int x){
    ssize[x]=1;
    hson[x]=0;
    int maxson=0;
    for (int i=list[x];i!=0;i=rds[i].next){
        dfs1(rds[i].v);
        if (ssize[rds[i].v]>maxson) {hson[x]=rds[i].v; maxson=ssize[rds[i].v];}
        ssize[x]+=ssize[rds[i].v];
    }
}
void insertSubtree(int x){
    map.insert(val[x]);
    for (int i=list[x];i!=0;i=rds[i].next){
        insertSubtree(rds[i].v);
    }
}
void dfs2(int x){
    for (int i=list[x];i!=0;i=rds[i].next){
        if (rds[i].v==hson[x]) continue;
        dfs2(rds[i].v);
        map.clear();
    }
    if (hson[x]) dfs2(hson[x]);
    map.insert(val[x]);
    for (int i=list[x];i!=0;i=rds[i].next){
        if (rds[i].v==hson[x]) continue;
        insertSubtree(rds[i].v);
    }
    int len=qu[x].size();
    for (int i=0;i<len;++i){
        ans[qu[x][i].id]=qu[x][i].x^map.query(qu[x][i].x);
    }
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
        for (int i=0;i<n;++i) qu[i].clear();
        for (int i=0;i<q;++i){
            int u,x;
            scanf("%d%d",&u,&x);
            --u;
            qu[u].push_back(query(i,x));
        }
        dfs1(0);
        dfs2(0);
        for (int i=0;i<q;++i) printf("%d\n",ans[i]);
        
    }
}