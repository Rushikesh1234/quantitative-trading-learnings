'''
Statistical Arbitrage:

Explanation: 
Uses statistical models to identify mispriced assets. 
Takes long positions in undervalued assets and short positions in overvalued ones.

Example: 
Stock pairs GHI and JKL are historically correlated. 
If GHI rises disproportionately, the algorithm shorts GHI and buys JKL.
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

# Calculate Spread between AAPL and MSFT
spread = data1['Close_AAPL'] - data2['Close_MSFT']

# Calculate Moving Average and Standard Deviation
spread_mean = spread.rolling(window=20).mean()
spread_std = spread.rolling(window=20).std()

z_score = (spread - spread_mean) / spread_std

print(data1)
print('\n')
print(data2)

plt.figure(figsize=(12, 6))
plt.subplot(2, 1, 1)
plt.plot(spread, label='Price Spread (AAPL - MSFT)')
plt.axhline(y=spread_mean.iloc[-1], color='r', linestyle='--', label='Mean Spread')
plt.title('Statistical Arbitrage - Spread of AAPL and MSFT')
plt.legend()

plt.subplot(2, 1, 2)
plt.plot(z_score, label='Z-Score of Spread', color='orange')
plt.axhline(y=1, color='g', linestyle='--', label='Upper Threshold (Z=1)')
plt.axhline(y=-1, color='b', linestyle='--', label='Lower Threshold (Z=-1)')
plt.title('Z-Score of the Spread')
plt.legend()

plt.tight_layout()
plt.show()

long_signal = z_score < -1
short_signal = z_score > 1

for date in long_signal[long_signal].index:
    print(f"Long Position Signal on {date}:")
    print(f" - Buy AAPL (undervalued)")
    print(f" - Sell MSFT (overvalued)")

for date in short_signal[short_signal].index:
    print(f"Short Position Signal on {date}:")
    print(f" - Sell AAPL (overvalued)")
    print(f" - Buy MSFT (undervalued)")