import trading

prices = [100, 105, 110, 120, 125]
threshold = 0.05

print("\nexecute_trades")
trades = trading.execute_trades(prices, threshold)
for i, trade in enumerate(trades):
    print(f"Day {i + 1}: {trade}")

moving_avg = trading.compute_moving_average(prices, 3)
print("\ncompute_moving_average")
for i, avg in enumerate(moving_avg):
    print(f"Day {i + 1}: {avg}")