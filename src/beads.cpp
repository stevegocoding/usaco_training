/*
ID: stevego1
LANG: C++
PROG: beads
*/

#define WHITE 'w'
#define RED 'r'
#define BLUE 'b' 

#include <iostream> 
#include <fstream> 
#include <string>

using namespace std;
int g_num_beads = 0; 
string g_beads;

int g_cur_brk = 0; 
int g_max_total = 0;

int prev(int i)
{
    int prev = (i == 0)? (g_num_beads - 1) : (i - 1) % g_num_beads;
    return prev; 
}

int next(int i)
{
    int next = (i + 1) % g_num_beads; 
    return next; 
}

char prev_bead(int i)
{
    int prev = (i == 0)? (g_num_beads - 1) : (i - 1) % g_num_beads;
    return g_beads[prev];
}

char next_bead(int i)
{
    int next = (i + 1) % g_num_beads; 
    return g_beads[next]; 
}

int main(int argc, char **argv)
{
    ifstream ifs("beads.in");
    ofstream ofs("beads.out"); 
    ifs >> g_num_beads; 
    ifs >> g_beads;

    while (g_cur_brk < g_num_beads)
    {   
        int l_total = 0;
        int r_total = 0; 
        int runner = prev(g_cur_brk); 
        char ch = prev_bead(g_cur_brk); 
        char prev_ch = ch;
        char r_or_b = ch;
        while (ch == prev_ch || ch == WHITE || r_or_b == WHITE || (prev_ch == WHITE && ch == r_or_b) )
        {
            if (ch != WHITE)
                r_or_b = ch; 
            prev_ch = ch; 
            ch = prev_bead(runner);
            runner = prev(runner);
            l_total++; 
            if (l_total >= g_num_beads)
                break;
        }
        runner = g_cur_brk; 
        ch = g_beads[g_cur_brk];
        prev_ch = ch; 
        while (ch == prev_ch || ch == WHITE || r_or_b == WHITE || (prev_ch == WHITE && ch == r_or_b) )
        {
            if (ch != WHITE)
                r_or_b = ch; 
            prev_ch = ch;
            ch = next_bead(runner);
            runner = next(runner); 
            r_total++;
            if (r_total >= g_num_beads)
                break;
        }
        
        if (l_total + r_total >= g_num_beads)
        {
            g_max_total = g_num_beads; 
            break;
        }

        if (l_total + r_total > g_max_total)
            g_max_total = l_total + r_total; 

        // g_cur_brk += runner;
        g_cur_brk += r_total; 
    } 

    ofs << g_max_total << endl;
    
    return 0; 
}