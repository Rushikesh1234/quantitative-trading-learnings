#include <iostream>
using namespace std;

// pointer dynamic array allocation adn deallocation
int main()
{
    int size;
    cout << "please enter stock size:";
    cin >> size;
    cout << endl;

    int* array = new int[size];
    cout << "Please enter all " << size << " stock value" << endl;
    for(int i =0; i<size; i++)
    {
        cin >> array[i];
    }
    cout << endl;
    cout << "Stock amount you have enterd: " << endl;
    for(int i =0; i<size; i++)
    {
        cout << array[i] << endl;
    }

    cout << "After deletion of array allocation: " << endl;
    delete[] array;

    cout << "Stock amount you have enterd: " << endl;
    for(int i =0; i<size; i++)
    {
        cout << array[i] << endl;
    }

    array = nullptr;

    cout << "Stock amount you have enterd: " << endl;
    for(int i =0; i<size; i++)
    {
        cout << array[i] << endl;
    }

    return 0;
}