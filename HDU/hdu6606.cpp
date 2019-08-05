#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
long long a[200001];
long long b[200001];
int len;
int n,k;
struct Segment_Tree{
    //constants and innerclass
    struct node{
        int l,r,lc,rc;
        int max;
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
        tr[now].l=l; tr[now].r=r; tr[now].max=-99999999;
        if (l<r){
            int mid=(l+r)>>1;
            ++num; tr[now].lc=num;
            ++num; tr[now].rc=num;
            build(l,mid,tr[now].lc);
            build(mid+1,r,tr[now].rc);
        } 
    }


    void pushup(node &f,node &lc,node &rc){
        f.max=max(lc.max,rc.max);
    }

    //warning: don't invoke both update and updateR in single segment tree, it may cause error
    void update(int pos,int val,int now=root){
        int mid=(tr[now].l+tr[now].r)>>1;
        if (tr[now].l==tr[now].r) {
            tr[now].max=max(tr[now].max,val); 
            return;
        } else if (pos<=mid) update(pos,val,tr[now].lc);
        else update(pos,val,tr[now].rc);
        //write parent update here
        pushup(tr[now],tr[tr[now].lc],tr[tr[now].rc]);
    }

    int query(int l,int r,int now=root){
        if (tr[now].l==l && tr[now].r==r) return tr[now].max;
        else {
            int mid=(tr[now].l+tr[now].r)>>1;
            if (r<=mid) return query(l,r,tr[now].lc);
            else if (l>mid) return query(l,r,tr[now].rc);
            else return max(query(l,mid,tr[now].lc),query(mid+1,r,tr[now].rc));
        }
    }
};
Segment_Tree tr;

bool check(long long m){
    tr.setRange(0,len-1);
    int tmp=lower_bound(b,b+len,0)-b;
    tr.update(tmp,0);
    for (int i=1;i<=n;++i){
        int t=lower_bound(b,b+len,a[i])-b;
        int t2=lower_bound(b,b+len,a[i]-m)-b;
        if (t2<=len-1) tr.update(t,tr.query(t2,len-1)+1);
        //else break;
    }
    if (tr.query(0,len-1)>=k) return true;
    return false;
}

int main(){
    int T;
    scanf("%d",&T);
    while (T--){

        scanf("%d%d",&n,&k);
        a[0]=0;
        b[0]=0;
        for (int i=1;i<=n;++i){
            scanf("%lld",&a[i]);
            a[i]+=a[i-1];
            b[i]=a[i];
        }
        sort(b,b+n+1);
        len=unique(b,b+n+1)-b;

        long long l=0x8000000000000000;
        long long r=0x7fffffffffffffff;
        while (l+1<r){
            long long mid=l+r>>1;
            if (check(mid)) r=mid;
            else l=mid;
        }
        printf("%lld\n",r);
    }
}