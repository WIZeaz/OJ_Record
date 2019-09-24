#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
struct point{
    long long x,y;
    point(){}
    point(long long _x,long long _y){x=_x; y=_y;}
    bool operator < (const point &b) const{
        return x<b.x;
    }
} px[300001],py[300001];
point tmp[300001];

long long dis2(const point&a, const point &b){
    long long t1=(a.x-b.x);
    long long t2=(a.y-b.y);
    return t1*t1+t2*t2;
}
long long solve(int l,int r){
    if (l+1==r){
        if (py[l].y>py[r].y) swap(py[l],py[r]);
        return dis2(px[l],px[r]);
    }
    else if (l+2==r){
        if (py[l].y>py[l+1].y) swap(py[l],py[l+1]);
        if (py[l].y>py[l+2].y) swap(py[l],py[l+2]);
        if (py[l+1].y>py[l+2].y) swap(py[l+1],py[l+2]);
        return min(min(dis2(px[l],px[l+1]),dis2(px[l+1],px[l+2])),dis2(px[l],px[l+2]));
    }
    int mid=l+r>>1;
    long long d=min(solve(l,mid),solve(mid+1,r));
    int i=l,j=mid+1;
    for (int k=l;k<=r;++k)
        if (i>mid) tmp[k]=py[j++];
        else if (j>r) tmp[k]=py[i++];
        else if (py[i].y<py[j].y) tmp[k]=py[i++];
        else tmp[k]=py[j++];

    for (int i=l;i<=r;++i) py[i]=tmp[i];
    int num=0;
    for (int i=l;i<=r;++i)
        if ((py[i].x-px[mid].x)*(py[i].x-px[mid].x)<=d) tmp[num++]=py[i];
    for (int i=0;i<num;++i){
        for (int j=i+1;j<num && j<=i+5;++j)
            d=min(d,dis2(tmp[i],tmp[j]));
    }
    return d;
}
int main(){
    int n;
    scanf("%d",&n);
    for (int i=0;i<n;++i){
        scanf("%lld%lld",&px[i].x,&px[i].y);
    }
    sort(px,px+n);
    for (int i=0;i<n;++i) py[i]=px[i];
    printf("%.4lf",sqrt(solve(0,n-1)));
}