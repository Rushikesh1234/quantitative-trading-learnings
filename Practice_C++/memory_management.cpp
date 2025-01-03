// Efficient memory management minimizes latency, reduces memory fragmentation, and ensures stability under heavy loads.

#include <iostream>
#include <string>
#include <memory>

using namespace std;

// Memory management basics - Static memory allocations
string company_name = "SQL";

void testfunctionA()
{
    int a = 10;
    cout << a << endl;
}

void testfunctionB()
{
    int b = 20;
    testfunctionA();
    cout << b << endl;
}

struct Trader
{
    public:
        string name;

        Trader(string name)
        {
            this->name = name;
        }

        string getname()
        {
            return name;
        }
};

int main()
{
    
    // Memory management basics - Stack memory allocations

    cout << "Memory management basics - Stack memory allocations" << endl;
    testfunctionB(); // stack frames will be created for testfunctionA and testfunctionB and destroyed after out of scope, after this line
    cout << endl;

    // Memory management basics - Heap memory allocations
    cout << "Memory management basics - Heap memory allocations" << endl;
    int* prices = new int(100); // Dynamically allocate memory
    cout << "Price " << *prices << endl;
    delete prices;
    cout << endl;

    //Manual memory management problems - memory leaks, dangling pointers or fragmentation
    // To avoid this prefer below few items

    // Smart pointers - sole ownership, delete after out of scope
    // example 1 - with struct
    cout << "access struct with smart pointers" << endl;
    unique_ptr<Trader> trader = make_unique<Trader>("Rushikesh");
    cout << trader->getname() << endl;
    cout << endl;

    // example 2 - with array
    cout << "access array with smart pointers" << endl;
    unique_ptr<int> stock = make_unique<int>(100);
    cout << "Array allocated using smart pointer - " << *stock << endl;
    cout << endl;

    // Shared pointers - shared ownership, delete after last shared_ptr is out of scope
    // example 1 - shared_ptr with struct
    cout << "access struct with shared pointers" << endl;
    shared_ptr<Trader> ptr1 = make_shared<Trader>("SIG");
    shared_ptr<Trader> ptr2 = ptr1;
    cout << "Access getname from ptr1 " << ptr1->getname() << endl;
    cout << "Access getname from ptr2 " << ptr2->getname() << endl;
    cout << endl;

    // Weak pointers - not owneing a refernce to shared pointer, prevents a circular reference that can lead to memory leaks, very helpful to monitor resource, not to use them
    // example - weak_ptr with struct
    cout << "access struct with weak pointers" << endl;
    shared_ptr<Trader> ptr3 = make_shared<Trader>("GGL");
    weak_ptr<Trader> ptr4 = ptr3;
    cout << "Access getname from ptr3 " << ptr3->getname() << endl;
    if(auto shared = ptr4.lock())
    {
        cout << "Access getname from ptr4 " << ptr3->getname() << endl;
    }
    cout << endl;
    
    return 0;
}