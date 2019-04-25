#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
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
point pts[30];
point ans[30];
int ansNum;
bool cmp(const point& a,const point& b){
    int t=(a-pts[0])^(b-pts[0]);
    if (t!=0) return t>0;
    else return (a.x*a.x+a.y*a.y)<(b.x*b.x+b.y*b.y);
}
void Graham(int n){
    for (int i=1;i<n;++i)
        if (pts[0].y>pts[i].y){
            point tmp=pts[0];
            pts[0]=pts[i];
            pts[i]=tmp;
        }
    sort(pts+1,pts+n,cmp);
    ansNum=2;
    ans[0]=pts[0];
    ans[1]=pts[1];
    for (int i=2;i<n;++i){
        while (((ans[ansNum-1]-ans[ansNum-2])^(pts[i]-ans[ansNum-1]))<0) --ansNum;
        ans[ansNum]=pts[i];
        ++ansNum;
    }
}
double getLen(const point ps[],int n){
    double r=0;
    point tmp=ps[n-1]-ps[0];
    r+=sqrt(tmp.x*tmp.x+tmp.y*tmp.y);
    for (int i=1;i<n;++i){
        tmp=ps[i]-ps[i-1];
        r+=sqrt(tmp.x*tmp.x+tmp.y*tmp.y);
    }
    return r;
}
point in[30];
int v[30];
int l[30];
int main()
{
    for (int k=1;;++k){
        int n;
        scanf("%d",&n);
        if (n==0) return 0;

        for (int i=0;i<n;++i){
            scanf("%d%d%d%d",&in[i].x,&in[i].y,&v[i],&l[i]);
        }

        int MaxState=(1<<n);
        int Minv,MinState;
        double Minl=0;
        Minv=0x3f3f3f3f; MinState=-1;
        for (int i=0;i<MaxState;++i){
            int nowState=i;
            int num=0;
            double nowl=0,needl=0;
            int nowv=0;
            for (int j=0;j<n;++j){
                if (nowState&1){
                    nowv+=v[j];
                    nowl+=l[j];
                } else {
                    pts[num]=in[j];
                    ++num;
                }
                nowState>>=1;
            }
            if (nowv>Minv) continue;
            if (num>1){
                Graham(num);
                needl=getLen(ans,ansNum);
            } else needl=0;
            if (nowl>=needl) {
                if (nowv<Minv) {Minv=nowv; Minl=double(nowl)-needl; MinState=i;}
            }
        }
        printf("Forest %d\nCut these trees:",k);
        for (int i=1;i<=n;++i){
            if (MinState&1) printf(" %d",i);
            MinState>>=1;
        }
        printf("\nExtra wood: %.2f\n\n",Minl);
    }
    return 0;
}