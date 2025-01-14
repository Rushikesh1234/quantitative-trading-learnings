#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <sstream>

using namespace std;
using json = nlohmann::json;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

class ChatGPT_Analyzer
{
public:
    ChatGPT_Analyzer()
    {
        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();
    }

    ~ChatGPT_Analyzer()
    {
        if (curl) {
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
    }

    string check_stock_signal(const string& news_for_profile, const string& profile)
    {
        try
        {
            string news = news_for_profile;
            stringstream input_stream;
            input_stream << "Please analyze below news for " << profile 
                         << " and give me signal whether I should buy or sell. Please remember, I need only value 'BUY' or 'SELL' in output. No other text. Thank you. News are "
                         << news;
            string input = input_stream.str();

            string response;

            if (curl)
            {
                curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");

                const char* api_key = getenv("OPENAI_API_KEY");
                if (api_key == nullptr)
                {
                    return "API key not set in environment variables.";
                }

                struct curl_slist* headers = NULL;
                headers = curl_slist_append(headers, "Content-Type: application/json");
                string auth_header = "Authorization: Bearer " + string(api_key);
                headers = curl_slist_append(headers, auth_header.c_str());

                json payload = {
                    {"model", "gpt-3.5-turbo"},
                    {"messages", {{{"role", "user"}, {"content", input}}}},
                    {"temperature", 0.7}
                };

                string payload_str = payload.dump();

                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload_str.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

                CURLcode res = curl_easy_perform(curl);
                if (res != CURLE_OK)
                {
                    cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
                    return "Error during API request.";
                }
                
                json json_response = json::parse(response);

                if (json_response.contains("choices") && !json_response["choices"].empty())
                {
                    return json_response["choices"][0]["message"]["content"].get<string>();
                }
                else
                {
                    return "No valid response";
                }
            }
            return "Curl initialization failed.";
        }
        catch (const exception& e)
        {
            cerr << "Error: " << e.what() << endl;
            return "Unable to analyze stock information.";
        }
    }

private:
    CURL* curl;
};

/*
int main()
{
    ChatGPT_Analyzer analyzer;
    string news = "The stock price has risen due to a positive earnings report.";
    string profile = "Tech Stocks";
    string signal = analyzer.check_stock_signal(news, profile);
    cout << "Trading Signal: " << signal << endl;
    return 0;
}
*/