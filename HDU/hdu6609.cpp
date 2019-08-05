#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int a[200001];
int b[200001];
struct Segment_Tree{
    //constants and innerclass
    struct node{
        int l,r,lc,rc;
        long long val,cnt;
    };
    static const int N=200000;
    static const int root=0;

    //variables
    int num;    
    node tr[2*N];

    //methods
    void setRange(int l,int r,int now=root){
        num=0;
        build(l,r,now);
    }
    void build(int l,int r,int now){
        tr[now].l=l; tr[now].r=r; tr[now].val=0; tr[now].cnt=0;
        if (l<r){
            int mid=(l+r)>>1;
            ++num; tr[now].lc=num;
            ++num; tr[now].rc=num;
            build(l,mid,tr[now].lc);
            build(mid+1,r,tr[now].rc);
        } 
    }


    void pushup(node &f,node &lc,node &rc){
        f.val=lc.val+rc.val;
        f.cnt=lc.cnt+rc.cnt;
    }

    //warning: don't invoke both update and updateR in single segment tree, it may cause error
    void update(int pos,int val,int now=root){
        int mid=(tr[now].l+tr[now].r)>>1;
        if (tr[now].l==tr[now].r) {
            tr[now].cnt+=val; 
            tr[now].val=tr[now].cnt*b[tr[now].l];
            return;
        } else if (pos<=mid) update(pos,val,tr[now].lc);
        else update(pos,val,tr[now].rc);
        //write parent update here
        pushup(tr[now],tr[tr[now].lc],tr[tr[now].rc]);
    }

    int query(int m,int now=root){
        if (tr[now].l==tr[now].r){
            if (tr[now].val<=m) return tr[now].cnt;
            return m/b[tr[now].l];
        }
        if (tr[now].val<=m) return tr[now].cnt;
        else{
            if (tr[tr[now].lc].val<=m) return tr[tr[now].lc].cnt+query(m-tr[tr[now].lc].val,tr[now].rc);
            else return query(m,tr[now].lc);
        }
    }
};

Segment_Tree tr;
int main(){
    int q;
    scanf("%d",&q);
    while (q--){
        int n,m;
        scanf("%d%d",&n,&m);
        for (int i=0;i<n;++i){
            scanf("%d",&a[i]);
            b[i]=a[i];
        }
        //cout<<n<<' '<<m<<endl;
        sort(b,b+n);
        int len=unique(b,b+n)-b;
        tr.setRange(0,len-1);
        for (int i=0;i<n;++i){
            int k=tr.query(m-a[i]);
            printf("%d ",i-k);
            int t=lower_bound(b,b+len,a[i])-b;
            tr.update(t,1);
        }
        printf("\n");

    }
}