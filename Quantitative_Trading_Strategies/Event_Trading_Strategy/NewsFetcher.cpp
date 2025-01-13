
#include "NewsFetcher.h"

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

size_t WriteCallBack(void* contents, size_t size, size_t nmemb, string* output)
{
    size_t total_size = size * nmemb;
    output -> append((char*) contents, total_size);
    return total_size;
}

NewsFetcher::NewsFetcher(){}

string NewsFetcher::fetch_news(string url)
{
    CURL* curl;
    CURLcode res;
    string response;

    curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
        {
            cerr << "CURL Error " << curl_easy_strerror(res) << endl;
        }
        curl_easy_cleanup(curl);
    }

    return response;
}

void NewsFetcher::parse_news(string news_data, string company)
{
    auto news_json = json::parse(news_data);
    for(const auto& item : news_json)
    {
        string title = item["title"];
        string description = item["description"];
        
        if(title.find(company) != string::npos || description.find(company) != string::npos)
        {
            std::cout << "Title: " << title << "\nDescription: " << description << std::endl;
        }
    }
}

/*
int main()
{
    string url = "http://127.0.0.1:5000/news";
    string news_data = fetch_news(url);
    parse_news(news_data, "Tesla");
    return 0;
}
*/