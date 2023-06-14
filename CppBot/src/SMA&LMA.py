import csv
import matplotlib.pyplot as plt

def plottingData(timeStamps, SMA, LMA, closedPrices):
    # Determine the shorter length of SMA and LMA arrays
    min_length = min(len(SMA), len(LMA))
    SMA = list(map(float, SMA))
    LMA = list(map(float, LMA))
    closedPrices = list(map(float, closedPrices))
    # Plotting the short-term moving average
    print(len(SMA))
    print(len(LMA))
    print(len(closedPrices))
    print(closedPrices[-min_length:])
    #selecting last (minlength) elements
    plt.plot(timeStamps[-min_length:], SMA[-min_length:], label="Short Term Moving Average")

    # Plotting the long-term moving average
    plt.plot(timeStamps[-min_length:], LMA[-min_length:], label="Long Term Moving Average")
    
    # Plotting the closed-prices 
    plt.plot(timeStamps[-min_length:], closedPrices[-min_length:], label="closedPrices")
    plt.xlim(timeStamps[-min_length], timeStamps[-1])
    # Adding labels and title
    plt.xlabel('Timestamp')
    plt.ylabel('Moving Average')
    plt.title('Short-term vs Long-term Moving Averages')
    plt.xticks(rotation='vertical')  # Rotate x-axis tick labels for better readability

    for x in timeStamps:
        plt.axvline(x=x, color='gray', linestyle='-', alpha=0.5)
    plt.xticks(rotation='vertical')  # Rotate x-axis tick labels for better readability
    # Adding a legend
    plt.legend()

    # Display the plot
    plt.show()

realTimeFileName = "/Users/shihyunnam/Desktop/OCaml-vs-Cpp-Algorithmic-Trading-Bot/CppBot/src/realtimeInfo.csv"
smaFilename = "/Users/shihyunnam/Desktop/OCaml-vs-Cpp-Algorithmic-Trading-Bot/CppBot/src/SMA.csv"
lmaFilename = "/Users/shihyunnam/Desktop/OCaml-vs-Cpp-Algorithmic-Trading-Bot/CppBot/src/LMA.csv"

timeStamps = []
closedPrices = []
SMA = []
LMA = []

with open(realTimeFileName, 'r') as csv_file:
    csv_reader = csv.reader(csv_file)
    next(csv_reader)  # Skipping the header row if it exists
    for row in csv_reader:
        time = row[0][6:10]
        timeStamps.append(time)
        closedPrices.append(row[4])


with open(smaFilename, 'r') as csv_file:
    csv_reader = csv.reader(csv_file)
    next(csv_reader)  # Skipping the header row if it exists
    for row in csv_reader:
        SMA.append(row[0])

with open(lmaFilename, 'r') as csv_file:
    csv_reader = csv.reader(csv_file)
    next(csv_reader)  # Skipping the header row if it exists
    for row in csv_reader:
        LMA.append(row[0])

plottingData(timeStamps, SMA, LMA, closedPrices)
