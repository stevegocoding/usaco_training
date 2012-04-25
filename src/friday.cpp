
/*
ID: stevego1
LANG: C++
PROG: friday
*/
#define JAN 0
#define FEB 1
#define MAR 2
#define APR 3
#define MAY 4
#define JUN 5
#define JUL 6
#define AUG 7
#define SEP 8
#define OCT 9
#define NOV 10
#define DEC 11

#define MON 0 
#define TUE 1 
#define WED 2
#define THU 3
#define FRI 4
#define SAT 5
#define SUN 6 

#include <fstream>

class c_date 
{

public:
    c_date(unsigned int y, unsigned int m, unsigned int d, unsigned int wd)
        : m_year(y)
        , m_month(m)
        , m_day(d)
        , m_week_day(wd)
    {}
    
    bool is_leap_year()
    {
        int frac = m_year % 400;
        if (frac == 0)
            return true;
        else
        {
            frac = m_year % 100;
            if (frac == 0) 
                return false; 
 
            frac = m_year % 4; 
            if (frac == 0)
                return true;
            else 
                return false; 
        }
    }

    void next_day()
    {
        unsigned int month_days = 0; 
        if (m_month == 1)
        {
            if (is_leap_year())
            {
                month_days = 29; 
            }
            else 
            {
                month_days = 28; 
            }
        }
        else if (m_month == 3 || m_month == 5 || m_month == 8 || m_month == 10)
        {
            month_days = 30; 
        }
        else 
            month_days = 31;

        unsigned int delta_month = (m_day + 1) / month_days;
        unsigned int delta_year = (m_month + delta_month) / 12;
        
        m_week_day = (m_week_day + 1) % 7;
        m_day = (m_day + 1) % month_days; 
        m_month = (m_month + delta_month) % 12;
        m_year = m_year + delta_year;
    }

    unsigned int get_year() { return m_year; }
    unsigned int get_month() { return m_month; }
    unsigned int get_day() { return m_day; } 
    unsigned int get_week_day() { return m_week_day; }
    
    unsigned int m_year;
    unsigned int m_month;
    unsigned int m_day;
    unsigned int m_week_day; 
}; 

int main(int argc, char **argv)
{
    std::ifstream ifs("friday.in"); 
    std::ofstream ofs("friday.out"); 
    
    unsigned int years = 0; 
    ifs >> years; 
    
    c_date date(1900, JAN, 0, MON); 
    unsigned int mon_13th = 0;
    unsigned int tue_13th = 0; 
    unsigned int wed_13th = 0; 
    unsigned int thu_13th = 0;
    unsigned int fri_13th = 0; 
    unsigned int sat_13th = 0; 
    unsigned int sun_13th = 0; 
    while ((date.get_year() - 1900) < years)
    {
        date.next_day();
        
        if (date.get_day() == 12) 
        {
            unsigned int wd = date.get_week_day(); 

            switch (wd)
            {
            case 0:
                mon_13th++; 
                break;
            case 1:
                tue_13th++;
                break;
            case 2:
                wed_13th++; 
                break; 
            case 3:
                thu_13th++; 
                break;
            case 4: 
                fri_13th++; 
                break;
            case 5:
                sat_13th++; 
                break; 
            case 6:
                sun_13th++; 
                break;
            }
        }
    }
    
    ofs << sat_13th << " " << sun_13th << " " << mon_13th << " " << tue_13th << " " << wed_13th << " " << thu_13th << " " << fri_13th; 
    ofs << std::endl; 
    return 0;
}