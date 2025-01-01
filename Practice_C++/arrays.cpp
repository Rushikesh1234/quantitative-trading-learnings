#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
    // Array declaration manually
    string stock_name[5] = {"ggl", "amz", "mac", "met", "tes"};
    for(int i=0; i<5; i++)
    {
        cout << stock_name[i] << endl;
    }

    // Array user input
    int* stock_price = new int[5];
    cout << "Please enter stock price for all 5 sotcks: " << endl;

    int sum_Of_Stocks = 0;

    for(int i=0;i<5; i++)
    {
        cout << stock_name[i] << " ";
        cin >> stock_price[i];
        sum_Of_Stocks += stock_price[i];
    }
    cout << "Sum of all Stocks " << sum_Of_Stocks << " and Average of all stocks " << (sum_Of_Stocks / 5) << endl;

    // Array sort
    sort(stock_price, stock_price + 5);

    // Array iterate
    cout << setw(10) << "Stock Name" << setw(15) << "Stock Price" << endl;
    for(int i=0; i<5; i++)
    {
        cout << setw(10) << stock_name[i] << setw(10) << stock_price[i] << endl;
    }



    return 0;
}