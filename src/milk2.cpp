/*
ID: stevego1
LANG: C++
PROG: milk2
*/

#include <fstream>
#include <algorithm> 
#include <vector>

using namespace std; 

struct milk_interval
{
    unsigned int start; 
    unsigned int end;

    milk_interval(unsigned int _start = 0, unsigned int _end = 0) 
        : start(_start)
        , end(_end)
    {}

    void merge(const milk_interval& interval)
    {
        start = min(start, interval.start); 
        end = max(end, interval.end); 
    }
};

int main(int argc, char **argv)
{
    ifstream ifs("milk2.in"); 
    ofstream ofs("milk2.out"); 
    
    int num_cows = 0; 
    ifs >> num_cows; 
    vector<milk_interval> intervals; 
    intervals.reserve(num_cows);
    
    for (int i = 0; i < num_cows; ++i)
    {
        unsigned int start = 0;
        unsigned int end = 0;
        ifs >> start >> end;
        intervals.push_back(milk_interval(start, end));
    }
    
    vector<milk_interval>::iterator it = intervals.begin(); 
    milk_interval longest = *it;
    milk_interval temp = *it; 
    int longest_no_milk = 0; 
    int temp2 = 0; 
    unsigned int minimum = 100000; 
    unsigned int maximum = 0; 
    for (++it; it != intervals.end(); ++it)
    {
        /*
        if ((temp2 = (it->start - temp.end)) > 0)
        {
            if (temp.end - temp.start > longest.end - longest.start)
                longest = temp;
            temp = *it; 
            longest_no_milk = max(temp2, longest_no_milk);
            continue;
        } 
        else 
        {
            if (it->start <= longest.)
                temp.merge(*it); 
        }
        */

        int d0 = it->start - temp.end; 
        int d1 = temp.start - it->end; 
        temp2 = max(d0, d1); 
        minimum = min(minimum, it->start); 
        maximum = max(maximum, it->end); 
        
        if (d0 < 0 || d1 < 0) 
        {
            temp.merge(*it);
            if (temp.end - temp.start > longest.end - longest.start)
                longest = temp;
        }
        else 
        {
            if (temp.end - temp.start > longest.end - longest.start)
                longest = temp;
            if (temp2 > longest_no_milk)
                longest_no_milk = temp2; 
            temp = *it;
            continue;
        }
    }

    if (longest.start <= minimum && longest.end >= maximum) 
        longest_no_milk = 0; 
   
    ofs << longest.end-longest.start << " "; 
    ofs << longest_no_milk;
    ofs << endl; 

    return 0; 
}