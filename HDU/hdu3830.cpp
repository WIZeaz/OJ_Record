#include <iostream>
using namespace std;
long long ox,oy,oz;
long long getDep(long long a,long long b,long long c,long long &x,long long &y,long long &z){
    long long n,m;
    //cout<<a<<' '<<b<<' '<<c<<endl;
    if (2*b<a+c){
        n=b-a; m=c-b;
        long long s=(m-1)/n;
        return s+getDep(a+s*n,b+s*n,c,x,y,z);
    } else if (2*b>a+c){
        n=b-a; m=c-b;
        long long s=(n-1)/m;
        return s+getDep(a,b-s*m,c-s*m,x,y,z);
    } else {
        //cout<<"done.\n";
        x=a; y=b; z=c;
        return 0;
    }
}
void go(long long step,long long a,long long b,long long c,long long &x,long long &y,long long &z){
    long long n,m;
    if (step>0){
        if (2*b<a+c){
            n=b-a; m=c-b;
            long long s=(m-1)/n;
            if (step<s) s=step;
            go(step-s,a+s*n,b+s*n,c,x,y,z);
        } else if (2*b>a+c){
            n=b-a; m=c-b;
            long long s=(n-1)/m;
            if (step<s) s=step;
            go(step-s,a,b-s*m,c-s*m,x,y,z);
        } else {
            x=a; y=b; z=c;
            return;
        }
    } else {
        x=a; y=b; z=c;
    }
}
int main()
{
    long long a,b,c,x,y,z;
    long long x1,y1,z1,x2,y2,z2;
    long long d1,d2;
    while (~scanf("%lld%lld%lld",&a,&b,&c)){
        scanf("%lld%lld%lld",&x,&y,&z);
        if (a>b) {long long t=a; a=b; b=t;}
        if (a>c) {long long t=a; a=c; c=t;}
        if (b>c) {long long t=b; b=c; c=t;}
        
        if (x>y) {long long t=x; x=y; y=t;}
        if (x>z) {long long t=x; x=z; z=t;}
        if (y>z) {long long t=y; y=z; z=t;}
        
        d1=getDep(a,b,c,x1,y1,z1);
        d2=getDep(x,y,z,x2,y2,z2);
        //cout<<d1<<' '<<d2<<endl;
        if (x1==x2 && y1==y2 && z1==z2){
            printf("YES\n");
            long long l,r;
            r=min(d1,d2)+1;
            l=-1;
            //cout<<l<<' '<<r<<endl;
            //if (d1<d2) {go(d2-d1,x,y,z,x1,y1,z1); x=x1; y=y1; z=z1;}
            //else if (d1>d2) {go(d1-d2,a,b,c,x1,y1,z1); a=x1; b=y1; c=z1;}
        // cout<<a<<' '<<b<<' '<<c<<' '<<x
            x1=x2=y1=y2=z1=z2=0;
            while (l+1<r){
                long long mid=(l+r)>>1;
                go(d1-mid,a,b,c,x1,y1,z1);
                //cout<<d1-mid<<' '<<x1<<' '<<y1<<' '<<z1<<endl;
                go(d2-mid,x,y,z,x2,y2,z2);
                //cout<<d2-mid<<" "<<x2<<' '<<y2<<' '<<z2<<endl;
                if (x1==x2 && y1==y2 && z1==z2) r=mid;
                else l=mid;
            }
            printf("%lld\n",d1+d2-2*r);
        } else printf("NO\n");
    }
}