/*
ID: stevego1
LANG: C++
PROG: crypt1
*/


#include <fstream>
#include <memory.h>

using namespace std;

bool digs[10];
bool verify(int v)
{
	while (v > 0)
	{
		if (digs[v % 10] == false) 
			return false;
		v /= 10; 
	}
	return true;
}

int main(int argc, char **argv)
{
	ifstream fin("crypt1.in");  
	ofstream fout("crypt1.out");  
	int cnt = 0, buffer;
	int digitnum = 0;
	::memset(digs, false, sizeof(digs));  
	fin >> digitnum;  
	for(int i = 0; i < digitnum; ++i)  
	{  
		fin >> buffer;  
		digs[buffer] = true;  
	}  
	for(int i = 111; i <= 999; ++i)  
	{  
		for(int j = 11; j <= 99; ++j) 
		{  
			if(!verify(i) || !verify(j))  
			{  
				continue;  
			}  
			int a, b, res;  
			a = i * (j % 10);  
			b = i * (j / 10);  
			res = i * j;  
			if((a > 999) || (b > 999) || (res > 9999))  
			{  
				continue;  
			}  
			if(!verify(a) || !verify(b) || !verify(res)) 
			{  
				continue;  
			}  
			else  
			{  
				cnt++; 
				//如果想输出算式，可以加上fout << i << " " << j << " " << a << " " << b << " " << res << endl;  
			}  
		}  
	}  
	fout << cnt << endl;  //输出答案  
	return 0;  
	
}

