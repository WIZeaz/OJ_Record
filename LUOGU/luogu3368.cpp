#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int lowbit(int x){return x&(-x);}

struct TreeArray{
    int n;
    int a[600001];
    void setRange(int N) { n=N;}
    void clear() {n=0; memset(a,0,sizeof(a));}
    void verify(int pos,int val){
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
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    tr.clear();
    tr.setRange(n+1);
    int l=0;
    for (int i=1;i<=n;++i){
        int t;
        scanf("%d",&t);
        tr.verify(i,t-l);
        l=t;
    }
    for (int i=1;i<=m;++i){
        int t,x;
        scanf("%d%d",&t,&x);
        if (t==1){
            int y,k;
            scanf("%d%d",&y,&k);
            tr.verify(x,k);
            tr.verify(y+1,-k);
        }
        else {
            printf("%d\n",tr.query(x));
        }
    }
}