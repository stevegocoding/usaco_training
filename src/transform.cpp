/*
ID: stevego1
LANG: C++
PROG: transform
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std; 

typedef vector<vector<char> > board_t; 

void init_board(board_t& board, int n)
{
	board.resize(n); 
	for (int i = 0; i < n; ++i)
		board[i].resize(n); 
}

board_t rotate_90(const board_t& a)
{
	int n = (int)a.size();

	board_t b; 
	init_board(b, n); 
	for (int i = 0; i < n; ++i) 
	{
		for (int j = 0; j < n; ++j)
		{
			b[j][n-1-i] = a[i][j]; 
		}
	}
	return b; 
}

board_t reflect_h(const board_t& a)
{
	int n = (int)a.size(); 

	board_t b; 
	init_board(b, n);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			b[i][n-1-j] = a[i][j];  
		}
	}
	return b; 
}

bool is_equal(const board_t& a, const board_t& b)
{
	int n = (int)a.size(); 
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (a[i][j] != b[i][j])
				return false; 
		}
	}
	return true; 
}

void read_board(ifstream& ifs, int n, board_t& board)
{
	init_board(board, n);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			char ch; 
			ifs >> ch; 
			board[i][j] = ch;  
		}
	}
}

void print_board(const board_t& board)
{
	int n = (int)board.size();
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout << board[i][j] << " "; 
		}
		cout << endl; 
	}
	cout << endl;
} 

int main(int argc, char **argv)
{
    ifstream ifs("transform.in"); 
    ofstream ofs("transform.out"); 

    unsigned int dim; 
    ifs >> dim; 
	
	board_t origin, temp, final; 
	read_board(ifs, dim, origin);
	read_board(ifs, dim, final);  
	int change = 0; 

	if (is_equal(rotate_90(origin), final)) 
		change = 1; 
	else if (is_equal(rotate_90(rotate_90(origin)), final))
		change = 2; 
	else if (is_equal(rotate_90(rotate_90(rotate_90(origin))), final))
		change = 3; 
	else if (is_equal(reflect_h(origin), final))
		change = 4; 
	else if (is_equal(reflect_h(origin), final) || 
				is_equal(rotate_90(reflect_h(origin)), final) || 
				is_equal(rotate_90(rotate_90(reflect_h(origin))), final) || 
				is_equal(rotate_90(rotate_90(rotate_90(reflect_h(origin)))), final))
		change = 5; 
	else if (is_equal(origin, final))
		change = 6; 
	else 
		change = 7; 

	ofs << change << endl;
	ofs.close(); 
    
	return 0; 
}