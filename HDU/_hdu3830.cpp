#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct state{
    long long a,b,c;
    state(){}
    state(long long _a,long long _b,long long _c) {a=_a; b=_b; c=_c;}
    bool operator == (const state& t) const{
        return ((a==t.a)&&(b==t.b)&&(c==t.c));
    }
    void init(){
        if (a>b) {long long  t=a; a=b; b=t;}
        if (a>c) {long long  t=a; a=c; c=t;}
        if (b>c) {long long  t=b; b=c; c=t;}
    }
};
long long getDep(state x,state& root){
    long long n=x.b-x.a,m=x.c-x.b;
    if (n<m){
        long long s=(m-1)/n;
        return s+getDep(state(x.a+s*n,x.b+s*n,x.c),root);
    } else if (n>m){
        long long s=(n-1)/m;
        return s+getDep(state(x.a,x.b-s*m,x.c-s*m),root);
    } else {
        root=x;
        return 0LL;
    }
}
state go(long long step,state x){
    long long n=x.b-x.a,m=x.c-x.b;
    if (step>0){
        if (n<m){
            long long s=(m-1)/n;
            if (s>step) s=step;
            return go(step-s,state(x.a+s*n,x.b+s*n,x.c));
        } else if (n>m){
            long long s=(n-1)/m;
            if (s>step) s=step;
            return go(step-s,state(x.a,x.b-s*m,x.c-s*m));
        } else {
            return x;
        }
    } else return x;
}
int main()
{
    state st,ed;
    state r1,r2;
    while (~scanf("%lld%lld%lld",&st.a,&st.b,&st.c)){
        scanf("%lld%lld%lld",&ed.a,&ed.b,&ed.c);
        //cout<<st.a<<' '<<st.b<<' '<<st.c<<endl<<ed.a<<' '<<ed.b<<' '<<ed.c<<endl;
        st.init(); ed.init();
        long long d1=getDep(st,r1);
        long long d2=getDep(ed,r2);
        //cout<<"d1: "<<d1<<"  d2: "<<d2<<endl;
        if (r1==r2){
            printf("YES\n");
            long long l=-1;
            long long r=min(d1,d2)+1;
            while (l+1<r){
                long long mid=l+((r-l)>>1);
                r1=go(d1-mid,st);
                r2=go(d2-mid,ed);
                //cout<<"r1: "<<r1.a<<' '<<r1.b<<' '<<r1.c<<endl;
                //cout<<"r2: "<<r2.a<<' '<<r2.b<<' '<<r2.c<<endl;
                if (r1==r2) l=mid;
                else r=mid;
            }
            //cout<<" r: "<<r<<endl;
            long long ans=d1+d2-2*l;
            printf("%lld\n",ans);
        } else printf("NO\n");
    }
    return 0;
}