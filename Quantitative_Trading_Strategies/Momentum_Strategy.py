'''
Momentum Trading:

Explanation: 
Capitalizes on price trends. 
Buys assets with upward momentum and sells those with downward momentum.

Example: 
Stock DEF has risen 10% over the past week. 
The algorithm buys DEF, anticipating the trend will continue.

'''

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import yfinance as yf

data = yf.download('AAPL', start = '2024-01-01', end = '2024-12-01')
data.columns = ['_'.join(col) for col in data.columns]
data = data.dropna()

# Daily Price Change
data['Price_Change'] = data['Close_AAPL'].diff()

# Seperate Gain and Loss for all data
data['Gain'] = np.where(data['Price_Change'] > 0, data['Price_Change'], 0)
data['Loss'] = np.where(data['Price_Change'] < 0, -data['Price_Change'], 0)

# Calculate last 20 day average for Gain and Loss
data['Avg_Gain'] = data['Gain'].rolling(window=20).mean()
data['Avg_Loss'] = data['Loss'].rolling(window=20).mean()

# Calculate RSI and Buy when >70 and Sell when <30
data['RSI'] = 100 - (100 / (1 + (data['Avg_Gain'] / data['Avg_Loss'])))
data = data.dropna()

# Calculate Signal
data['RSI_Signal'] = 0
data.loc[data['RSI'] < 30, 'RSI_Signal'] = 1
data.loc[data['RSI'] > 70, 'RSI_Signal'] = -1

print(data)

plt.figure(figsize=(10,6))
plt.plot(data['Close_AAPL'], label='AAPL Price')
plt.title('Momentum Strategy with Buy and Sell Signals')
plt.legend()
plt.scatter(data.index[data['RSI_Signal'] == 1], data['Close_AAPL'][data['RSI_Signal'] == 1], marker='^', color='g', label = 'Buy Signal')
plt.scatter(data.index[data['RSI_Signal'] == -1], data['Close_AAPL'][data['RSI_Signal']== -1], marker='v', color='r', label='Sell Signal')
plt.legend()
plt.show()

plt.figure(figsize=(10, 6))
plt.plot(data['RSI'], label='RSI')
plt.axhline(70, color='r', linestyle='--', label='Overbought')
plt.axhline(30, color='g', linestyle='--', label='Oversold')
plt.title('Momentum Strategy with RSI moments')
plt.legend()
plt.show()
