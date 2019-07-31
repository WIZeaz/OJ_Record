#include <iostream>
#include <cstring>
#include <string>
using namespace std;
int a[100001];
#define L 45
struct Segment_Tree{
    struct node{
        int l,r,lc,rc;
        int val[L];
    };
    static const int N=100000;
    static const int root=0;
    //variables
    int num;    
    node tr[2*N];

    //methods
    void setRange(int l,int r,int now=root){
        num=0;
        build(l,r,now);
    }
    void merge(node &l,node &r,node& f){
        int i=0;
        int j=0;
        for (int c=0;c<L;++c){
            if (i>=L) {f.val[c]=r.val[j]; ++j;}
            else if (j>=L) {f.val[c]=l.val[i]; ++i;}
            else if (l.val[i]<r.val[j]) {f.val[c]=r.val[j]; ++j;}
            else {f.val[c]=l.val[i]; ++i;}
        }
    }
    void build(int l,int r,int now){
        tr[now].l=l; tr[now].r=r; memset(tr[now].val,0,sizeof(tr[now].val));
        //for (int i=0;i<50;++i) tr[now].val[i]=0;
        if (l<r){
            int mid=(l+r)>>1;
            ++num; tr[now].lc=num;
            ++num; tr[now].rc=num;
            build(l,mid,tr[now].lc);
            build(mid+1,r,tr[now].rc);
            merge(tr[tr[now].lc],tr[tr[now].rc],tr[now]);
        } else {
            tr[now].val[0]=a[l];
        }
    }
    node query(int l,int r,int now=root){
        if (tr[now].l==l && tr[now].r==r) return tr[now];
        else {
            int mid=(tr[now].l+tr[now].r)>>1;
            if (r<=mid) return query(l,r,tr[now].lc);
            else if (l>mid) return query(l,r,tr[now].rc);
            else{
                node lc= query(l,mid,tr[now].lc);
                node rc=query(mid+1,r,tr[now].rc);
                node f;
                f.l=l; f.r=r; merge(lc,rc,f);
                return f;
            }
        }
    }

};
Segment_Tree tr;

int main()
{
    int n,q;
    while (~scanf("%d%d",&n,&q)){
        for (int i=1;i<=n;++i) scanf("%d",&a[i]);
        tr.setRange(1,n);
        while (q--){
            int l,r;
            scanf("%d%d",&l,&r);
            auto tmp=tr.query(l,r);
        
            long long ans=-1;
            for (int i=0;i<L-2;++i){
                //printf("%d ",tmp.val[i]);
                if ((long long)tmp.val[i]<(long long)tmp.val[i+1]+(long long)tmp.val[i+2]){
                    ans=(long long)tmp.val[i]+(long long)tmp.val[i+1]+(long long)tmp.val[i+2];
                    break;
                }

            }
            printf("%lld\n",ans);
        }
    }

}