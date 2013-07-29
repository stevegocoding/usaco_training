/*
ID: stevego1
LANG: C++
PROG: numtri
*/

#include <vector>
#include <fstream>

using namespace std;

int max_depth = 0;
vector<vector<int> > array, dp; 

int max_sum = 0; 

void search(vector<int>& array, int idx, int depth, int sum)
{
	if (depth == max_depth)
	{
		if (sum > max_sum)
			max_sum = sum; 

		return;
	}
	search(array, idx+depth+1, depth+1, sum+array[idx]);
	search(array, idx+depth+2, depth+1, sum+array[idx]);
}


void dp_solve(int num_rows)
{
	for (int row = 1; row < num_rows; ++row)
	{
		for (int i = 0; i <= row; ++i)
		{
			if (i == 0)
				dp[row][i] = dp[row-1][i] + array[row][i];
			else if (i == row)
				dp[row][i] = dp[row-1][i-1] + array[row][i]; 
			else
				dp[row][i] = max(dp[row-1][i] + array[row][i], dp[row-1][i-1] + array[row][i]);
			
			if (dp[row][i] > max_sum)
				max_sum = dp[row][i]; 
		}
	}
}


int main(int argc, char **argv)
{
	ifstream ifs("numtri.in"); 
	ofstream ofs("numtri.out");

	ifs >> max_depth;
	array.resize(max_depth); 
	dp.resize(max_depth); 
	for (int i = 1; i <= max_depth; ++i)
	{
		array[i-1] = vector<int>(i);
		dp[i-1] = vector<int>(i);
		for (int j = 0; j < i; ++j)
		{
			int val = 0; 
			ifs >> val;
			array[i-1][j] = val;
			dp[i-1][j] = 0; 
		}
	}

	dp[0][0] = array[0][0]; 

	//search(array, 0, 0, 0);
	dp_solve(max_depth); 

	ofs << max_sum << endl; 

	return 0;
}
