#include <iostream>
using namespace std;
main()
{
	string a,b;
	long next[101],i,j;
	cin>>a>>b;
	next[1]=0;
	j=0;
	for (i=1;i<=b.size();i++){
		while (b[i-1]!=b[j] && j>0) j=next[j];
		if (b[i-1]==b[j]) j++;
		next[i+1]=j;
	}
	for (i=1;i<=a.size();i++){
		while (a[i-1]!=b[j] && j>0) j=next[j];
		if (a[i-1]==b[j]) j++;
		if (j==b.size()){cout<<"success!\nThe first appear position is:"<<i-j+1<<endl; break;}
	}
}