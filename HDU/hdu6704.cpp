#include <bits/stdc++.h>
using namespace std;
#define STRMAXLEN 100010
int rnk[STRMAXLEN];
int buckets[STRMAXLEN];
int sa[STRMAXLEN]; //the number of rank i number,start from 1
int tsa[STRMAXLEN];
int height[STRMAXLEN];
int bucketSort(int len,int charnum,int k){
    for (int i=0;i<=charnum;++i) buckets[i]=0;
    for (int i=0;i<len;++i) buckets[rnk[i]]++;
    for (int i=1;i<=charnum;++i) buckets[i]+=buckets[i-1];
    for (int i=len;i>=1;--i) sa[buckets[rnk[tsa[i]]]--]=tsa[i];
    swap(tsa,rnk); //sheng shu zu
    charnum=1;
    rnk[sa[1]]=1;
    for (int i=2;i<=len;++i){
        if (tsa[sa[i]]!=tsa[sa[i-1]]) ++charnum;
        else if ((sa[i]+k>=len) != (sa[i-1]+k>=len)) ++charnum;
        else if ((sa[i]+k<len && sa[i-1]+k<len) && tsa[sa[i]+k]!=tsa[sa[i-1]+k]) ++charnum;
        rnk[sa[i]]=charnum;
    }
    return charnum;
}
void SuffixSort(char str[],int len){
    for (int i=0;i<len;++i){
        rnk[i]=int(str[i]);
        tsa[i+1]=i;
    }
    int charnum=bucketSort(len,256,0);
    for (int k=1;k<len && charnum<len;k<<=1){
        int t=0;
        for (int i=0;i<k;++i) tsa[++t]=len-k+i;
        for (int i=1;i<=len;++i) if (sa[i]-k>=0) tsa[++t]=sa[i]-k;
        charnum=bucketSort(len,charnum,k);
    }
}
void getHeight(char str[],int len){
    int j=0;
    for (int i=0;i<len;++i){
        if (rnk[i]-1>0) while (str[i+j]==str[sa[rnk[i]-1]+j]) ++j;
        height[rnk[i]]=j;
        if (j>0) --j;
    }
}
char str[STRMAXLEN];
//ST
int d[20][STRMAXLEN];
int query(int l,int r){
    int t=log2(r-l+1);
    return min(d[t][l],d[t][r-(1<<t)+1]);
}
void init(int a[],int len){
    for (int i=1;i<=len;++i){
        d[0][i]=a[i];
    }
    int t=1;
    for (int i=1;t<=len;++i){
        for (int j=1;j+t<=len;++j)
            d[i][j]=min(d[i-1][j],d[i-1][j+t]);
        t<<=1;
    }
}
//binary search
int L,R;
void find(int pos,int len,int k){
    int l,r;
    l=pos; r=len+1;
    while (l+1<r){
        int mid=l+r>>1;
        if (query(pos+1,mid)>=k) l=mid;
        else r=mid;
    }
    R=l;
    l=1; r=pos+1;
    while (l+1<r){
        int mid=l+r>>1;
        if (query(mid,pos)>=k) r=mid;
        else l=mid;
    }
    L=r-1;
}
//perminentSegmentTree
struct permanentSegmentTree{
    struct node{
        int lc,rc,l,r;
        int val;
    };
    node tr[5000001];
    int roots[100001];
    int num;
    int vernum;
    void setRange(int l,int r){
        num=0;
        vernum=0;
        roots[0]=0;
        build(l,r,0);
    }
    void build(int l,int r,int now){
        tr[now].l=l; tr[now].r=r; tr[now].val=0; 
        if (tr[now].l!=tr[now].r){
            int mid=l+r>>1;
            tr[now].lc=++num;
            tr[now].rc=++num;
            build(l,mid,tr[now].lc);
            build(mid+1,r,tr[now].rc);
        }
    }
    void update(int pos,int val){
        roots[vernum+1]=update(pos,val,roots[vernum]);
        ++vernum;
    }
    int update(int pos,int val,int now){
        int t=++num;
        tr[t]=tr[now];
        if (tr[t].l==tr[t].r){
            tr[t].val+=val;
        } else {
            int mid=tr[now].l+tr[now].r>>1;
            if (pos<=mid) tr[t].lc=update(pos,val,tr[now].lc);
            else tr[t].rc=update(pos,val,tr[now].rc);
            tr[t].val=tr[tr[t].lc].val+tr[tr[t].rc].val;
        }
        return t;
    }
    int query(int v1,int v2,int k){
        return _query(roots[v1],roots[v2],k);
    }
    int _query(int now1,int now2,int k){
        if (tr[now1].l==tr[now1].r) return tr[now1].l;
        int t=tr[tr[now2].lc].val-tr[tr[now1].lc].val;
        if (t>=k) return _query(tr[now1].lc,tr[now2].lc,k);
        else return _query(tr[now1].rc,tr[now2].rc,k-t);
    }
};
permanentSegmentTree tr;

int main()
{
    int T;
    scanf("%d",&T);
    while (T--){
        int len,q;
        scanf("%d%d",&len,&q);
        scanf("%s",str);
        SuffixSort(str,len);
        getHeight(str,len);
        height[1]=0;
        init(height,len);
        tr.setRange(1,len);
        for (int i=1;i<=len;++i)
            tr.update(sa[i]+1,1);
        while (q--){
            int l,r,k;
            scanf("%d%d%d",&l,&r,&k);
            --l; --r;

            find(rnk[l],len,r-l+1);

            if (R-L+1<k) printf("-1\n");
            else {
                printf("%d\n",tr.query(L-1,R,k));
            }
        }
    }
}