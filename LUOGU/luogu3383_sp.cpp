#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
struct edge{
    int v,next;
} rds[100001];
int num=0;
int head[100001];
void addedge(int u,int v){
    rds[num].v=v;
    rds[num].next=head[u];
    head[u]=num;
    ++num;
}
struct trnode{
    int top,f,size,id,idout,hson,dep;
} trnds[100001];
int dfn[100001];
int cnt=0;
void dfs1(int x,int f,int d){
    trnds[x].f=f; trnds[x].size=1; trnds[x].hson=0; trnds[x].dep=d;
    for (int i=head[x];i!=0;i=rds[i].next)
        if (rds[i].v!=f){
            dfs1(rds[i].v,x,d+1);
            trnds[x].size+=trnds[rds[i].v].size;
            if (trnds[rds[i].v].size>trnds[trnds[x].hson].size) trnds[x].hson=rds[i].v;
        }
}
void dfs2(int x,int top){
    dfn[++cnt]=x;
    trnds[x].id=cnt;
    trnds[x].top=top;
    if (trnds[x].hson!=0) dfs2(trnds[x].hson,top);
    for (int i=head[x];i!=0;i=rds[i].next)
        if (rds[i].v!=trnds[x].f && rds[i].v!=trnds[x].hson){
            dfs2(rds[i].v,rds[i].v);
        }
    trnds[x].idout=cnt;
}



/*Segment Tree*/
const int N=100000;
const int root=0;
struct node{
    int l,r,lc,rc;
    long long val,cover;
};
struct Segment_Tree{
    //constants

    //clarification
    int num;    
    node tr[2*N];

    //methods
    void setRange(int l,int r,int now=root){
        num=0;
        build(l,r,now);
    }
    void build(int l,int r,int now){
        tr[now].l=l; tr[now].r=r; tr[now].val=0; tr[now].cover=0;
        if (l<r){
            int mid=(l+r)>>1;
            ++num; tr[now].lc=num;
            ++num; tr[now].rc=num;
            build(l,mid,tr[now].lc);
            build(mid+1,r,tr[now].rc);
        }
    }
    void update(int l,int r,long long val,int now=root){
        int mid=(tr[now].l+tr[now].r)>>1;
        if (tr[now].l==l && tr[now].r==r) {
            //change the value you need
            if (l==r) tr[now].val+=val;
            else {
                tr[now].cover+=val;
                tr[now].val=tr[tr[now].lc].val+tr[tr[now].rc].val+tr[now].cover*(tr[now].r-tr[now].l+1);
            }
            return;
        } else{
            if (r<=mid) update(l,r,val,tr[now].lc);
            else if (l>mid) update(l,r,val,tr[now].rc);
            else{
                update(l,mid,val,tr[now].lc);
                update(mid+1,r,val,tr[now].rc);
            }
            tr[now].val=tr[tr[now].lc].val+tr[tr[now].rc].val+tr[now].cover*(tr[now].r-tr[now].l+1);
        }
    }
    long long query(int l,int r,int now=root){
        if (tr[now].l==l && tr[now].r==r) return tr[now].val;
        else {
            int mid=(tr[now].l+tr[now].r)>>1;
            if (r<=mid) return query(l,r,tr[now].lc)+tr[now].cover*(r-l+1);
            else if (l>mid) return query(l,r,tr[now].rc)+tr[now].cover*(r-l+1);
            else return query(l,mid,tr[now].lc)+query(mid+1,r,tr[now].rc)+tr[now].cover*(r-l+1);
        }
    }

};
Segment_Tree tr;

void change(int u,int v,int w){
    while (trnds[u].top!=trnds[v].top){
        if (trnds[trnds[u].top].dep>trnds[trnds[v].top].dep){tr.update(trnds[trnds[u].top].id,trnds[u].id,w); u=trnds[trnds[u].top].f; }
        else{tr.update(trnds[trnds[v].top].id,trnds[v].id,w); v=trnds[trnds[v].top].f; }
    }
    if (trnds[u].dep<trnds[v].dep) tr.update(trnds[u].id,trnds[v].id,w);
    else tr.update(trnds[v].id,trnds[u].id,w);
}
int main()
{
    int n,m;
    scanf("%d",&n);
    memset(head,0,sizeof(head));
    num=1;
    for (int i=0;i<n-1;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        ++u; ++v;
        addedge(u,v);
    }
    tr.setRange(1,n);
    dfs1(1,1,0);
    dfs2(1,1);
    scanf("%d",&m);
    for (int i=1;i<=m;++i){
        char ch;
        int u,v,w;
        scanf("%s%d",&ch,&u);
        ++u;
        if (ch=='A'){
            scanf("%d%d",&v,&w);
            ++v;
            change(u,v,w);
        } else{
            printf("%lld\n",tr.query(trnds[u].id,trnds[u].idout));
        }
    }
}