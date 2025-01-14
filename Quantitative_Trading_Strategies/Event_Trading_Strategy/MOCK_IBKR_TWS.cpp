// File is reponsible to mimic or interpret IBKR TWS API for placing an order or retrieving trade information

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;

struct Order
{
    public:
        string symbol;
        int quantity;

        Order() : 
            symbol(""), quantity(0) {}
    
        Order(string symbol, int quantity) : 
            symbol(symbol), quantity(quantity){}
};

class MOCK_IBKR_TWS
{
    unordered_map<int, Order> orders;
    int next_order_id;

    public:
        MOCK_IBKR_TWS() : next_order_id(1) {};
        
        int place_order(string &symbol, int quantity)
        {
            int order_id = next_order_id++;
            Order order = Order(symbol, quantity);
            orders[order_id] = order;
            return order_id;
        }

        string view_orders(int order_id)
        {
            stringstream vieworder;
            vieworder  << "Order ID: " << order_id << ", Symbol: " << orders[order_id].symbol 
                     << ", Quantity: " << orders[order_id].quantity << endl;
            return vieworder.str();
        }

        string view_orders()
        {
            stringstream vieworder;
            vieworder << "All Placed orders: \n";
            for (const auto& [id, order] : orders) {
                vieworder << "Order ID: " << id << ", Symbol: " << order.symbol 
                     << ", Quantity: " << order.quantity << endl;
            }
            return vieworder.str();
        }

        string update_order_quantity(int order_id, int val)
        {
            stringstream vieworder;
            orders[order_id].quantity -= val;
            vieworder << "Update Quantity for Order ID: " << order_id << ", Symbol: " << orders[order_id].symbol 
                     << ", Quantity: " << orders[order_id].quantity << endl;
            return vieworder.str();
        }

        string delete_order(int order_id)
        {
            stringstream vieworder;
            auto it = orders.find(order_id);

            if (it != orders.end()) {
                const Order& order = it->second;
                vieworder << "Order ID: " << it->first
                    << ", Symbol: " << order.symbol
                    << ", Quantity: " << order.quantity << endl;
                orders.erase(it);
                vieworder << "Order ID " << order_id << " deleted successfully." << endl;
            } else {
                vieworder << "Order ID " << order_id << " not found, cannot delete." << endl;
            }
            
            return vieworder.str();
        }
};