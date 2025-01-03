#include <iostream>
#include <string>
using namespace std;

class Stock
{
    public:
        string symbol;
        double price;
        
        Stock()
        {
            symbol = "";
            price = 0.0;
        }

        Stock(string symbol, double price)
        {
            this->symbol = symbol;
            this->price = price;
        }

        ~Stock()
        {
            cout << "Stock object has been destroyed." << symbol << endl;
        }
};

int main()
{
    int size;

    cout << "How many stocks you have?";
    cin >> size;

    Stock stocks[size];

    cout << "Please Enter Stock name and Stock amount for total " << size << " stocks -" << endl;

    for(int i=0; i<size; i++)
    {
        string symbol;
        double price;

        cout << "Enter stock name: ";
        cin >> stocks[i].symbol;
        cout << "Enter stock price: ";
        cin >> stocks[i].price;
    }

    cout << "Total stocks we have in our databse:" << endl;

    for(int i=0; i<size; i++)
    {
        cout << stocks[i].symbol << " " << stocks[i].price << endl;
    }

    return 0;
}