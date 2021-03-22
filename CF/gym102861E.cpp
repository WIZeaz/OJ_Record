#include <bits/stdc++.h>
using namespace std;
int lowbit(int x){return x&(-x);}
struct BIT{
    int n,st;
    int a[200001];
    int sum[200001];
    void setRange(int N) {
        n=N;
        // st=1;
        // while ((st<<1)<=n) st<<=1;
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
};
BIT bit;
int f[200001][20];
int ans[200001];
vector<int> edges[200001];
vector<int> query_on_node[200001];
int age[200001];
void solve(int u){
    // printf("solve(u=%d)\n",u);
    for (auto w:query_on_node[u]) bit.add(w,1);
    ans[u]+=bit.query(age[u]);
    for (auto v:edges[u]) solve(v);
    for (auto w:query_on_node[u]) bit.add(w,-1);
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;++i){
        int a,b;
        scanf("%d%d",&a,&b);
        age[i]=a;
        f[i][0]=b;
        if (b!=i) edges[b].push_back(i);
    }
    for (int j=1;j<20;++j)
        for (int i=1;i<=n;++i)
            f[i][j]=f[f[i][j-1]][j-1];
    bit.setRange(100000);
    for (int i=1;i<=m;++i){
        int o,l,r;
        scanf("%d%d%d",&o,&l,&r);
        int u=o;
        for (int j=19;j>=0;--j)
            if (age[f[u][j]]<=r) u=f[u][j];
        // printf("(o,l,r,u)=%d,%d,%d,%d\n",o,l,r,u);
        query_on_node[u].push_back(l);
    }
    solve(1);
    for (int i=1;i<=n;++i) printf("%d ",ans[i]);
}
