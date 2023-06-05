import pandas as pd
import matplotlib.pyplot as plt
from matplotlib_inline import backend_inline
import io

def use_svg_display():
  backend_inline.set_matplotlib_formats('svg')

def set_figsize(figsize=(8.5, 6.5)):
  use_svg_display()
  plt.rcParams['figure.figsize'] = figsize

def set_axes(axes, xlabel, ylabel, xlim, ylim, xscale, yscale, legend):
  axes.set_xlabel(xlabel)
  axes.set_ylabel(ylabel)
  axes.set_xscale(xscale)
  axes.set_yscale(yscale)
  axes.set_xlim(xlim)
  axes.set_ylim(ylim)
  if legend:
    axes.legend(legend)
  axes.grid()
  
def plot(X, Y=None, xlabel=None, ylabel=None, legend=None, xlim=None, 
         ylim=None, xscale='linear', yscale='linear',
         fmts=('-', 'm--', 'g-.', 'r:'), figsize=(8.5, 6.5), axes=None):
  if legend is None:
    legend = []

  set_figsize(figsize)
  axes = axes if axes else plt.gca()

  def has_one_axis(X):
    return (hasattr(X, "ndim") and X.ndim == 1 or isinstance(X, list)
    and not hasattr(X[0], "__len__"))

  if has_one_axis(X):
    X = [X]
  if Y is None:
    X, Y = [[]] * len(X), x
  elif has_one_axis(Y):
    Y = [Y]
  if len(X) != len(Y):
    X = X * len(Y)

  axes.cla()
  for x, y, fmt in zip(X, Y, fmts):
    if len(x):
      axes.plot(x, y, fmt)
    else:
      axes.plot(y, fmt)
  set_axes(axes, xlabel, ylabel, xlim, ylim, xscale, yscale, legend)
  

def plot_stock_data(filename, stock_symbol):
    # Read the data from the CSV file
    data = pd.read_csv(filename, names=["Date", "Price", "Short MA", "Long MA"], header=None)

    # Convert the "Date" column to datetime
    # data["Date"] = pd.to_datetime(data["Date"])
    data["Date"] = pd.to_datetime(data["Date"], format='%Y-%m-%dT%H:%M:%SZ')

    print(data.head(10))

    # Extract the necessary columns
    dates = data["Date"]
    prices = data["Price"]
    short_ma = data["Short MA"]
    long_ma = data["Long MA"]

    # Prepare your data to fit the plot function
    X = [dates, dates, dates]
    Y = [prices, short_ma, long_ma]

    # Create legend
    legend = ["Price", "Short MA", "Long MA"]

    # Create xlabel and ylabel
    xlabel = "Date"
    ylabel = "Value"

    # Plot the data
    plot(X, Y, xlabel=xlabel, ylabel=ylabel, legend=legend)

    # Save the plot as an image file
    plt.savefig(f"{stock_symbol}_moving_averages_plot.png")

    # Show the plot
    plt.show()

# plot_stock_data("AAPL.csv", "AAPL")
# plot_stock_data("MS.csv", "MS")
# plot_stock_data("MSFT.csv", "MSFT")
# plot_stock_data("NFLX.csv", "NFLX")
# plot_stock_data("TSLA.csv", "TSLA")
plot_stock_data("NVDA.csv", "NVDA")