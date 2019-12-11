#include <bits/stdc++.h>
using namespace std;
struct node{
    int id,val;
    node(){}
    node(int _id,int _val){id=_id; val=_val;}
    bool operator<(const node& b) const{
        return val<b.val;
    }
};
node a[200001];
node b[200001];
int c[200001];
int lowbit(int x){return x&(-x);}
const long long M=99999997;
struct TreeArray{
    int n;
    int a[500001];
    void setRange(int N) { n=N;}
    void clear() {memset(a,0,sizeof(a));}
    void modify(int pos,int val){
        for (int i=pos;i<=n;i+=lowbit(i))
            a[i]+=val;
    }
    int query(int pos){
        int rnt=0;
        for (int i=pos;i>0;i-=lowbit(i)) rnt+=a[i];
        return rnt;
    }
};
TreeArray tr;
int main(){
    int n;
    scanf("%d",&n);
    for (int i=0;i<n;++i){scanf("%d",&a[i].val); a[i].id=i+1;}
    for (int i=0;i<n;++i){scanf("%d",&b[i].val); b[i].id=i+1;}
    sort(a,a+n); sort(b,b+n);
    for (int i=0;i<n;++i) c[a[i].id]=b[i].id;
    long long ans=0;
    tr.clear();
    tr.setRange(n);
    for (int i=n;i>=1;--i){
        ans=(ans+tr.query(c[i]))%M;
        tr.modify(c[i],1);
    }
    printf("%lld",ans);
}