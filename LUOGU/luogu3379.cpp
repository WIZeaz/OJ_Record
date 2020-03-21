#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define MAXD 19
//standard adjacent table definition
struct edge{
    int v,next;
    edge(){}
    edge(int _v,int _next){v=_v; next=_next;}
};
edge edges[1000001];
int num,head[500001];
void addedge(int u,int v){
    edges[++num]=edge(v,head[u]);
    head[u]=num;
}

int f[500001][21];
int depth[500001];
void init(int x,int father,int d){
    depth[x]=d;
    f[x][0]=father;
    for (int i=1;(1<<i)<=d;++i){
        f[x][i]=f[f[x][i-1]][i-1];
    }
    for (int v=head[x];v!=0;v=edges[v].next){
        if (edges[v].v==father) continue;
        init(edges[v].v,x,d+1);
    }
        
}
int getLCA(int u,int v){
    if (depth[u]>depth[v]) swap(u,v);
    int len=depth[v]-depth[u];
    for (int i=0;(1<<i)<=len;++i)
        if ((1<<i)&len) v=f[v][i];
    for (int i=MAXD;i>=0;--i)
        if (f[u][i]!=f[v][i]){u=f[u][i]; v=f[v][i];}
    if (u==v) return u;
    else return f[u][0];
}
int main()
{
    int n,u,v;
    int m,s;
    scanf("%d%d%d",&n,&m,&s);
    memset(head,0,sizeof(head));
    memset(f,0,sizeof(f));
    num=0;
    for (int i=0;i<n-1;++i){
        scanf("%d%d",&u,&v);
        addedge(u,v);
        addedge(v,u);
    }
    init(s,s,0);
    for (int i=0;i<m;++i){
        scanf("%d%d",&u,&v);
        printf("%d\n",getLCA(u,v));
    }
}