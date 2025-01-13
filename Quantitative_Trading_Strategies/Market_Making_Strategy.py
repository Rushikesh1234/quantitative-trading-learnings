'''
Market Making:

Explanation: 
Provides liquidity by placing buy and sell orders simultaneously, profiting from the spread.

Example: 
For stock MNO, the algorithm quotes a bid price of $99.50 and an ask price of $100, 
earning $0.50 per share traded.
'''

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import yfinance as yf

data = yf.download('AAPL', start = '2024-01-01', end = '2024-12-01')
data.columns = ['_'.join(col) for col in data.columns]
data = data.dropna()

spread = 0.5

data['Bid'] = data['Close_AAPL'] - spread / 2
data['Ask'] = data['Close_AAPL'] + spread / 2

data = data.dropna()

print(data)

plt.figure(figsize=(10,6))
plt.plot(data['Close_AAPL'], label='AAPL Price')
plt.plot(data['Bid'], label='Bid Price')
plt.plot(data['Ask'], label='Ask Price')
plt.legend()
plt.title('Market Making')
plt.show()