/*
ID: stevego1
LANG: C++
PROG: barn1
*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std; 

struct gap
{
	gap(int _g = 0, int _pos = 0)
		: g(_g)
		, pos(_pos) 
	{}

	int g; 
	int pos; 
};
bool gap_comp(const gap& g1, const gap& g2) { return (g1.g == g2.g) ? (g1.pos > g2.pos) : (g1.g > g2.g); }

int main(int argc, char **argv)
{
	int m = 0;			// maximum boards.
	int s = 0;			// total stalls.
	int c = 0;			// numbers of cows in stall 
	vector<int> occu_s;	// occupied stalls 
	vector<gap> gaps;	// gap[i] = occu_s[i] - occu_s[i-1] 

	ifstream ifs("barn1.in");
	ofstream ofs("barn1.out"); 
	ifs >> m >> s >> c; 
	for (int i = 0; i < c; ++i)
	{
		int v = 0; 
		ifs >> v;
		occu_s.push_back(v); 
	}
	sort(occu_s.begin(), occu_s.end());
	gaps.resize(c);
	gaps[0] = gap(0, 0); 
	for (int i = 1; i < c; ++i) 
	{
		gaps[i] = gap(occu_s[i] - occu_s[i-1], i); 
	}
	sort(gaps.begin(), gaps.end(), gap_comp); 

	vector<int> segs; 
	int ns = (m < c)? (m-1):(c-1); 
	for (int i = 0; i < ns; ++i)
	{
		segs.push_back(gaps[i].pos); 
	}
	segs.push_back(c);
	sort(segs.begin(), segs.end()); 
	int result = 0; 
	int start = 0; 
	for (int i = 0; i < ns+1; ++i)
	{
		result += occu_s[segs[i] - 1] - occu_s[start] + 1; 
		start = segs[i];
	}

	ofs << result << endl;
	return 0;
}