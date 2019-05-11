#include <cstring>
#include <cstdio>
#include <string>
#include <set>
#include <iostream>
using namespace std;
set<string> e;
int work(char* str)
{
    int i=0,j=1,k=0; 
    int len=strlen(str);
    while (j<len && k<len){
		int t=str[(i+k)%len]-str[(j+k)%len];
        if (!t) ++k;
        else {
            if (t<0) j+=k+1;
            else {i+=k+1; j=i+1;}
            k=0;
        }
    }
    return i;
}
int main()
{
    int T;
    char str[10000];
    while (~scanf("%d",&T)){
        e.clear();
        while (T--){
            scanf("%s",str);
            int tmp=work(str);
            int len=strlen(str);
            string ch;
            for (int i=tmp;i<len;++i)
                ch+=str[i];
            for (int i=0;i<tmp;++i)
                ch+=str[i];
            e.insert(ch);
        }
        printf("%d\n",e.size());
    }
    return 0;
}