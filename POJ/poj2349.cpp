#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;
struct point{
    int x,y;
} list[1001];
int road[1001][1001];
bool vis[1001];
int dis[1001];
int dis2(int x,int y){
    return x*x+y*y;
}
int main()
{
    int s,n;
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%d%d",&s,&n);
        for (int i=0;i<n;++i){
            scanf("%d%d",&list[i].x,&list[i].y);
        }
        for (int i=0;i<n;++i)
            for (int j=0;j<n;++j)
                road[i][j]=dis2(list[i].x-list[j].x,list[i].y-list[j].y);
        int ans=0;
        memset(vis,0,sizeof(vis));
        memset(dis,127,sizeof(dis));
        dis[0]=0;
        for (int i=0;i<n;++i){
            int Min=0x7f7f7f7f;
            int Minx=-1;
            for (int j=0;j<n;++j)
                if (!vis[j] && Min>dis[j]) {Minx=j; Min=dis[j];}
            ans=max(ans,Min);
            vis[Minx]=true;
            for (int j=0;j<n;++j)
                if (!vis[j] && road[Minx][j]<dis[j]) dis[j]=road[Minx][j];
        }
        sort(dis,dis+n);
        printf("%.2f\n",sqrt(dis[n-s]));
    }
    return 0;
}