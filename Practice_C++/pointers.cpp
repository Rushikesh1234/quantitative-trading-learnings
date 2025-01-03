#include <iostream>

using namespace std;

// Basics of pointers
int main()
{

    int a = 10;
    int* ptr = &a;

    cout << "value of a: " << a << endl;
    cout << "value of ptr: " << ptr << endl;
    cout << "value of address a " << &a << endl;
    cout << "value of ptr pointer " << *ptr << endl;
    cout << "value of ptr address " << &ptr << endl;

    cout << endl;

    double b = 100.05;
    double* ptr1 = &b;

    cout << "value of b: " << b << endl;
    cout << "value of ptr1: " << ptr1 << endl;
    cout << "value of address b " << &b << endl;
    cout << "value of ptr1 pointer " << *ptr1 << endl;

    cout << "after delete allocation " << endl;
    delete ptr1;
    ptr1 = nullptr;
    cout << "value of ptr1: " << ptr1 << endl;

    return 0;
}