import pandas as pd
import matplotlib.pyplot as plt
import torch
import torch.optim as optim

df = pd.read_csv("summary_weather_and_burned_area.csv") #dataframe
#'Rain_y' is same as 'Rain_x' (average vs. sum)

df_x = df[['TEMP', 'RH', 'WS', 'FFMC', 'DMC', 'DC', 'ISI', 'BUI', 'FWI', 'DSR', 'RAIN_x', 'HECTARES(yesterday)']]
#df_x = df[['FWI']]
df_y = df[['HECTARES']]

#divide dataframe
x_train = df_x.loc[0:1000]
y_train = df_y.loc[0:1000]

x_test = df_x.loc[1001:]
y_test = df_y.loc[1001:]

#tranfer the dataframe to class tensor
#a1*x1+a2*x2+a3*x3...= y1
#a1*x1
#[a1, a2, a3]*[x11, x12, x13] = [y1, y2, y3]
#             [x21, x22, x23]
#             [x31, x32, x33]
#             
x_train = torch.tensor(x_train.values, dtype=torch.float).t()
y_train = torch.tensor(y_train.values, dtype=torch.float).t()

x_test = torch.tensor(x_test.values, dtype=torch.float).t()
y_test = torch.tensor(y_test.values, dtype=torch.float).t()
#dimension of Xs through features
input_dim = 12

#We define the trainable parameters A and b
#Use torch.randn() to generate the random 
A = torch.randn((1, input_dim), requires_grad=True) #[a1, a2, a3...an]
b = torch.randn(1, requires_grad=True) #constant
#Matrix multiplication
def model(x_input):
    return A.mm(x_input) + b
#square deviation
def loss(y_predicted, y_target):
    return ((y_predicted - y_target)**2).sum()/(y_target.shape[1])

#Main optimization loop
#scenorio1
def trainModel(epochs, learningRate):
    optimizer = optim.Adam([A, b], lr=learningRate)
    for epoch in range(epochs):

        optimizer.zero_grad()

        y_predicted = model(x_train)
        current_loss = loss(y_predicted, y_train)

        current_loss.backward()
        optimizer.step()
        #print(f"epoch = {epoch}, loss = {current_loss}, A = {A.detach().numpy()}, b = {b.item()}")

def main():
    #Training the model
    learningRate = 0.001
    #Implenment Adam algorithm
    for num in range(5000, 50001, 5000):
        epochs = num
        trainModel(epochs, learningRate)
        #calculate y_test_predicted 
        y_predicted = model(x_test)
        #calulate deviation and see the performance of the trained model
        test_loss = loss(y_predicted, y_test)
        print("The loss of the test set: {} of {} times training and the learning rate is {}".format(test_loss, epochs, learningRate))

main()
