#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void write_to_text_file(vector<double>& data, string filepath)
{
    ofstream outfile(filepath);

    if(outfile.is_open())
    {
        int i=1;
        for(const auto& val : data)
        {
            outfile << "Day " << i << ": " << val << endl;
        }
        outfile.close();
        cout << "Text Data saved to file." << endl;
    }
    else
    {
        cerr << "Text File not found" << endl;
    }
}

void read_from_text_file(string filepath)
{
    ifstream infile(filepath);
    string line;

    if(infile.is_open())
    {
        cout << "Reading Text File:" << endl;
        while(getline(infile, line))
        {
            cout << line << endl;
        }
        infile.close();
    }
    else
    {
        cerr << "Text File not found" << endl;
    }
}

struct Trade
{
    string stock_name;
    int volume;
    double price;
};

void write_to_binary_file(Trade* trade, int n, string binary_file_path)
{
    ofstream outfile(binary_file_path, ios::binary);

    if(outfile.is_open())
    {
        for(int i=0; i<n; i++)
        {
            outfile.write(reinterpret_cast<char*>(&trade[i]), sizeof(trade[i])); 
        }
        outfile.close();
        cout << "Binary Data is saved successfully." << endl;
    }
    else
    {
        cerr << "Binary File not found" << endl;
    }
}

void read_from_binary_file(string binary_file_path)
{
    ifstream infile(binary_file_path, ios::binary);
    Trade readTrade;

    if(infile.is_open())
    {
        cout << "Reading Binary File:" << endl;
        while(infile.read(reinterpret_cast<char*>(&readTrade), sizeof(readTrade)))
        {
            cout << "Stock Name: " << readTrade.stock_name << " Stock Volum: " << readTrade.volume << " Stock Price: " << readTrade.price << endl;
        }
    }
    else
    {
        cerr << "Binary File not found" << endl;
    }
}


double convertToDouble(string& str, bool& success)
{
    try
    {
        success = true;
        return stod(str);
    }
    catch(const std::exception& e)
    {
        success = false;
        std::cerr << e.what() << '\n';
        return 0.0;
    }
    
}

void work_on_csv()
{
    cout << "Worknig on CSV File:" << endl;

    string input_csv_file = "test input_csv_file.csv";
    string processed_csv_file = "test processed_csv_file.csv";

    vector<vector<string>> input_data;

    // Read CSV file
    ifstream infile(input_csv_file);
    if(!infile.is_open())
    {
        cerr << "Input CSV file not found." << endl;
    }

    string line;
    bool isHeader = true;
    vector<string> headers;

    while(getline(infile, line))
    {
        vector<string> row;
        stringstream ss(line);
        string field;

        while(getline(ss, field, ','))
        {
            row.push_back(field);   
        }

        if(isHeader)
        {
            headers = row;
            headers.push_back("AveragePrice"); 
            isHeader = false;
        }
        else
        {
            input_data.push_back(row);
        }
    }

    infile.close();

    string headersName = headers[0] + " " + headers[1] + " " + headers[2] + " " + headers[3] + " " + headers[4] + " " + headers[5];
    cout << headersName << endl;

    // Modify Data
    // Column name - date	close	volume	open	high	low
    for(auto& row : input_data)
    {
        bool isCloseValid, isVolumeValid, isOpenValid, isHighValid, isLowValid;
        string date = row[0];
        double close = convertToDouble(row[1], isCloseValid);
        double volume = convertToDouble(row[2], isVolumeValid);
        double open = convertToDouble(row[3], isOpenValid);
        double high = convertToDouble(row[4], isHighValid);
        double low = convertToDouble(row[5], isLowValid);

        if(isCloseValid && isVolumeValid && isOpenValid && isHighValid && isLowValid)
        {
            double average = (open + close + high + low) / 4.0;
            row.push_back(to_string(average));
        }
        else
        {
            row.push_back("N/A");
        }
        string temp = date + " " + to_string(close) + " " + to_string(volume) + " " + to_string(open) + " " + to_string(high) + " " + to_string(low);
        cout << temp << endl;
    }

    ofstream outfile(processed_csv_file);

    if(!outfile.is_open())
    {
        cerr << "Output CSV file not found." << endl;
    }

    for(size_t i = 0; i<headers.size(); i++)
    {
        outfile << headers[i];
        if(i < headers.size() - 1) outfile << ",";
    }
    outfile << "\n";

    for(const auto& row :input_data)
    {
        for(size_t i = 0; i<row.size(); i++)
        {
            outfile << row[i];
            if(i < row.size() - 1) outfile << ",";
        }
        outfile << "\n";
    }

    outfile.close();

    cout << "Data has been processed successfully." << endl;
}

int main()
{
    // Text Files

    string text_file_path = "test txt stock file operations.txt";

    vector<double> data;
    data.push_back(100.0);
    data.push_back(102.0);
    data.push_back(101.0);
    data.push_back(104.0);
    data.push_back(107.0);
    data.push_back(110.0);

    write_to_text_file(data, text_file_path);

    read_from_text_file(text_file_path);


    // Binary Files - Very helpful, optimized and efficient way to store historical market data

    string binary_file_path = "test binart stock file operations.bin";
    
    Trade trade[5];

    trade[0].stock_name = "ggl"; trade[0].volume = 1000; trade[0].price = 180.00;
    trade[1].stock_name = "pep"; trade[1].volume = 900; trade[1].price = 80.00;
    trade[2].stock_name = "mic"; trade[2].volume = 1500; trade[2].price = 280.00;
    trade[3].stock_name = "sig"; trade[3].volume = 2000; trade[3].price = 100.00;
    trade[4].stock_name = "tes"; trade[4].volume = 100; trade[4].price = 580.00;

    write_to_binary_file(trade, 5, binary_file_path);

    read_from_binary_file(binary_file_path);


    // CSV Files 

    work_on_csv();

    return 0;
}