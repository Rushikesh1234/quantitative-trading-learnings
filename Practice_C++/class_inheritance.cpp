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

        string display() const
        {
            return symbol + " " + to_string(price);
        }
};

class TechStock : public Stock
{
    public:
        string companyName;
        TechStock(string companyName, string symbol, double price) : Stock(symbol, price)
        {
            this->companyName = companyName;
        }

        void displayCompanyInfo() const
        {
            cout << "Company Information " << companyName << " " << display() << endl;
        }
};

int main()
{
    TechStock google("Google", "ggl", 127.00);
    TechStock microsoft("Microsoft", "mic", 567.00);
    TechStock sig("SIG", "sig", 927.00);
    
    google.displayCompanyInfo();
    microsoft.displayCompanyInfo();
    sig.displayCompanyInfo();
    
    return 0;
}
