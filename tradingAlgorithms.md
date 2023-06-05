Algorithmic trading strategies

1.Trend Following(Moving Average): This algorithm aims to identify and exploit trends in the market. 
It uses technical analysis indicators to determine the direction of the market trend and generates buy or sell 
signals accordingly. For example, it may buy when the price crosses above a moving average or sell when the 
price drops below a certain threshold.

For instance, a simple moving average (SMA) calculates the average of a selected range of prices, typically closing prices, by the number of periods in that range. 

Mathematically, if `P = (p1, p2, p3, ..., pn)` are the prices of the last `n` days, the simple moving average would be calculated as:

SMA = (p1 + p2 + p3 + ... + pn) / n


An algorithm could generate a buy signal when the price of the stock (P) crosses above its moving average line (SMA) indicating an upward trend, and a sell signal when it crosses below, suggesting a downward trend.
