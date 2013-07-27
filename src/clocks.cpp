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
	
	void move(int move_idx)
	{
		for (size_t i = 0; i < move_ways[move_idx].size(); ++i)
		{
			int row = move_ways[move_idx][i]/3;
			int col = move_ways[move_idx][i]%3;
			m_clocks[row][col] += 3;
			if (m_clocks[row][col] > 12)
				m_clocks[row][col] -= 12;
		}
	}

	void undo_move(int move_idx)
	{
		for (size_t i = 0; i < move_ways[move_idx].size(); ++i)
		{
			int row = move_ways[move_idx][i]/3;
			int col = move_ways[move_idx][i]%3;
			m_clocks[row][col] -= 3;
			if (m_clocks[row][col] <= 0)
				m_clocks[row][col] += 12;
		}
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

vector<int> best_moves(9, 0);
int n_best_moves = 0; 
void dfs(c_clocks& clocks, int move_idx, vector<int>& move_reps)
{
	if (move_idx == 9)
	{
		if (clocks.is_all_12())
		{
			int n = 0; 
			for (int i = 0; i < 9; ++i)
			{
				n += move_reps[i];
			}
			if (n_best_moves == 0 || n < n_best_moves)
			{
				n_best_moves = n;
				for (int i = 0; i < 9; ++i)
					//std::copy(move_reps.begin(), move_reps.end(), best_moves); 
					best_moves[i] = move_reps[i];
			}	
		}
		return; 
	}

	for (int rep = 3; rep >= 0; --rep)
	{
		for (int i = 0; i < rep; ++i)
		{
			clocks.move(move_idx); 
		}
		
		move_reps[move_idx] = rep;
		
		dfs(clocks, move_idx+1, move_reps);

		// Undo move 
		for (int i = 0; i < rep; ++i)
		{
			clocks.undo_move(move_idx); 
		}
	}
}

int main(int argc, char **argv)
{
	ifstream ifs("clocks.in");
	ofstream ofs("clocks.out");

	init_moves_table();
	
	c_clocks clocks = read_input_clocks(ifs);

	vector<int> move_reps(9, 0);
	dfs(clocks, 0, move_reps);

	string sep = "";
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < best_moves[i]; ++j)
		{
			ofs << sep.c_str() << i + 1;
			sep = " ";
		}
	}

	ofs << std::endl;

	ifs.close();
	ofs.close();

	return 0; 
}
