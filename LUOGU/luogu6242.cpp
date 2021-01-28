#include <bits/stdc++.h>
using namespace std;
int a[500001];

struct SegmentTree{
    //constants and innerclass
    struct node{
        int l,r,lc,rc;
        long long sum,maxEl,maxCnt,secEl;
        long long hMaxEl;
        long long add1,add2;
        long long hAdd1,hAdd2;
    };
    static const int N=500000;
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
        tr[now].l=l; tr[now].r=r; 
        if (l==r){
            tr[now].sum=a[l];
            tr[now].maxEl=a[l];
            tr[now].secEl=-1e18;
            tr[now].maxCnt=1;
            tr[now].add1=tr[now].add2=tr[now].hAdd1=tr[now].hAdd2=0;
            tr[now].hMaxEl=a[l];
            return;
        }
        int mid=(l+r)>>1;
        ++num; tr[now].lc=num;
        ++num; tr[now].rc=num;
        build(l,mid,tr[now].lc);
        build(mid+1,r,tr[now].rc);
        pushup(tr[now],tr[tr[now].lc],tr[tr[now].rc]);
        
    }
    void lazyupdate(node &x, long long add1,long long add2,long long hAdd1,long long hAdd2){
        //set flag and update
        //if (add1==0 && add2==0 && hAdd==0) return;
        x.hAdd1=max(x.hAdd1,x.add1+hAdd1);
        x.hAdd2=max(x.hAdd2,x.add2+hAdd2);
        x.add1+=add1;
        x.add2+=add2;
        
        x.hMaxEl=max(x.hMaxEl,x.maxEl+hAdd1);
        x.sum+=add1*x.maxCnt+add2*(x.r-x.l-x.maxCnt+1);
        x.maxEl+=add1;
        x.secEl+=add2;
    }
    void pushdown(node &f,node &lc, node &rc){
        //transfer flag and update
        long long tMax=max(lc.maxEl,rc.maxEl);
        if (tMax==lc.maxEl) lazyupdate(lc,f.add1,f.add2,f.hAdd1,f.hAdd2);
        else lazyupdate(lc,f.add2,f.add2,f.hAdd2,f.hAdd2);
        if (tMax==rc.maxEl) lazyupdate(rc,f.add1,f.add2,f.hAdd1,f.hAdd2);
        else lazyupdate(rc,f.add2,f.add2,f.hAdd2,f.hAdd2);

        f.add1=f.add2=f.hAdd1=f.hAdd2=0;
    }
    void pushup(node &f,node &lc,node &rc){
        if (lc.maxEl>rc.maxEl){
            f.maxEl=lc.maxEl;
            f.maxCnt=lc.maxCnt;
            f.secEl=max(rc.maxEl,lc.secEl);
        } else if (lc.maxEl<rc.maxEl){
            f.maxEl=rc.maxEl;
            f.maxCnt=rc.maxCnt;
            f.secEl=max(lc.maxEl,rc.secEl);
        } else {
            f.maxEl=lc.maxEl;
            f.maxCnt=lc.maxCnt+rc.maxCnt;
            f.secEl=max(lc.secEl,rc.secEl);
        }
        f.sum=lc.sum+rc.sum;
        f.hMaxEl=max(lc.hMaxEl,rc.hMaxEl);
    }

    void add(int l,int r,long long val,int now=root){
        
        if (tr[now].l==l && tr[now].r==r) {
            //lazy operation
            lazyupdate(tr[now],val,val,val,val);
            return;
        } else {
            //Pushdown here
            pushdown(tr[now],tr[tr[now].lc],tr[tr[now].rc]);

            int mid=(tr[now].l+tr[now].r)>>1;
            if (r<=mid) add(l,r,val,tr[now].lc);
            else if (l>mid) add(l,r,val,tr[now].rc);
            else {
                add(l,mid,val,tr[now].lc);
                add(mid+1,r,val,tr[now].rc);
            }
            //write parent update here
            pushup(tr[now],tr[tr[now].lc],tr[tr[now].rc]);
        }
    }
    void doMin(int l,int r,long long val,int now=root){
        if (tr[now].l==l && tr[now].r==r){
            if (val>=tr[now].maxEl) return;
            if (val>tr[now].secEl){
                lazyupdate(tr[now],val-tr[now].maxEl,0,val-tr[now].maxEl,0);
                return;
            }
        }
        pushdown(tr[now],tr[tr[now].lc],tr[tr[now].rc]);
        int mid=(tr[now].l+tr[now].r)>>1;
        if (r<=mid) doMin(l,r,val,tr[now].lc);
        else if (l>mid) doMin(l,r,val,tr[now].rc);
        else {
            doMin(l,mid,val,tr[now].lc);
            doMin(mid+1,r,val,tr[now].rc);
        }
        //write parent update here
        pushup(tr[now],tr[tr[now].lc],tr[tr[now].rc]);
    }
    node query(int l,int r,int now=root){
        if (tr[now].l==l && tr[now].r==r) return tr[now];
        else {
            pushdown(tr[now],tr[tr[now].lc],tr[tr[now].rc]);
            int mid=(tr[now].l+tr[now].r)>>1;
            if (r<=mid) return query(l,r,tr[now].lc);
            else if (l>mid) return query(l,r,tr[now].rc);
            else{
                node lNode=query(l,mid,tr[now].lc);
                node rNode=query(mid+1,r,tr[now].rc);
                node parentNode;
                pushup(parentNode,lNode,rNode);
                return parentNode;
            } 
        }
    }

};
SegmentTree tr;
int main(){
    int n,m;
    //freopen("P6242_1.in","r",stdin);
    //freopen("answer.out","w",stdout);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i) scanf("%d",&a[i]);
    tr.setRange(1,n);
    while (m--){
        int op,l,r;
        scanf("%d%d%d",&op,&l,&r);
        if (op==1){
            int k;
            scanf("%d",&k);
            tr.add(l,r,k);
        } else if (op==2){
            int k;
            scanf("%d",&k);
            tr.doMin(l,r,k);
        } else {
            auto ansNode=tr.query(l,r);
            if (op==3) printf("%lld\n",ansNode.sum);
            else if (op==4) printf("%lld\n",ansNode.maxEl);
            else printf("%lld\n",ansNode.hMaxEl);
        }
    }
}