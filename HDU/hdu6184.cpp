#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;
typedef long long ll;

vector<int> edges[300001];

ll getSum(int u,int v){//size(u)<size(v)
    int pos=0;
    ll ret=0;
    for (auto w:edges[u]){
        if (w==v) continue;
        pos=lower_bound(edges[v].begin()+pos,edges[v].end(),w)-edges[v].begin();
        if (pos>=edges[v].size()) break;
        if (edges[v][pos]==w) ret++;
    }
    //printf("getSum(%d,%d)=%d\n",u,v,ret*(ret-1)/2);
    return ret*(ret-1)/2ll;
}



int main(){
    int n,m;
    while (~scanf("%d%d",&n,&m)){
        for (int i=1;i<=n;++i){
            edges[i].clear();
        }
        for (int i=1;i<=m;++i){
            int u,v;
            scanf("%d%d",&u,&v);
            edges[u].push_back(v);
            edges[v].push_back(u);
        }
        for (int i=1;i<=n;++i) sort(edges[i].begin(),edges[i].end());
        ll ans=0;
        for (int i=1;i<=n;++i){
            for (auto v:edges[i]){
                int u=i;
                if (v<=u) continue;
                if (edges[u].size()>edges[v].size()) swap(u,v);
                ans+=getSum(u,v);
            }
        }
        printf("%lld\n",ans);
    }
    
}