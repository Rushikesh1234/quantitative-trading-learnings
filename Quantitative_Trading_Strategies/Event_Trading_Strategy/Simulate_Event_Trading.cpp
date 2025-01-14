#include <iostream>
#include "News_Fetcher.cpp"
#include "MOCK_IBKR_TWS.cpp"
#include "ChatGPT_Analyzer.cpp"

using namespace std;

int main()
{
    News_Fetcher news_fetcher;
    MOCK_IBKR_TWS mock_ibkr_tws;
    ChatGPT_Analyzer chatgpt_analyzer;

    string url = "http://127.0.0.1:5000/news";
    string news_data = news_fetcher.fetch_news(url);
    cout << "News Data " << news_data << endl << endl;

    // Buy Scenario
    cout << "************ Buy Stock Scenarion **************" << endl << endl;
    string profile1 = "Tesla";
    string symbol1 = "TES";
    cout << "Profile " << profile1 << " Symbol " << symbol1 << endl << endl;

    json news_for_profile1 = news_fetcher.parse_news(news_data, profile1);
    cout << "News For Profile " << news_for_profile1 << endl << endl;

    string stock_signal1 = chatgpt_analyzer.check_stock_signal(news_for_profile1.dump(), profile1);
    cout << "Stock Signal " << stock_signal1 << endl << endl;

    int order_id1;
    if(stock_signal1.compare("Buy"))
    {
        cout << "Buying some stock...." << endl;
        order_id1 = mock_ibkr_tws.place_order(symbol1, 100);
        cout << "Order placed successfully " << order_id1 << endl << endl;

        cout << "Display order " << endl;
        cout << mock_ibkr_tws.view_orders(order_id1);
    }
    else if(stock_signal1.compare("Sell"))
    {
        cout << "Selling some stock...." << endl;
        cout << mock_ibkr_tws.update_order_quantity(order_id1, 50);
        cout << "Order placed successfully" << endl << endl;
    }


    // Sell Scenario
    cout << "************ Sell Stock Scenarion **************" << endl << endl;
    string profile2 = "Walmart";
    string symbol2 = "Wal";
    int order_id2 = mock_ibkr_tws.place_order(symbol2, 100);
    cout << "Profile " << profile2 << " Symbol " << symbol2 << endl << endl;

    json news_for_profile2 = news_fetcher.parse_news(news_data, profile2);
    cout << "News For Profile " << news_for_profile2 << endl << endl;

    string stock_signal2 = chatgpt_analyzer.check_stock_signal(news_for_profile2.dump(), profile2);
    cout << "Stock Signal " << stock_signal2 << endl << endl;

    if(stock_signal2.compare("BUY"))
    {
        cout << "Buying some stock...." << endl;
        order_id2 = mock_ibkr_tws.place_order(symbol2, 100);
        cout << "Order placed successfully " << order_id2 << endl << endl;

        cout << "Display order " << endl;
        cout << mock_ibkr_tws.view_orders(order_id2);
    }
    else if(stock_signal2.compare("SELL"))
    {
        cout << "Selling some stock...." << endl;
        cout << mock_ibkr_tws.update_order_quantity(order_id2, 50);
        cout << "Order placed successfully" << endl << endl;
    }
    
    cout << endl << endl;
    cout << mock_ibkr_tws.view_orders();

    return 0;

}