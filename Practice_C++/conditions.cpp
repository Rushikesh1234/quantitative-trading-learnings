#include <iostream>
#include <string>

using namespace std;

int main()
{
    int volume = 990;

    if(volume < 1000)
    {
        cout << "Stock volume " << volume << " is less than 1000" << endl;
    }
    else if (volume == 1000)
    {
        cout << "Stock volume " << volume << " is equal to 1000" << endl;
    }
    else
    {
        cout << "Stock volume " << volume << " is more than 1000" << endl;
    }
    

    return 0;
}