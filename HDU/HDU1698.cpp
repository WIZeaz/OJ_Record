#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
struct node{
    int l,r,lc,rc;
    int cover;
    int val;
};
const int N=250000;
const int root=0;
struct SegmentTree{
    //Variables
    int num;    
    node tr[4*N];

    //methods
    void clear(){
        num=0;
    }
    void build(int l,int r,int now=root){
        tr[now].l=l; tr[now].r=r; tr[now].val=0; tr[now].cover=0;
        if (l<r){
            int mid=(l+r)>>1;
            ++num; tr[now].lc=num;
            ++num; tr[now].rc=num;
            build(l,mid,tr[now].lc);
            build(mid+1,r,tr[now].rc);
        }
    }
    void update(int pos,int val,int now=root){
        int mid=(tr[now].l+tr[now].r)>>1;
        if (tr[now].l==pos && tr[now].r==pos) {
            //change the value you need
            tr[now].val=val; 
            return;
        } else if (pos<=mid) update(pos,val,tr[now].lc);
        else update(pos,val,tr[now].rc);
        //write parent update here
        tr[now].val=tr[tr[now].lc].val+tr[tr[now].rc].val;
    }
    void _update(int l,int r,int val,int now=root){
        if (tr[now].l==l && tr[now].r==r){
            tr[now].cover=val;
            tr[now].val=val*(r-l+1);
        } else {
            if (tr[now].cover==val) return;
            else if (tr[now].cover!=-1){
                tr[tr[now].lc].cover=tr[now].cover;
                tr[tr[now].lc].val=(tr[tr[now].lc].r-tr[tr[now].lc].l+1)*tr[tr[now].lc].cover;
                tr[tr[now].rc].cover=tr[now].cover;
                tr[tr[now].rc].val=(tr[tr[now].rc].r-tr[tr[now].rc].l+1)*tr[tr[now].rc].cover;
                tr[now].cover=-1;
            }
            int mid=(tr[now].l+tr[now].r)>>1;
            if (r<=mid) _update(l,r,val,tr[now].lc);
            else if (l>mid) _update(l,r,val,tr[now].rc);
            else{
                _update(l,mid,val,tr[now].lc);
                _update(mid+1,r,val,tr[now].rc);
            }
            //write parent update here
            tr[now].val=tr[tr[now].lc].val+tr[tr[now].rc].val;
        }
    }
    int query(int l,int r,int now=root){
        if (tr[now].l==l && tr[now].r==r) return tr[now].val;
        else {
            int mid=(tr[now].l+tr[now].r)>>1;
            if (r<=mid) return query(l,r,tr[now].lc);
            else if (l>mid) return query(l,r,tr[now].rc);
            else return query(l,mid,tr[now].lc)+query(mid+1,r,tr[now].rc);
        }
    }

};
SegmentTree tr;
int main()
{
    int n,T;
    scanf("%d",&T);
    for (int Case=1;Case<=T;++Case){
        int q;
        scanf("%d%d",&n,&q);
        tr.num=0;
        tr.build(1,n);
        tr._update(1,n,1);
        for (int i=1;i<=q;++i){
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            tr._update(a,b,c);
        }
        printf("Case %d: The total value of the hook is %d.\n",Case,tr.query(1,n));
    }
    return 0;
}