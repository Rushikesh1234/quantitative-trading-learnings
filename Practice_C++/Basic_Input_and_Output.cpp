#include <iostream>
#include <iomanip>
#include <string>

int main()
{
    int a, b, c;

    // cin, cout
    std::cout << "Enter any 2 number: ";
    std::cin >> a >> b;
    c = a + b;
    std::cout << "Addition is " << c << std::endl;

    // cerr
    std::cerr << "Error found : " << std::endl;

    // clog
    std::clog << "Calculated value for " << a << "& " << b << " is " << c << std::endl;

    // setw, left, right
    std::cout << std::setw(10) << "Title" << std::setw(10) << "Value" << std::endl;
    std::cout << std::setw(10) << "Ggl" << std::setw(10) << "10.05" << std::endl;
    std::cout << std::left << std::setw(10) << "Ggl" << std::right << std::setw(10) << "10.05" << std::endl;

    // setprecision
    double val = 0.523423423423;
    std::cout << "Output for double val is: " << std::setprecision(5) << val << std::endl;

    // fixed point
    double val2 = 0.423431231232131123;
    std::cout << "Fixed point " << val2 << std::fixed << std::setprecision(6) << val2 << std::endl;
    double val3 = 0.42342341313131321312;
    std::cout << "Effect of Fixed point " << val3 << std::endl;

    return 0;
}