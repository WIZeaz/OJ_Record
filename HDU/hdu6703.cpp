#include <iostream>
using namespace std;
struct segmentTree{
    struct node{
        int lc,rc,l,r;
        int val;
    } tr[500001];
    int num;
    void setRange(int l,int r){
        num=0;
        build(l,r,0);
    }
    void build(int l,int r,int now=0){
        tr[now].l=l; tr[now].r=r; tr[now].val=0;
        if (l<r){
            int mid=l+r>>1;
            tr[now].lc=++num;
            tr[now].rc=++num;
            build(l,mid,tr[now].lc);
            build(mid+1,r,tr[now].rc);
        }
    }
    void update(int pos,int val,int now=0){
        if (tr[now].l==tr[now].r){
            tr[now].val=val;
        } else {
            int mid=tr[now].l+tr[now].r>>1;
            if (pos<=mid) update(pos,val,tr[now].lc);
            else update(pos,val,tr[now].rc);
            tr[now].val=max(tr[tr[now].lc].val,tr[tr[now].rc].val);
        }
    }
    int query(int l,int r,int k,int now=0){
        if (tr[now].val<=k) return -1;
        if (tr[now].l==tr[now].r && tr[now].val>k){
            return tr[now].l;
        }
        int mid=tr[now].l+tr[now].r>>1;
        if (r<=mid) return query(l,r,k,tr[now].lc);
        else if (l>mid) return query(l,r,k,tr[now].rc);
        else {
            int t=query(l,mid,k,tr[now].lc);
            if (t!=-1) return t;
            return query(mid+1,r,k,tr[now].rc);
        }
    }

};
segmentTree tr;
int a[100001];
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        int n,m;
        scanf("%d%d",&n,&m);
        tr.setRange(1,n);
        for (int i=1;i<=n;++i){
            int t;
            scanf("%d",&a[i]);
            tr.update(a[i],i);
        }
        int last=0;
        for (int i=0;i<m;++i){
            int op;
            scanf("%d",&op);
            if (op==1){
                int pos;
                scanf("%d",&pos);
                pos^=last;
                tr.update(a[pos],n+1);
            } else {
                int r,k;
                scanf("%d%d",&r,&k);
                r^=last; k^=last;
                last=tr.query(k,n,r);
                if (last==-1) last=n+1;
                printf("%d\n",last);
            }
        }
    }
}