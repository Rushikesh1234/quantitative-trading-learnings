'''
Mean Reversion:

Explanation: 
Assumes prices revert to their historical average. 
Buy when the price is below the average; sell when it's above.

Example: 
Stock ABC trades at $95, but its historical average is $100. 
The algorithm buys ABC, expecting it to rise.
'''

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import yfinance as yf

data = yf.download('AAPL', start = '2024-01-01', end = '2024-12-01')
data.columns = ['_'.join(col) for col in data.columns]
data = data.dropna()

# Calculate Moving Avg and Standard Deviation
data['Mean'] = data['Close_AAPL'].rolling(window=20).mean()
data['SD'] = data['Close_AAPL'].rolling(window=20).std()

# Calculate Upper and Lower Band so we can calculate with Closing price
data['Upper'] = data['Mean'] + 2 * data['SD']
data['Lower'] = data['Mean'] - 2 * data['SD']
data = data.dropna()

# Calculate Signal
data['Signal'] = 0
data.loc[data['Close_AAPL'] < data['Lower'], 'Signal'] = 1
data.loc[data['Close_AAPL'] > data['Upper'], 'Signal'] = -1

print(data)

plt.figure(figsize=(10,6))
plt.plot(data['Close_AAPL'], label='AAPL Price')
plt.plot(data['Mean'], label = 'Moving Average')
plt.plot(data['Upper'], label = 'Upper Band')
plt.plot(data['Lower'], label = 'Lower Band')

plt.scatter(data.index[data['Signal'] == 1], data['Close_AAPL'][data['Signal'] == 1], marker='^', color="g", label='Buy Signal')
plt.scatter(data.index[data['Signal'] == -1], data['Close_AAPL'][data['Signal'] == -1], marker='v', color="r", label='Sell Signal')

plt.legend()
plt.title('Mean Reversion')
plt.show()
