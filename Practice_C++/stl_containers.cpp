#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Stock
{
    public:
        string symbol;
        vector<double> last_five_days_price;

        Stock()
        {
            symbol = "";
        }

        Stock(string symbol)
        {
            this->symbol = symbol;
        }

        void setPrice(double price)
        {
            last_five_days_price.push_back(price);
        }

        string getSymbol()
        {
            return symbol;
        }

        void getLastFiveDaysPrice()
        {
            for(double price : last_five_days_price)
            {
                cout << price << " ";
            }
            cout << endl;
        }

};

int main()
{
    cout << endl; 
    
    map<string, Stock> companyProfile;

    Stock google("ggl");
    google.setPrice(232.22);
    google.setPrice(231.22);
    google.setPrice(234.21);
    google.setPrice(223.11);
    google.setPrice(234.21);

    Stock tesla("tes");
    tesla.setPrice(132.22);
    tesla.setPrice(131.42);
    tesla.setPrice(134.26);
    tesla.setPrice(123.91);
    tesla.setPrice(134.41);

    Stock sig("sig");
    sig.setPrice(432.22);
    sig.setPrice(431.42);
    sig.setPrice(434.26);
    sig.setPrice(423.91);
    sig.setPrice(434.41);

    companyProfile["Google"] = google;
    companyProfile["Tesla"] = tesla;
    companyProfile["SIG"] = sig;
    
    for(const auto& pair : companyProfile)
    {
        string companyName = pair.first;
        Stock profile = pair.second;

        cout << "Company Name: " << companyName << endl;

        cout << "Symbol: " << profile.getSymbol() << endl;

        cout << "Max Price within last 5 day prices: " << *max_element(profile.last_five_days_price.begin(), profile.last_five_days_price.end()) << endl;
        
        cout << "Min Price within last 5 day prices: " << *min_element(profile.last_five_days_price.begin(), profile.last_five_days_price.end()) << endl;
        
        cout << "Last 5 days prices: ";
        profile.getLastFiveDaysPrice();

        cout << "After sorted those 5 days prices: ";
        sort(profile.last_five_days_price.begin(), profile.last_five_days_price.end());
        profile.getLastFiveDaysPrice();

        cout << endl;
    }



    return 0;
}