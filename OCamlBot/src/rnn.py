import torch
import torch.nn as nn
import pandas as pd
from sklearn.preprocessing import MinMaxScaler

filename = "NVDA.csv"

# Load data
data = pd.read_csv(filename, names=["Date", "Price", "Short MA", "Long MA"], header=None)

print(data.tail())

# Normalize data
scaler = MinMaxScaler(feature_range=(0, 1))
scaled_data = scaler.fit_transform(data[['Price', 'Short MA', 'Long MA']])

# Reshape data for RNN input
X = scaled_data[:-1, :]  # all but the last row
y = scaled_data[1:, 0]  # all but the first row of 'Price' column

# Convert to PyTorch tensors
X = torch.tensor(X, dtype=torch.float).unsqueeze(1)  # add an extra dimension for batch
y = torch.tensor(y, dtype=torch.float).unsqueeze(1)  # add an extra dimension to match model output


# Define RNN model
class RNN(nn.Module):
    def __init__(self, input_size, hidden_size, output_size):
        super(RNN, self).__init__()
        self.rnn = nn.RNN(input_size, hidden_size, batch_first=True)
        self.fc = nn.Linear(hidden_size, output_size)

    def forward(self, x):
        out, _ = self.rnn(x)
        out = self.fc(out[:, -1, :])
        return out
    
# Define LSTM model
class LSTM(nn.Module):
    def __init__(self, input_size, hidden_size, output_size):
        super(LSTM, self).__init__()
        self.lstm = nn.LSTM(input_size, hidden_size, batch_first=True)
        self.fc = nn.Linear(hidden_size, output_size)

    def forward(self, x):
        out, _ = self.lstm(x)
        out = self.fc(out[:, -1, :])
        return out

model = LSTM(input_size=X.shape[2], hidden_size=50, output_size=1)

# model = RNN(input_size=X.shape[2], hidden_size=50, output_size=1)

# Define loss function and optimizer
criterion = nn.MSELoss()
optimizer = torch.optim.Adam(model.parameters())

# Train the model
for epoch in range(50):
    model.zero_grad()
    output = model(X)
    loss = criterion(output, y)
    loss.backward()
    optimizer.step()

print("Now the model is trained and can be used for predictions")

# Let's assume you want to predict the next price given the last row in your data
last_row = scaled_data[-1, :]  # the last row in your data
last_row = torch.tensor(last_row, dtype=torch.float).unsqueeze(0).unsqueeze(0)  # reshape for RNN

# Make a prediction
with torch.no_grad():  # we don't need gradients for prediction
    prediction = model(last_row)

# The prediction is also scaled in the range (0, 1), so we need to reverse the scaling
predicted_price = scaler.inverse_transform([[prediction.item(), 0, 0]])[0, 0]

# print(f"The predicted next price using RNN is: {predicted_price}")

print(f"The predicted next price using LSTM is: {predicted_price}")

