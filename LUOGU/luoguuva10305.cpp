#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
struct node{
    int v,next;
    node(){}
    node(int _v,int _next){
        v=_v; next=_next;
    }
};
node rds[500001];
int head[50001];
int deg[50001];
int num;
void addedge(int u,int v){
    rds[++num]=node(v,head[u]);
    ++deg[v];
    head[u]=num;
}
vector<int> ans;
bool topo(int n){
    queue<int> que;
    for (int i=1;i<=n;++i)
        if (deg[i]==0){
            que.push(i);
            ans.push_back(i);
        }
    while (!que.empty()){
        int u=que.front();
        que.pop();
        for (int i=head[u];i;i=rds[i].next){
            int v=rds[i].v;
            --deg[v];
            if (deg[v]==0){
                que.push(v);
                ans.push_back(v);
            }
        }
    }
    if (ans.size()==n) return true;
    return false;
}
int main(){
    int n,m;

    while (~scanf("%d%d",&n,&m)){
        if (n==0 && m==0) return 0;
        memset(head,0,sizeof(head));
        num=0;
        for (int i=0;i<m;++i){
            int u,v;
            scanf("%d%d",&u,&v);
            addedge(u,v);
        }
        ans.clear();
        topo(n);
        for (auto i:ans){
            printf("%d ",i);
        }
        printf("\n");
    }
}