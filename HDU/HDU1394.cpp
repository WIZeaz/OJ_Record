#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
struct node{
    int l,r,lc,rc;
    int val;
};
const int N=6000;
const int root=0;
struct SegmentTree{
    //Variables
    int num;    
    node tr[4*N];

    //methods
    void build(int l,int r,int now=root){
        tr[now].l=l; tr[now].r=r; tr[now].val=0;
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
    /*void update(int l,int r,int val,int now=root){
                int mid=(tr[now].l+tr[now].r)>>1;
        if (tr[now].l==l && tr[now].r==r) {
            //change the value you need
            tr[now].val=val; 
            return;
        } else if (pos<=mid) update(pos,val,tr[now].lc);
        else update(pos,val,tr[now].rc);
        //write parent update here
        tr[now].val=tr[tr[now].lc].val+tr[tr[now].rc].val;
    }*/
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
int num[N];
int main()
{
    int n;
    
    while (~scanf("%d",&n)){
        int ans=0;
        //must clean to zero!
        tr.num=0;
        tr.build(1,n);
        for (int i=1;i<=n;++i){
            scanf("%d",&num[i]);
            ans+=tr.query(1,n-num[i]);
            tr.update(n-num[i],1);
        }
        int tmp=ans;
        for (int i=1;i<n;++i){
            tmp+=n-2*num[i]-1;
            ans=(tmp<ans)?tmp:ans;
        }
        printf("%d\n",ans);
    }
    return 0;
}