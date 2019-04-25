#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;
#define INF 0x3f3f3f3f
int road[1001][1001];
bool vis[1001];
int dis[1001];
bool cnt[1001];
int main()
{
    int m,n;
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%d%d",&n,&m);
        memset(road,0x3f,sizeof(road));
        for (int i=0;i<m;++i){
            int s,t,w;
            scanf("%d%d%d",&s,&t,&w);
            --s; --t;
            road[s][t]=w;
            road[t][s]=w;
        }
        bool flag=false;
        int ans=0;
        memset(vis,0,sizeof(vis));
        memset(dis,0x3f,sizeof(dis));
        memset(cnt,0,sizeof(cnt));
        dis[1]=0;
        for (int i=0;i<n;++i){
            int Min=INF;
            int Minx=-1;
            for (int j=0;j<n;++j)
                if (!vis[j] && Min>dis[j]) {Minx=j; Min=dis[j];}
            
            if (Minx==-1) {flag=true; break;}
            if (cnt[Minx]) {flag=true; break;}
            vis[Minx]=true;
            ans+=Min;
            
            for (int j=0;j<n;++j)
                if (!vis[j]){
                    if (road[Minx][j]<dis[j]) {dis[j]=road[Minx][j]; cnt[j]=false;}
                    else if (road[Minx][j]==dis[j]) {cnt[j]=true;}
                }
        }
        if (flag) printf("Not Unique!\n");
        else printf("%d\n",ans);
    }
    return 0;
}