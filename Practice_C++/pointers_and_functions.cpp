#include <iostream>
#include <limits>

using namespace std;

// Passing pointers to functions as parameter
void updatePrice(double* price)
{
    *price += 10;
}

// Passing array pointers to functions as parameter
double calcAverage(double* prices, int size)
{
    double avg = 0.0;
    for(int i=0; i<size; i++)
    {
        avg += prices[i];
    }

    return avg / size;
}

void swapUsingPointer(double* ptrStock1, double* ptrStock2)
{
    double temp = *ptrStock1;
    *ptrStock1 = *ptrStock2;
    *ptrStock2 = temp;
}

double* allocateSpace(int size)
{
    return new double[size];
}

double findMinStock(double* stocks, int size)
{
    double minStock = numeric_limits<double>::max();

    for(int i=0; i<size; i++)
    {
        if(minStock > stocks[i])
        {
            minStock = stocks[i];
        }
    }

    return minStock;
}

double findMaxStock(double* stocks, int size)
{
    double maxStock = numeric_limits<double>::min();

    for(int i=0; i<size; i++)
    {
        if(maxStock < stocks[i])
        {
            maxStock = stocks[i];
        }
    }

    return maxStock;
}

void stockCalculations()
{
    int size;
    cout << "Enter total stocks available " << endl;
    cin >> size;

    double* stocks = allocateSpace(size);

    cout << "Enter " << size << " stock values " << endl;
    for(int i=0; i<size; i++)
    {
        cin >> stocks[i];
    }
    cout << endl;

    double average = calcAverage(stocks, size);
    cout << "Total average " << average << endl;

    double minStockVal = findMinStock(stocks, size);
    cout << "Min Stock " << minStockVal << endl;

    double maxStockVal = findMaxStock(stocks, size);
    cout << "Max Stock " << maxStockVal << endl;
}

int main()
{
    // Passing pointers to functions as parameter
    cout << "Passing pointers to functions as parameter" << endl;
    double stockPrice = 190.10;
    double* price = &stockPrice;

    cout << "StockPrice is " << stockPrice << endl;

    updatePrice(price);
    cout << "Update StockPrice is " << stockPrice << endl << endl;

    // Passing array pointers to functions as parameter
    cout << "Passing array pointers to functions as parameter" << endl;
    double stockPrices[5] = {190.10, 185.10, 176.10, 120.04, 140.40};
    double *prices = stockPrices;
    int size = sizeof(stockPrices) / sizeof(stockPrices[0]);
    cout << "Average of stockPrices: " << calcAverage(prices, size) << endl << endl;

    // Swap two stock prices using pointers as funcation parameters
    double stock1 = 101.03; double* ptrStock1 = &stock1;
    double stock2 = 202.22; double* ptrStock2 = &stock2;

    cout << "Before swap - stock1 " << stock1 << " and stock2 " << stock2 << endl;
    swapUsingPointer(ptrStock1, ptrStock2);
    cout << "After swap - stock1 " << stock1 << " and stock2 " << stock2 << endl << endl;

    // Returning pointers from functions
    size = 5;    
    double* stocks = allocateSpace(size);

    for(int i=0; i<size; i++)
    {
        stocks[i] = 100 + i;
    }

    cout << "Dynamic array using pointer " << endl;

    for(int i=0; i<size; i++)
    {
        cout << stocks[i] << " ";
    }
    cout << endl << endl;

    // work with pointer and functions for stocks analyzer

    stockCalculations();
    cout << endl << endl;
    return 0;
}