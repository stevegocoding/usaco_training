/*
ID:stevego1
PROG:packrec
LANG:C++
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
ifstream fin ("packrec.in");
ofstream fout("packrec.out");
int rec[4][2];
unsigned int sol[2304][2],cc=-1,mins=-1;
bool mark[150][150];
int max4(int a,int b,int c,int d);
void check(int x,int y);
void process(int a,int b,int c,int d);
int compare(const void * ptr1,const void * ptr2);
int main(void)
{
	for(int i=0;i<4;i++)fin>>rec[i][0]>>rec[i][1];
	for(int i=0,c=0;i<4;i++)
		for(int j=0;j<4;j++)
			for(int k=0;k<4;k++)
				for(int l=0;l<4;l++)
				{
					if (i==j||i==k||i==l||j==k||j==l||k==l)continue;
					process(i,j,k,l);
				}
				qsort(sol,cc+1,sizeof(int)*2,compare);
				fout<<mins<<endl;
				for(int i=0;i<=cc;i++) fout<<sol[i][0]<<' '<<sol[i][1]<<endl;
				return 0;
}
int max4(int a,int b,int c,int d)
{
	int maxv=a;
	if(maxv<b)maxv=b;
	if(maxv<c)maxv=c;
	if(maxv<d)maxv=d;
	return maxv;
}
void check(int x,int y)
{
	if(x>y)swap(x,y);
	if(mark[x-1][y-1])return;
	mark[x-1][y-1]=true;
	if(mins>x*y){mins=x*y;cc=0;sol[0][0]=x;sol[0][1]=y;} else
		if(mins==x*y){sol[++cc][0]=x;sol[cc][1]=y;}
}
void process(int a,int b,int c,int d)
{
	int pos[4];
	for(pos[0]=0;pos[0]<2;pos[0]++)
		for(pos[1]=0;pos[1]<2;pos[1]++)
			for(pos[2]=0;pos[2]<2;pos[2]++)
				for(pos[3]=0;pos[3]<2;pos[3]++)
				{
					int x,y;
					x=max4(rec[a][pos[0]],rec[b][pos[1]],rec[c][pos[2]],rec[d][pos[3]]);
					y=rec[a][!pos[0]]+rec[b][!pos[1]]+rec[c][!pos[2]]+rec[d][!pos[3]];
					check(x,y);
					x=max(rec[b][pos[1]]+rec[c][pos[2]]+rec[d][pos[3]],rec[a][pos[0]]);
					y=rec[a][!pos[0]]+max4(0,rec[b][!pos[1]],rec[c][!pos[2]],rec[d][!pos[3]]);
					check(x,y);
					x=max(rec[b][pos[1]]+rec[c][pos[2]],rec[a][pos[0]])+rec[d][pos[3]];
					y=max4(0,rec[a][!pos[0]]+rec[b][!pos[1]],rec[a][!pos[0]]+rec[c][!pos[2]],rec[d][!pos[3]]);
					check(x,y);
					if(rec[b][pos[1]]<=rec[c][pos[2]])
					{
						x=rec[a][pos[0]]+rec[c][pos[2]]+rec[d][pos[3]];
						y=max4(rec[a][!pos[0]],rec[b][!pos[1]]+rec[c][!pos[2]],rec[d][!pos[3]],0);
						check(x,y);
					}
					x=max(rec[a][pos[0]],rec[b][pos[1]])+rec[c][pos[2]]+rec[d][pos[3]];
					y=max4(rec[a][!pos[0]]+rec[b][!pos[1]],rec[c][!pos[2]],rec[d][!pos[3]],0);
					check(x,y);
					if(rec[b][!pos[1]]<=rec[d][!pos[3]]) 
					{
						if(rec[a][!pos[0]]+rec[b][!pos[1]]<=rec[d][!pos[3]])
							x=max4(rec[c][pos[2]],rec[b][pos[1]]+rec[d][pos[3]],rec[a][pos[0]]+rec[d][pos[3]],0);
						else
							if(rec[a][pos[0]]+rec[c][pos[2]]<=rec[b][pos[1]]+rec[d][pos[3]] && rec[a][pos[0]]<rec[b][pos[1]]) x=rec[b][pos[1]]+rec[d][pos[3]];
							else
								x=max4(rec[a][pos[0]]+rec[c][pos[2]],rec[b][pos[1]]+rec[d][pos[3]],rec[a][pos[0]]+rec[d][pos[3]],rec[b][pos[1]]+rec[c][pos[2]]);
						y=max(rec[a][!pos[0]]+rec[b][!pos[1]],rec[c][!pos[2]]+rec[d][!pos[3]]);
						check(x,y);
					}
				}
}
int compare(const void * ptr1,const void * ptr2)
{
	int *a=(int *)ptr1,*b=(int *)ptr2;
	int tmp=a[0]-b[0];
	if (tmp==0) return a[1]-a[2];
	return tmp;
}