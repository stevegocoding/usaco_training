/*
ID: stevego1
LANG: C++
PROG: milk3
*/


#include <vector>
#include <fstream>

using namespace std;
using std::min;

// Capacities of the 3 buckets
vector<int> caps(3, 0);
vector<int> result(21, 0);

bool visited[21][21][21];

void dfs(int a, int b, int c)
{
	if (a < 0 || b < 0 || c < 0)
	{
		return;
	}

	if (!visited[a][b][c])
	{
		visited[a][b][c] = true; 
		dfs(a + min(c, caps[0]-a), b, c - min(c, caps[0]-a));		// C => A
		dfs(a + min(b, caps[0]-a), b - min(b, caps[0]-a), c);		// B => A
		
		dfs(a - min(a, caps[1]-b), b + min(a, caps[1]-b), c);		// A => B
		dfs(a, b + min(c, caps[1]-b), c - min(c, caps[1]-b));		// C => B

		dfs(a - min(a, caps[2]-c), b, c + min(a, caps[2]-c));		// A => C
		dfs(a, b - min(b, caps[2]-c), c + min(b, caps[2]-c));		// B => C

	}

}

int main(int argc, char **argv)
{
	ifstream ifs("milk3.in");
	ofstream ofs("milk3.out"); 

	
	ifs >> caps[0] >> caps[1] >> caps[2]; 

	dfs(0, 0, caps[2]);

	for (int i = 0; i < 21; ++i)
	{
		for (int j = 0; j < 21; ++j)
		{
			if (visited[0][i][j])
				++result[j]; 
		}
	}

	string sep = "";
	for (int i = 0; i < 21; ++i)
	{
		if (result[i] != 0)
		{
			ofs << sep.c_str() << i;
			sep = " ";
		}
	}

	ofs << std::endl; 

	return 0; 
}