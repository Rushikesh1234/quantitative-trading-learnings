#include <iostream>
#include <string>

using namespace std;

int main()
{
    // For loop 

    for(int i=0; i<5; i++)
    {
        cout << "Day " << i+1 << " Trade In" << endl;
    }

    // While loop
    int i=0;
    int sum = 0;
    while(i < 10)
    {
        sum += i;
        i++;
    }
    cout << "Total sum is: " << sum << endl;

    // Do while
    int j = 1;
    int total = 0;
    do
    {
        total += j;
        j++;
    } while (j < 10);
    cout << "Total sum is: " << total << endl;

    return 0;
}