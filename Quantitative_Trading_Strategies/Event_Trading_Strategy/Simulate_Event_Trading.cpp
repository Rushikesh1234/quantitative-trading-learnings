#include <iostream>
#include "NewsFetcher.h"

using namespace std;

int main()
{
    NewsFetcher newfetcher;
    string url = "http://127.0.0.1:5000/news";
    string news_data = newfetcher.fetch_news(url);
    parse_news(newfetcher.news_data, "Tesla");

    IBKR

}