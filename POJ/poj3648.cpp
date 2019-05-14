#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
#define NODEN 2000010
#define ROADM 2000010
struct path{
    int v,next;
    path(int _v,int _next) {v=_v; next=_next;}
    path(){}
} rds[ROADM];
int num;
int list[NODEN];
void addedge(int u,int v){
    ++num;
    rds[num]=path(v,list[u]);
    list[u]=num;
}
void exclude(int u,int v){
    addedge(u,v^1);
    addedge(v,u^1);
}
int dfn[ROADM],low[ROADM],cnt;
bool inStack[ROADM];
stack<int> st;
int color[ROADM];
int cnum=0;
int type[ROADM];
void tarjan(int x){
    ++cnt;
    dfn[x]=cnt;
    low[x]=cnt;
    inStack[x]=true;
    st.push(x);
    for (int t=list[x];t!=0;t=rds[t].next){
        int v=rds[t].v;
        if (!dfn[v]){
            tarjan(v);
            low[x]=min(low[x],low[v]);
        } else if (inStack[v]) low[x]=min(low[x],low[v]);
        type[x]=min(type[x],type[v]);
    }
    if (dfn[x]==low[x]){
        if (type[x]==0) type[x]=1;
        type[x^1]=-1*type[x];
        while (st.top()!=x){
            color[st.top()]=cnum;
            inStack[st.top()]=false;
            type[st.top()]=type[x];
            type[st.top()^1]=-1*type[x];
            st.pop();
        }
        color[st.top()]=cnum;
        inStack[st.top()]=false;
        st.pop();
        ++cnum;
    }
}
void solve(int n){
    memset(dfn,0,sizeof(dfn)); 
    memset(low,0,sizeof(low));
    memset(color,0,sizeof(color));
    cnum=0; cnt=0;
    for (int i=0;i<2*n;++i) 
        if (!dfn[i]) tarjan(i);
    for (int i=0;i<2*n;i+=2)
        if (color[i]==color[i|1]) {printf("bad luck\n"); return;}
    for (int i=2;i<2*n;i+=2){
        if (type[i]==1) printf("%dh ",i/2);
        else printf("%dw ",i/2);
    }
    printf("\n");
}
int main()
{
    int n,k,m;
    while (~scanf("%d%d",&n,&m)){
        if (n==0 && m==0) return 0;
        memset(list,0,sizeof(list));
        num=0;
        for (int i=0;i<m;++i){
            int u,v;
            char ch1[10],ch2[10];
            scanf("%d%s%d%s",&u,ch1,&v,ch2);
            u*=2; v*=2;
            if (ch1[0]=='h') u=u^1;
            if (ch2[0]=='h') v=v^1;
            exclude(u,v);
        }
        addedge(0,1);
        cnt=0;
        memset(dfn,0,sizeof(dfn));
        memset(inStack,0,sizeof(inStack));
        memset(type,0,sizeof(type));
        while (!st.empty()) st.pop();
        solve(n);
    }
}