#include <iostream>

using namespace std;

int main()
{
    int cycle1, yearsAgo1, cycle2, yearsAgo2;
    cin>> yearsAgo1>> cycle1>> yearsAgo2>> cycle2;
    int year;
    int jump;
    if( cycle1 > cycle2) {
        jump = cycle1;
        year = cycle1 - yearsAgo1;
        if( year == 0) year += cycle1;
    } else {
        jump = cycle2;
        year = cycle2 - yearsAgo2;
        if( year == 0) year += cycle2;
    }
    
    while( year <= 5000 && ( (year + yearsAgo1)%cycle1 != 0 || (year + yearsAgo2)%cycle2 != 0 )) 
    {
        year+=jump;
    }
    
    cout<< year<< endl;

    return 0;
}
