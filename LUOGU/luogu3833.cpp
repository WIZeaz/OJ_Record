#include <bits/stdc++.h>
using namespace std;
const int N=100050;
const int root=0;
int num=0;
int in[100050],out[100050];
struct edge{
    int v,next;
    edge(){}
};
int edgeNum=0;
edge rds[100050];
int head[100050];
void addedge(int u,int v){
    ++edgeNum;
    rds[edgeNum].v=v;
    rds[edgeNum].next=head[u];
    head[u]=edgeNum;
}
//segment tree
struct node{
    int l,r,lc,rc;
    __int128 val,wval;
};
const int MaxL=18;
int depth[100050];
int f[100050][MaxL+1];
void init(int x,int father,int d){
    ++num;
    in[x]=num;
    depth[x]=d;
    f[x][0]=father;
    for (int i=1;(1<<i)<=d;++i){
        f[x][i]=f[f[x][i-1]][i-1];
    }
    for (int v=head[x];v!=0;v=rds[v].next){
        init(rds[v].v,x,d+1);
    }
    out[x]=num;
}
int getLCA(int u,int v){
    if (depth[u]>depth[v]) swap(u,v);
    int len=depth[v]-depth[u];
    for (int i=0;(1<<i)<=len;++i)
        if ((1<<i)&len) v=f[v][i];
    for (int i=MaxL;i>=0;--i)
        if (f[u][i]!=f[v][i]){u=f[u][i]; v=f[v][i];}
    if (u==v) return u;
    else return f[u][0];
}
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
        tr[now].l=l; tr[now].r=r; tr[now].val=0; tr[now].wval=0;
        if (l<r){
            int mid=(l+r)>>1;
            ++num; tr[now].lc=num;
            ++num; tr[now].rc=num;
            build(l,mid,tr[now].lc);
            build(mid+1,r,tr[now].rc);
        }
    }
    void update(int pos,__int128 val,int dep,int now=root){
        int mid=(tr[now].l+tr[now].r)>>1;
        if (tr[now].l==pos && tr[now].r==pos) {
            //change the value you need
            tr[now].val+=val; 
            tr[now].wval=tr[now].val*(__int128)(dep+1);
            return;
        } else if (pos<=mid) update(pos,val,dep,tr[now].lc);
        else update(pos,val,dep,tr[now].rc);
        //write parent update here
        tr[now].val=tr[tr[now].lc].val+tr[tr[now].rc].val;
        tr[now].wval=tr[tr[now].lc].wval+tr[tr[now].rc].wval;
    }
    __int128 query(int l,int r,int now=root){
        if (tr[now].l==l && tr[now].r==r) return tr[now].val;
        else {
            int mid=(tr[now].l+tr[now].r)>>1;
            if (r<=mid) return query(l,r,tr[now].lc);
            else if (l>mid) return query(l,r,tr[now].rc);
            else return query(l,mid,tr[now].lc)+query(mid+1,r,tr[now].rc);
        }
    }
    __int128 queryw(int l,int r,int now=root){
        if (tr[now].l==l && tr[now].r==r) return tr[now].wval;
        else {
            int mid=(tr[now].l+tr[now].r)>>1;
            if (r<=mid) return queryw(l,r,tr[now].lc);
            else if (l>mid) return queryw(l,r,tr[now].rc);
            else return queryw(l,mid,tr[now].lc)+queryw(mid+1,r,tr[now].rc);
        }
    }

};
Segment_Tree tr;
inline void print(__int128 x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)
        print(x/10);
    putchar(x%10+'0');
}
int main()
{
    int n,m;
    memset(head,0,sizeof(head));
    scanf("%d",&n);
    for (int i=1;i<n;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        ++u; ++v;
        if (u>v) swap(u,v);
        addedge(u,v);
    }
    tr.setRange(1,n);
    init(1,1,0);
    scanf("%d",&m);
    for (int i=1;i<=m;++i){
        char ch;
        int u,v,w;
        scanf("%s%d",&ch,&u);
        ++u;
        if (ch=='A'){
            scanf("%d%d",&v,&w);
            ++v;
            tr.update(in[u],w,depth[u]);
            tr.update(in[v],w,depth[v]);
            int l=getLCA(u,v);
            tr.update(in[l],-w,depth[l]);
            if (l!=1) tr.update(f[l][0],-w,depth[f[l][0]]);
        } else{
            __int128 tmp=tr.queryw(in[u],out[u])-tr.query(in[u],out[u])*(__int128)depth[u];
            print(tmp);
            printf("\n");
        }
    }
}