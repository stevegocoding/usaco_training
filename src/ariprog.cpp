/*
ID: stevego1
LANG: C++
PROG: ariprog
*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct answer_ab
{
	answer_ab(int _a, int _b)
		: a(_a)
		, b(_b) {}
	int a; 
	int b;
};

bool compare_ab(const answer_ab& val_a, const answer_ab& val_b)
{
	if (val_a.b < val_b.b)
		return true; 
	else if (val_a.b == val_b.b)
	{
		return val_a.a <= val_b.a; 
	}
	else 
		return false; 
}

vector<bool> bisquares(250*250*2, false); 
vector<answer_ab> sequence;

void fill_bisquares(int m)
{
	for (int p = 0; p <= m; ++p)
	{
		for (int q = p; q <= m; ++q)
		{
			bisquares[p*p + q*q] = true;
		}
	}
}

int find_sequence(int n, int m)
{
	int count = 0; 
	for (int a = 0; a <= m*m; ++a)
	{
		if (bisquares[a])
		{
			for (int b = 1; b <= (m*m*2-a)/(n-1); ++b)
			{
				if (!bisquares[a+b*(n-1)])
					continue; 
				
				bool t = true;
				for (int k = 0; k < n; ++k)
				{
					if (!bisquares[a+b*k])
					{
						t = false;
						break;
					}
				}
				if (t)
				{
					++count;
					sequence.push_back(answer_ab(a, b));
				}
			}
		}
	}
	
	return count;
}

int main(int argc, char **argv)
{
	ifstream ifs("ariprog.in");
	ofstream ofs("ariprog.out");
	
	int n = 0; 
	int m = 0; 
	int count = 0; 

	ifs >> n >> m; 

	fill_bisquares(m);

	count = find_sequence(n, m); 
	if (count == 0)
		ofs << "NONE" << endl; 
	else
	{
		std::sort(sequence.begin(), sequence.end(), compare_ab);
		
		for (int i = 0; i < sequence.size(); ++i)
		{
			ofs << sequence[i].a << " " << sequence[i].b << endl;
		}
	}
}