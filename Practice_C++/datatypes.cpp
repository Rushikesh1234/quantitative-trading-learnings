#include <iostream>
#include <string>

using namespace std;

int main()
{
    string stock_name = "Ggl";
    int stock_volume = 1000;
    double stock_price = 150.75;
    bool isActive = false;

    cout << "Stock Name " << stock_name << endl;
    cout << "Stock Volume " << stock_volume << endl;
    cout << "Stock Price " << stock_price << endl;
    cout << "Stock isActive? " << (isActive ? "Yes" : "No") << endl;

    return 0;
}   