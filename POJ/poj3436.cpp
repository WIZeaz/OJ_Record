#include <vector>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <climits>
using namespace std;

struct ISAP{
    struct Edge{
        int u,v,c,f;
        Edge(){}
        Edge(int _u,int _v,int _c,int _f){
            u=_u; v=_v; c=_c; f=_f;
        }
    };
    
    static const int _num_v=1000;

    vector<Edge> edges;
    vector<int> e[_num_v];
    bool vis[_num_v];
    int dist[_num_v];
    int num[_num_v];
    int cur[_num_v];
    int n,s,t;
    void init(int _n,int _s,int _t){
        n=_n; s=_s; t=_t;
        edges.clear();
        for (int i=1;i<=_n;++i) e[i].clear();
        fill(vis+1,vis+1+n,0);
        fill(dist+1,dist+1+n,n);
        fill(num+1,num+1+n,0);
        fill(cur+1,cur+1+n,0);
    }
    void addedge(int u,int v,int c){
        edges.push_back(Edge(u,v,c,0));
        edges.push_back(Edge(v,u,0,0));
        int num=edges.size();
        e[u].push_back(num-2);
        e[v].push_back(num-1);
    }

    void bfs(int s,int t){
        queue<int> que;
        que.push(t);
        vis[t]=true;
        dist[t]=0;
        num[0]++;
        while (!que.empty()){
            int u=que.front();
            que.pop();
            for (int i=0;i<e[u].size();++i){
                Edge &edge=edges[e[u][i]^1];
                if (vis[edge.u] || edge.c==edge.f) continue;
                dist[edge.u]=dist[u]+1;
                num[dist[edge.u]]++;
                vis[edge.u]=true;
                que.push(edge.u);
            }
        }
    }
    
    int augment(int u,int f){
        if (u==t) return f;
        
        int rest=f;
        int len=e[u].size();
        // printf("augment(%d,%d) len=%d\n",u,f,len);
        bool ok=false;
        for (int i=cur[u];i<len;++i){
            int &j=e[u][i];
            Edge &e=edges[j];
            if (dist[e.v]+1!=dist[e.u] || e.c==e.f) continue;
            cur[u]=i;
            int now_flow=augment(e.v,min(rest,e.c-e.f));
            rest-=now_flow;
            edges[j].f+=now_flow;
            edges[j^1].f-=now_flow;
            ok=true;
            if (!rest) return f-rest;
        }
        
        if (--num[dist[u]]==0) dist[s]=n;

        cur[u]=0;
        int d_min=n-1;
         for (int i=0;i<e[u].size();++i)
            if (edges[e[u][i]].f<edges[e[u][i]].c)
                d_min=min(d_min,dist[edges[e[u][i]].v]);
        
        dist[u]=d_min+1;
        num[dist[u]]++;

        return f-rest;
    }

    long long maxflow(){
        bfs(s,t);
        long long f=0;
        while (dist[s]<n){
            f+=augment(s,INT_MAX);
            //printf("f=%lld\n",f);
        }
        return f;
    }
};
int mask1[100],mask2[100]; //not be present, should be present
int prod[100];
int bits[100];
int q[100];
ISAP flow;
struct Answer{
    int a,b,x;
    Answer(){}
    Answer(int _a,int _b,int _x){a=_a; b=_b; x=_x;}
};
vector<Answer> details;
int main(){
    int p,n;
    bits[0]=1;
    for (int i=1;i<31;++i) bits[i]=bits[i-1]*2;
    while (~scanf("%d%d",&p,&n)){
        int s=2*n+1;
        int t=2*n+2;
        flow.init(2*n+2,s,t);
        for (int i=1;i<=n;++i) mask1[i]=mask2[i]=prod[i]=0;
        details.clear();
        for (int i=1;i<=n;i++){
            scanf("%d",&q[i]);
            flow.addedge(i,n+i,q[i]);
            for (int j=0;j<p;++j){
                int t;
                scanf("%d",&t);
                if (t==0) mask1[i]|=bits[j];
                else if (t==1) mask2[i]|=bits[j];
            }
            for (int j=0;j<p;++j){
                int t;
                scanf("%d",&t);
                if (t==1) prod[i]|=bits[j];
            }
        }
        for (int i=1;i<=n;++i){
            for (int j=1;j<=n;++j)
                if ((prod[i]&mask1[j])==0 && (prod[i]&mask2[j])==mask2[j]){
                    //printf("add: %d->%d\n",i,j);
                    flow.addedge(n+i,j,q[i]);
                }
            if (mask2[i]==0) flow.addedge(s,i,q[i]);
            if (prod[i]+1==bits[p]) flow.addedge(n+i,t,q[i]);
        }
        long long maxflow=flow.maxflow();
        for (int i=0;i<flow.edges.size();++i){
            ISAP::Edge& e=flow.edges[i];
            if (e.u>2*n || e.v>2*n || e.f<=0 || e.u<e.v) continue;
            details.push_back(Answer(e.u-n,e.v,e.f));
        }
        printf("%lld %d\n",maxflow,details.size());
        for (int i=0;i<details.size();++i){
            Answer& ans=details[i];
            printf("%d %d %d\n",ans.a,ans.b,ans.x);
        }
    }
}