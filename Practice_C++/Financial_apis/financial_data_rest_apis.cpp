#include <curl/curl.h>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

size_t WriteCallBack(void* contents, size_t size, size_t nmemb, string* output)
{
    size_t total_size = size * nmemb;
    output -> append((char*) contents, total_size);
    return total_size;
}

void http_get_request(string url_get)
{
    CURL* curl;
    CURLcode res;
    string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url_get.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
        {
            cerr << "GET Request Failed: " << curl_easy_strerror(res) << endl;
        }
        else
        {
            try {
                cout << "Response: " << json::parse(readBuffer).dump(4) << endl;
            } catch (const json::parse_error& e) {
                cerr << "Error parsing JSON response: " << e.what() << endl;
                cerr << "Raw Response: " << readBuffer << endl;
            }
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

void http_post_request(string url_post, const string& json_payload)
{
    CURL* curl;
    CURLcode res;
    string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl)
    {
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url_post.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
        {
            cerr << "POST response failed: " << curl_easy_strerror(res) << endl;
        }
        else
        {
            try {
                cout << "Response: " << json::parse(readBuffer).dump(4) << endl;
            } catch (const json::parse_error& e) {
                cerr << "Error parsing JSON response: " << e.what() << endl;
                cerr << "Raw Response: " << readBuffer << endl;
            }
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

int main()
{


    cout << "Request Historical Data" << endl << endl;
    string url_get_hisory_data = "http://127.0.0.1:5000/iserver/marketdata/history";
    http_get_request(url_get_hisory_data);
    cout << endl << endl;

    cout << "Initialize Brokerage Session" << endl << endl;
    string url_post("http://127.0.0.1:5000/iserver/auth/ssodh/init");
    string json_payload = R"({"publish": true, "compete": true})";
    http_post_request(url_post, json_payload);
    cout << endl << endl;

    cout << "Signatures and Owners for valid accountId" << endl << endl;
    string accountId1 = "U1234567";
    string url_get_accounts1 = "http://127.0.0.1:5000/iserver/" + accountId1 + "/signatures-and-owners";
    http_get_request(url_get_accounts1);
    cout << endl << endl;

    cout << "Signatures and Owners for invalid accountId" << endl << endl;
    string accountId2 = "A52342342";
    string url_get_accounts2 = "http://127.0.0.1:5000/iserver/" + accountId2 + "/signatures-and-owners";
    http_get_request(url_get_accounts2);
    cout << endl << endl;

    return 0;
}


// g++ -o financial_data_rest_apis financial_data_rest_apis.cpp -std=c++11 -lcurl