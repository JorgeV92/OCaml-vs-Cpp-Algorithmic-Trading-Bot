import csv
import matplotlib.pyplot as plt

def plottingData(timeStamps, SMA, LMA):
    # Determine the shorter length of SMA and LMA arrays
    min_length = min(len(SMA), len(LMA))
    SMA = list(map(float, SMA))
    LMA = list(map(float, LMA))
    # Plotting the short-term moving average
    plt.plot(timeStamps[:min_length], SMA[:min_length], label="Short Term Moving Average")

    # Plotting the long-term moving average
    plt.plot(timeStamps[:min_length], LMA[:min_length], label="Long Term Moving Average")

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
SMA = []
LMA = []

with open(realTimeFileName, 'r') as csv_file:
    csv_reader = csv.reader(csv_file)
    next(csv_reader)  # Skipping the header row if it exists
    for row in csv_reader:
        time = row[0][6:10]
        timeStamps.append(time)

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

plottingData(timeStamps, SMA, LMA)