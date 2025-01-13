'''
Moving Average Crossover:

Explanation: 
Uses two moving averages (e.g., 10-day and 50-day) to identify trends. 
A buy signal occurs when the short-term average crosses above the long-term average, 
and a sell signal occurs when it crosses below.

Example: 
If the 10-day moving average of stock XYZ is $50 and 
crosses above the 50-day moving average of $48, the algorithm buys XYZ.
'''


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import yfinance as yf

data = yf.download('AAPL', start = '2024-01-01', end = '2024-12-01')
data.columns = ['_'.join(col) for col in data.columns]
data = data.dropna()

# Calculate fast moving average (short-term) and slow moving average (long-term)
data['FM50'] = data['Close_AAPL'].rolling(window=50).mean()
data['SM200'] = data['Close_AAPL'].rolling(window=200).mean()

# Calculate Signal
data['Signal'] = 0
data.loc[data['FM50'] > data['SM200'], 'Signal'] = 1
data.loc[data['FM50'] < data['SM200'], 'Signal'] = -1

print(data)

plt.figure(figsize=(10,6))
plt.plot(data['Close_AAPL'], label='AAPL Price')
plt.plot(data['FM50'], label='50-Day Fast Moving Avg')
plt.plot(data['SM200'], label='200-Day Slow Moving Avg')
plt.scatter(data.index[data['Signal'] == 1], data['Close_AAPL'][data['Signal'] == 1], marker='^', color="g", label='Buy Signal')
plt.scatter(data.index[data['Signal'] == -1], data['Close_AAPL'][data['Signal'] == -1], marker='v', color="r", label='Sell Signal')
plt.legend()
plt.title('Moving Average Crossover')
plt.show()
