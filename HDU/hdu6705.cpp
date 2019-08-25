#include <bits/stdc++.h>
using namespace std;
struct edge{
    int v,w;
    edge(){}
    edge(int _v,int _w){v=_v; w=_w; }
    bool operator < (const edge &b) const{
        return w<b.w;
    }
};
vector<edge> vec[50001];
struct node{
    int u,v,x;
    long long s;
    node(){}
    node(int _u,int _v,int _x,long long _s) {u=_u; v=_v; x=_x; s=_s;}
    bool operator <(const node& b) const{
        return s+vec[u][x].w>b.s+vec[b.u][b.x].w;
    }
};
priority_queue<node> que;
int qu[50001];
long long ans[50001];
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        int n,m,q;
        que=priority_queue<node>();
        scanf("%d%d%d",&n,&m,&q);
        for (int i=1;i<=n;++i) vec[i].clear();
        for (int i=0;i<m;++i){
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            vec[u].push_back(edge(v,w));
        }
        for (int i=1;i<=n;++i)
            if (vec[i].size()>0){
                sort(vec[i].begin(),vec[i].end());
                que.push(node(i,vec[i][0].v,0,0));
            }
        int maxK=0;
        for (int i=0;i<q;++i){
            scanf("%d",&qu[i]);
            maxK=max(maxK,qu[i]);
        }
        for (int i=0;i<maxK;++i){
            node tmp=que.top();
            que.pop();
            ans[i]=tmp.s+vec[tmp.u][tmp.x].w;
            if (tmp.x+1<vec[tmp.u].size()) que.push(node(tmp.u,vec[tmp.u][tmp.x+1].v,tmp.x+1,tmp.s));
            if (vec[tmp.v].size()>0) que.push(node(tmp.v,vec[tmp.v][0].v,0,tmp.s+vec[tmp.u][tmp.x].w));
        }
        for (int i=0;i<q;++i){
            printf("%lld\n",ans[qu[i]-1]);
        }
    }
}