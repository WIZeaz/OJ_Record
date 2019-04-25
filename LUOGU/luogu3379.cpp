#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
struct edge{
    int v,next;
} rds[1000001];
int num;
int head[500001];
void addedge(int u,int v){
    rds[num].v=v;
    rds[num].next=head[u];
    head[u]=num;
    ++num;
}
int f[500001][21];
int depth[500001];
int MaxL=20;
void init(int x,int father,int d){
    depth[x]=d;
    f[x][0]=father;
    for (int i=1;(1<<i)<=d;++i){
        f[x][i]=f[f[x][i-1]][i-1];
    }
    for (int v=head[x];v!=0;v=rds[v].next)
        if (rds[v].v!=father){
            init(rds[v].v,x,d+1);
        }
}
int getLCA(int u,int v){
    if (depth[u]>depth[v]){
        int t=u; u=v; v=t;
    }
    int len=depth[v]-depth[u];
    for (int i=0;(1<<i)<=len;++i)
        if ((1<<i)&len) v=f[v][i];
    for (int i=MaxL;i>=0;--i)
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
    num=1;
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