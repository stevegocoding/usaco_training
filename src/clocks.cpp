/*
ID: stevego1
LANG: C++
PROG: clocks
*/

#include <fstream>
#include <vector>
#include <iterator>
#include <deque> 

using namespace std;

vector<vector<int> > move_ways;

void init_moves_table()
{
	int seq1[] = {0, 1, 3, 4};		// ABDE
	int seq2[] = {0, 1, 2};			// ABC
	int seq3[] = {1, 2, 4, 5};		// BCEF
	int seq4[] = {0, 3, 6};			// ADG
	int seq5[] = {1, 3, 4, 5, 7};	// BDEFH
	int seq6[] = {2, 5, 8};			// CFI
	int seq7[] = {3, 7, 6, 7};		// DEGH
	int seq8[] = {6, 7, 8};			// GHI
	int seq9[] = {4, 5, 7, 8};		// EFHI
	
	move_ways.push_back(vector<int>(seq1, seq1+4));
	move_ways.push_back(vector<int>(seq2, seq2+3));
	move_ways.push_back(vector<int>(seq3, seq3+4));
	move_ways.push_back(vector<int>(seq4, seq4+3));
	move_ways.push_back(vector<int>(seq5, seq5+5));
	move_ways.push_back(vector<int>(seq6, seq6+3));
	move_ways.push_back(vector<int>(seq7, seq7+4));
	move_ways.push_back(vector<int>(seq8, seq8+3));
	move_ways.push_back(vector<int>(seq9, seq9+4)); 	
}

class c_clocks
{
public:
	c_clocks(const vector<vector<int> >& clocks)
	{
		std::copy(clocks.begin(), clocks.end(), back_inserter(m_clocks)); 
	}
	
	c_clocks move(int move_idx)
	{	
		vector<vector<int> > temp; 
		std::copy(m_clocks.begin(), m_clocks.end(), back_inserter(temp)); 
		for (size_t i = 0; i < move_ways[move_idx].size(); ++i)
		{
			int row = move_ways[move_idx][i]/3;
			int col = move_ways[move_idx][i]%3;
			temp[row][col] += 3;
			if (temp[row][col] > 12)
				temp[row][col] -= 12;
		}

		return c_clocks(temp);
	}

	bool is_all_12() const
	{
		for (size_t i = 0; i < 3; ++i)
		{
			for (size_t j = 0; j < 3; ++j)
			{
				if (m_clocks[i][j] != 12)
					return false;
			}
		}
		return true;
	}
	
private:
	vector<vector<int> > m_clocks;
};

enum e_moves
{
	MOVE_ABDE = 0, 
	MOVE_ABC = 1
};

c_clocks read_input_clocks(ifstream& ifs)
{
	vector<vector<int> > clocks;
	clocks.resize(3);
	clocks[0].resize(3);
	clocks[1].resize(3);
	clocks[2].resize(3);
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			int t = 0; 
			ifs >> t; 
			clocks[i][j] = t;
		}
	}

	return c_clocks(clocks);
}

vector<int> move_count(9, 0);

void truncated_dfs(c_clocks& clocks, int depth, vector<int>& move_steps, vector<vector<int> >& results)
{
	if (clocks.is_all_12())
	{
		results.push_back(move_steps);
		return;
	}

	if (depth == 0)
		return; 
	
	for (int i = 0; i < (int)move_ways.size(); ++i)
	{
		if (move_count[i] >= 3)
			return; 
		
		if (!results.empty() && (move_steps.size() >= results[0].size() || (i+1) >= results[0][move_steps.size()]))
			return; 
		
		c_clocks moved_clocks = clocks.move(i); 
		move_count[i]++;
		move_steps.push_back(i+1); 
		truncated_dfs(moved_clocks, depth-1, move_steps, results);
		move_steps.pop_back();
		move_count[i]--; 
	} 
}

void dfs_iterative_deepening(c_clocks& clocks, vector<vector<int> >& results)
{
	int max_depth = 11;
	//for (int depth = 0; depth < max_depth; ++depth)
	{
		vector<int> steps; 
		truncated_dfs(clocks, 11, steps, results);
		steps.clear();
		move_count = vector<int>(9, 0);
	}
}

void bfs(c_clocks& clocks, vector<vector<int> >& results)
{
	deque<c_clocks> q;
	vector<int> path;
	
	q.push_back(clocks);

	while (!q.empty())
	{
		c_clocks currrent = q.front();
		q.pop_front(); 

		if (currrent.is_all_12())
		{
			results.push_back(path);
			path.clear();
			q.clear(); 
			q.push_back(clocks);
			return;
		}
		
		for (int i = 0; i < (int)move_ways.size(); ++i)
		{
			if (!results.empty() && ((path.size() + 1) >= results[0].size() || (i+1) >= results[0][path.size()]))
				continue;
			
			c_clocks moved_clocks = clocks.move(i); 
			q.push_back(moved_clocks);
			path.push_back(i+1);
		}
	}
}

int main(int argc, char **argv)
{
	ifstream ifs("clocks.in");
	ofstream ofs("clocks.out");

	init_moves_table();
	
	c_clocks clocks = read_input_clocks(ifs); 
	vector<vector<int> > results;
	
	//bfs(clocks, results); 
	dfs_iterative_deepening(clocks, results);
	
	if (results.size() > 0)
	{
		for (size_t i = 0; i < results[0].size(); ++i)
		{
			ofs << results[0][i];
			if (i == results[0].size()-1)
				ofs << std::endl; 
			else 
				ofs << " "; 
		}
	}
	
	ifs.close();
	ofs.close();

	return 0; 
}