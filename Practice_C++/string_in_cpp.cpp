#include <iostream>
#include <string>

int main()
{
    // strings - one word
    std::string info;
    std::cout << "Enter your name : ";
    std::cin >> info;

    // strings - complete line
    std::cout << "How can i help you?" << std::endl;
    std::getline(std::cin, info);
    std::cout << "You asked: " << info << " And the answer is: Sorry this is not chatgpt, find your answer by yourself." << std::endl;

    // string concat
    std::string symbol = "Ggl";
    std::string sector = "Technolgy";

    std::string stock_information = "Symbol is " + symbol + " and from " + sector + " sector";
    std::cout << "Stock Information " << stock_information << std::endl;

    // string length
    std::cout << "Symbol leangth " << stock_information.length() << std::endl;

    // string first index
    std::cout << "Second last string in stock_information " << stock_information[stock_information.length()-2] << std::endl;

    // string find
    int index = stock_information.find("Ggl");
    std::cout << "I found index for value Ggl: " << index << std::endl;
    std::cout << "We found this value " << stock_information.substr(index, 3) << std::endl;

    // string replace
    stock_information.replace(index, 3, "Mic");
    std::cout << "After replacement " << stock_information << std::endl;

    // string compare
    if(symbol == "Mic" || symbol.compare("Mic"))
    {
        std::cout << "Found stock name" << std::endl;
    }
    else
    {
        std::cout << "Not found" << std::endl;
    }



    return 0;
}