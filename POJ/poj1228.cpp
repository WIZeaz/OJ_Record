#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
struct point{
    int x,y;
    point(){}
    point(int x,int y){this->x=x; this->y=y;}
    point operator - (const point &b)  const{
        return point(x-b.x,y-b.y);
    }
    point operator * (const point &b) const{
        return point(x*b.x,y*b.y);
    }
    int operator ^ (const point &b) const{
        return x*b.y-y*b.x;
    }
};
point pts[10001];
point ans[10001];
bool used[10001];
int ansNum;
bool cmp(const point& a,const point& b){
    int t=(a-pts[0])^(b-pts[0]);
    if (t!=0) return t>0;
    else return (a.x*a.x+a.y*a.y)<(b.x*b.x+b.y*b.y);
}
void Graham(int n){
    for (int i=1;i<n;++i)
        if (pts[0].y>pts[i].y || (pts[0].y==pts[i].y && pts[0].x>pts[i].x)){
            point tmp=pts[0];
            pts[0]=pts[i];
            pts[i]=tmp;
        }
    sort(pts+1,pts+n,cmp);
    //for (int i=0;i<n;++i) cout<<pts[i].x<<','<<pts[i].y<<endl;
    ansNum=2;
    ans[0]=pts[0];
    ans[1]=pts[1];
    for (int i=2;i<n;++i){
        while (((ans[ansNum-1]-ans[ansNum-2])^(pts[i]-ans[ansNum-1]))<=0) --ansNum;
        ans[ansNum]=pts[i];
        
        ++ansNum;
    }
}
bool check(const point ps[],int n){
    int sst=0;
    for (int i=1;i<n;++i)
        if (ps[i].y<ps[sst].y || (ps[i].y==ps[sst].y && ps[i].x<ps[sst].x)) sst=i;
    int st=sst;
    int now=(st+1)%n;
    while (1){
        point tmp=ps[now]-ps[st];
        int last=now;
        while (((ps[(now+1)%n]-ps[st])^(tmp))==0) now=(now+1)%n;
        if (now==last) return false;
        if (now==sst) return true;
        st=now;
        now=(now+1)%n;
    }
    return true;
}
double getArea(const point ps[],int n){
    double area=0;
    for (int i=2;i<n;++i){
        area+=double((ps[0]-ps[i-1])^(ps[i]-ps[i-1]))/2.0f;
    }
    if (area<0) area=-area;
    return area;
}
int main()
{
    int T;
    scanf("%d",&T);
    while (T--){
        int n;
        scanf("%d",&n);
        for (int i=0;i<n;++i)
            scanf("%d%d",&pts[i].x,&pts[i].y);
        Graham(n);
        if (ansNum<n || !check(ans,ansNum) || getArea(ans,ansNum)==0) printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}