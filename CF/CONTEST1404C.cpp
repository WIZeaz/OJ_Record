#include <bits/stdc++.h>
using namespace std;
int lowbit(int x){return x&(-x);}
struct TreeArray{
    int n,st;
    int a[500001];
    void setRange(int N) {
        n=N;
        st=1;
        while ((st<<1)<=n) st<<=1;
    }
    void clear() {memset(a,0,sizeof(a));}
    void add(int pos,int val){
        for (int i=pos;i<=n;i+=lowbit(i)) a[i]+=val;
    }
    int query(int pos){
        int rnt=0;
        for (int i=pos;i>0;i-=lowbit(i)) rnt+=a[i];
        return rnt;
    }
    int search(int k){
        int ret=0;
        for (int i=st;i>0;i>>=1)
            if ((ret|i)<=n && a[(ret|i)]>=k){
                ret|=i;
                k-=a[ret];
            }
        return ret;
    }
};
TreeArray tr;

struct Query{
    int l,r,id;
} qu[500001];
int ans[500001];
int a[500001];
 //position of last >=x
int search(int l,int r,int x){
    --l; ++r;
    while (l+1<r){
        int mid=l+r>>1;
        if (tr.query(mid)>=x) l=mid;
        else r=mid;
    }
    return l;
}/* 
void out(int l,int r){
    for (int i=l;i<=r;++i) printf("%d ",tr.query(i));
    puts("");
}  */
int main(){
    int n,q;
    scanf("%d%d",&n,&q);
    for (int i=1;i<=n;++i) scanf("%d",&a[i]);
    tr.setRange(n+1);
    for (int i=0;i<q;++i){
        int x,y;
        scanf("%d%d",&x,&y);
        qu[i]={x+1,n-y,i};
        // printf("%d,%d\n",x+1,n-y);
    }
    sort(qu,qu+q,[](const Query &a,const Query &b){
        return a.r<b.r;
    });
    int j=1;
    for (int i=0;i<q;++i){
        //printf("i=%d query={%d,%d}\n",i,qu[i].l,qu[i].r);
        while (j<=n && qu[i].r>=j){
            int x=j-a[j];
            // printf("j=%d x=%d pos=%d\n",j,x,pos);
            if (x>=0 && x<=tr.a[1]){
                //out(1,n);
                int pos=min(tr.search(x),j);
                //printf("pos=%d\n",pos);
                tr.add(1,1);
                tr.add(pos+1,-1);
            }
            ++j;
        }
        ans[qu[i].id]=tr.query(qu[i].l);
    }
    
    for (int i=0;i<q;++i) printf("%d\n",ans[i]);
}
