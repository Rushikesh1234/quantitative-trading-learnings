'''
Pairs Trading:

Explanation: 
Trades two correlated assets. 
Buys the underperforming asset and sells the overperforming one.

Example: 
Gold and silver prices diverge. 
The algorithm buys silver and shorts gold, expecting prices to converge.
'''

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import yfinance as yf

data1 = yf.download('AAPL', start = '2024-01-01', end = '2024-12-01')
data2 = yf.download('MSFT', start = '2024-01-01', end = '2024-12-01')

data1.columns = ['_'.join(col) for col in data1.columns]
data2.columns = ['_'.join(col) for col in data2.columns]

data1 = data1.dropna()
data2 = data2.dropna()

# Calculate the spread
spread = data1['Close_AAPL'] - data2['Close_MSFT']

# Plot the spread
plt.figure(figsize=(10, 6))
plt.plot(spread, label='Spread (AAPL - MSFT)')
plt.axhline(y=spread.mean(), color='r', linestyle='--', label='Mean')
plt.legend()
plt.title('Pairs Trading Strategy - AAPL vs MSFT')
plt.show()