/*
ID: stevego1
LANG: C++
PROG: transform
*/

#include <fstream>
#include <vector>

using namespace std;

bool varify_rotate_90(const vector<char>& before, const vector<char>& after, unsigned int dim)
{
    for (unsigned int i = 0; i < dim*dim; ++i)
    {
        int row = i / dim - (int)(dim / 2); 
        int col = i % dim - (int)(dim / 2); 

        int t_row = col + (int)(dim / 2);
        int t_col = -row + (int)(dim / 2); 
        
        if (before[i] != after[t_row * dim + t_col]) 
            return false; 
    }
    return true; 
}

bool varify_rotate_180(const vector<char>& before, const vector<char>& after, unsigned int dim)
{
    for (unsigned int i = 0; i < dim*dim; ++i)
    {
        int row = i / dim - (int)(dim / 2); 
        int col = i % dim - (int)(dim / 2); 

        int t_row = -row + (int)(dim / 2);
        int t_col = -col + (int)(dim / 2);
        
        if (before[i] != after[t_row * dim + t_col]) 
            return false; 
    }
    return true; 
}

bool varify_rotate_270(const vector<char>& before, const vector<char>& after, unsigned int dim)
{
    for (unsigned int i = 0; i < dim*dim; ++i)
    {
        int row = i / dim - (int)(dim / 2); 
        int col = i % dim - (int)(dim / 2); 

        int t_row = -col + (int)(dim / 2);
        int t_col = row + (int)(dim / 2);
        
        if (before[i] != after[t_row * dim + t_col]) 
            return false; 
    }
    return true; 
}

bool varify_reflect(const vector<char>& before, const vector<char>& after, unsigned int dim)
{
    for (unsigned int i = 0; i < dim*dim; ++i)
    {
        int row = i / dim - (int)(dim / 2); 
        int col = i % dim - (int)(dim / 2); 

        int t_row = -row + (int)(dim / 2);
        int t_col = col + (int)(dim / 2);
        
        if (before[i] != after[t_row * dim + t_col]) 
            return false; 
    }
    return true; 
}

bool varify_combination(const vector<char>& before, const vector<char>& after, unsigned int dim)
{
    int which_rotate = -1;
    for (unsigned int i = 0; i < dim*dim; ++i)
    {
        int row = i / dim - (int)(dim / 2); 
        int col = i % dim - (int)(dim / 2); 

        int t_row = -row;
        int t_col = col;

        int tt_row_90 = t_col + (int)(dim / 2); 
        int tt_col_90 = -t_row + (int)(dim / 2);

        int tt_row_180 = -t_row + (int)(dim / 2); 
        int tt_col_180 = -t_col + (int)(dim / 2); 

        int tt_row_270 = -t_col + (int)(dim / 2); 
        int tt_col_270 = t_row + (int)(dim / 2); 
        
        if (before[i] == after[tt_row_90 * dim + tt_col_90]) 
        {
            if (which_rotate == -1)
            {
                which_rotate = 0;
                continue;
            }
            else if (which_rotate != 0) 
                return false;
            else 
                continue; 
        }
        else if (before[i] == after[tt_row_180 * dim + tt_col_180])
        {
            if (which_rotate == -1)
            {
                which_rotate = 1;
                continue;
            }
            else if (which_rotate != 1) 
                return false;
            else 
                continue; 
        }
        else if (before[i] == after[tt_row_270 * dim + tt_col_270])
        {
            if (which_rotate == -1)
            {
                which_rotate = 2;
                continue;
            }
            else if (which_rotate != 2) 
                return false;
            else 
                continue; 
        }
        else 
            return false;
    }
    return true; 
}

bool varify_no_changes(const vector<char>& before, const vector<char>& after, unsigned int dim)
{
    for (unsigned int i = 0; i < dim*dim; ++i)
    {   
        if (before[i] != after[i]) 
            return false; 
    }
    return true; 
}

int main(int argc, char **argv)
{
    ifstream ifs("transform.in"); 
    ofstream ofs("transform.out"); 

    unsigned int dim; 
    ifs >> dim; 

    vector<char> before;
    vector<char> after;
    before.reserve(dim*dim); 
    after.reserve(dim*dim); 

    for (unsigned int i = 0; i < dim * dim; ++i)
    {
        char ch;
        ifs >> ch;
        before.push_back(ch);
    }
    for (unsigned int j = 0; j < dim * dim; ++j)
    {
        char ch;
        ifs >> ch;
        after.push_back(ch);
    }

    unsigned int result = 0;
    if (varify_rotate_90(before, after, dim))
        result = 1;
    else if (varify_rotate_180(before, after, dim))
        result = 2; 
    else if (varify_rotate_270(before, after, dim))
        result = 3; 
    else if (varify_reflect(before, after, dim))
        result = 4; 
    else if (varify_combination(before, after, dim))
        result = 5; 
    else if (varify_no_changes(before, after, dim))
        result = 6;
    else 
        result = 7; 

    ofs << result << endl; 
   
    return 0; 
}