/*
ID: stevego1
LANG: C++
PROG: milk2
*/

#include <fstream>
#include <algorithm> 
#include <vector>

using namespace std; 

enum time_point_type 
{
    MILK_START = 0,
    MILK_END
};

struct time_point 
{
    unsigned int time; 
    time_point_type t;
    time_point(unsigned int _time, time_point_type _t)
        : time(_time)
        , t(_t)
    {} 
};

bool time_point_comp(const time_point& t1, const time_point& t2)
{
    return (t1.time < t2.time) || (t1.time == t2.time && t1.t < t2.t); 
}

int main(int argc, char **argv)
{
    ifstream ifs("milk2.in"); 
    ofstream ofs("milk2.out"); 
    
    int num_cows = 0; 
    ifs >> num_cows; 
    
    vector<time_point> time_points; 
    time_points.reserve(num_cows * 2); 
    
    for (int i = 0; i < num_cows * 2; ++i)
    {
        unsigned int time;
        ifs >> time; 
        time_point_type t = (time_point_type)(i % 2);
        time_points.push_back(time_point(time, t));
    }
    
    sort(time_points.begin(), time_points.end(), time_point_comp); 
    
    vector<time_point>::iterator it = time_points.begin(); 
    int longest_in_milk_interval = 0;
    int longest_non_milk_interval = 0;
    int in_milk_cnt = 0; 
    int milk_start_time = 0;
    int milk_end_time = 0;
    for(; it != time_points.end(); ++it)
    {
        if (it->t == MILK_START)
        {
            if (in_milk_cnt == 0) 
            {
                milk_start_time = it->time; 
                if (it != time_points.begin() && milk_start_time - milk_end_time > longest_non_milk_interval)
                    longest_non_milk_interval = milk_start_time - milk_end_time; 
            }
            in_milk_cnt++; 
        }
        else if (it->t == MILK_END)
        {
            in_milk_cnt--; 
            if (in_milk_cnt == 0)
            {
                milk_end_time = it->time; 
                if (milk_end_time - milk_start_time > longest_in_milk_interval)
                    longest_in_milk_interval = milk_end_time - milk_start_time;
            }
        }    
    }
    
    ofs << longest_in_milk_interval << " " << longest_non_milk_interval << endl; 
    
    return 0; 
}