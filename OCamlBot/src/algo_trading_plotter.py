import pandas as pd
import matplotlib.pyplot as plt
from matplotlib_inline import backend_inline
import io
import numpy as np

def plot_stock_data(filename, title):
    # Read the data from the CSV file
    data = pd.read_csv(filename, names=['date', 'price', 'short_ma', 'long_ma'])

    # Convert the 'date' column to datetime
    data['date'] = pd.to_datetime(data['date'])

    # Set the date as the index of the dataframe
    data.set_index('date', inplace=True)

    # Add a 'signal' column to the DataFrame
    # Buy signal is when short-term MA crosses above long-term MA
    data['buy_signal'] = np.where(data['short_ma'] > data['long_ma'], data['price'], np.nan)
    # Sell signal is when short-term MA crosses below long-term MA
    data['sell_signal'] = np.where(data['short_ma'] < data['long_ma'], data['price'], np.nan)

    # Plot the price, short moving average, and long moving average
    plt.figure(figsize=(14,7))
    plt.plot(data['price'], label='Price', color='blue')
    plt.plot(data['short_ma'], label='Short-term MA', color='red')
    plt.plot(data['long_ma'], label='Long-term MA', color='green')

    # Add markers for the buy and sell signals
    # plt.plot(data['buy_signal'], marker='o', markersize=3, label='Buy Signal', color='black', linestyle='None')
    # plt.plot(data['sell_signal'], marker='o', markersize=3, label='Sell Signal', color='pink', linestyle='None')

    plt.title(title)
    plt.xlabel('Date')
    plt.ylabel('Price')
    plt.legend()
    plt.grid(True)
    plt.show()

plot_stock_data('AAPL.csv', 'Apple Price and Moving Averages')

