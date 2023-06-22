import csv
import numpy as np
import math
import matplotlib.pyplot as plt

#plotting the data with specified requirements
def plottingData(timeStamps, openingPrices, highestPrices, lowestPrices, closedPrices):
    plt.plot(timeStamps, openingPrices, label="Opening Prices")
    plt.plot(timeStamps, highestPrices, label="highest Prices")
    plt.plot(timeStamps, lowestPrices, label="lowest Prices")
    plt.plot(timeStamps, closedPrices, label="closed Prices")
    plt.xlabel('timeStamps')
    plt.ylabel('PriceInformation')
    plt.title('Timestamps and Prices information')
    plt.xlim(timeStamps[0], timeStamps[-1])  # Set x-axis limits based on the data range
    # Adjust y-axis ticks
    plt.ylim(np.round(min(lowestPrices)), np.round(max(highestPrices)))
    # Draw auxiliary lines for specified x-axis values
    for x in timeStamps:
        plt.axvline(x=x, color='gray', linestyle='--', alpha=0.5)
    plt.xticks(rotation='vertical')  # Rotate x-axis tick labels for better readability
    min_lowest = min(lowestPrices)
    max_highest = max(highestPrices)
    y_ticks = np.arange(min_lowest, max_highest + 10, 10)
    plt.yticks(y_ticks)
    plt.legend()
    plt.tight_layout()  # Adjust layout to prevent label overlap
    plt.show()

fileName = "/Users/shihyunnam/Desktop/OCaml-vs-Cpp-Algorithmic-Trading-Bot/CppBot/src/stockInfo.csv"
timeStamps = []
openingPrices = []
highestPrices = []
lowestPrices = []
closedPrices = []

with open(fileName, 'r') as csv_file:
    csv_reader = csv.reader(csv_file)
    next(csv_reader)# Skipping the header row if it exists

    for row in csv_reader:
        time = row[0]#time parsing
        timeStamps.append(time)
        openingPrices.append(float(row[1]))
        highestPrices.append(float(row[2]))
        lowestPrices.append(float(row[3]))
        closedPrices.append(float(row[4]))

# Plot the data
plottingData(timeStamps, openingPrices,highestPrices, lowestPrices, closedPrices)

