// File is reponsible to mimic or interpret IBKR TWS API for placing an order or retrieving trade information

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Order
{
    public:
        string symbol;
        int quantity;
        string action;
    
        Order(string symbol, int quantity, string action) : symbol(symbol), quantity(quantity), action(action){}
};

class IBKRStub
{
    unordered_map<int, Order> orders;
    int next_order_id;

    public:
        IBKRStub() : next_order_id(1) {};
        
        int place_order(string &symbol, int quantity, const string& action)
        {
            int order_id = next_order_id++;
            Order order = Order(symbol, quantity, action);
            orders[order_id] = order;
            std::cout << "Order placed - ID: " << order_id
                  << ", Symbol: " << symbol
                  << ", Quantity: " << quantity
                  << ", Action: " << action << std::endl;
            return order_id;
        }

        void view_orders(int order_id)
        {
            cout << "Order ID: " << order_id << ", Symbol: " << orders[order_id].symbol 
                     << ", Quantity: " << orders[order_id].quantity << ", Action: " << orders[order_id].action << endl;
        }

        void view_orders()
        {
            cout << "All Placed orders: \n";
            for (const auto& [id, order] : orders) {
                cout << "Order ID: " << id << ", Symbol: " << order.symbol 
                     << ", Quantity: " << order.quantity << ", Action: " << order.action << endl;
            }
        }

        void update_order_quantity(int order_id, int val)
        {
            orders[order_id].quantity -= val;
            cout << "Update Quantity for Order ID: " << order_id << ", Symbol: " << orders[order_id].symbol 
                     << ", Quantity: " << orders[order_id].quantity << endl;
        }

        void delete_order(int order_id)
        {
            auto it = orders.find(order_id);

            if (it != orders.end()) {
                const Order& order = it->second;
                cout << "Order ID: " << it->first
                    << ", Symbol: " << order.symbol
                    << ", Quantity: " << order.quantity
                    << ", Action: " << order.action << endl;
                orders.erase(it);
                cout << "Order ID " << order_id << " deleted successfully." << endl;
            } else {
                cout << "Order ID " << order_id << " not found, cannot delete." << endl;
            }
        }
};