#include <iostream>

using namespace std;

int main()
{
    int cycle1, yearsAgo1, cycle2, yearsAgo2;
    cin>> yearsAgo1>> cycle1>> yearsAgo2>> cycle2;
    int year = 1;
    
    while( year <= 5000 && ( (year + yearsAgo1)%cycle1 != 0 || (year + yearsAgo2)%cycle2 != 0 )) 
    {
        year++;
    }
    
    cout<< year<< endl;


    return 0;
}
