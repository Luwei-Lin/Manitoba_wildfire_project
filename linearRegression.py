#Credits to @Asad Mahmood https://towardsdatascience.com/linear-regression-with-pytorch-eb6dedead817 
#import libraries
import numpy as np
import torch
from torch.autograd import Variable
import pandas as pd
import matplotlib.pyplot as plt

class linearRegression(torch.nn.Module):
    def __init__(self, inputSize, outputSize):
        super(linearRegression, self).__init__()
        self.linear = torch.nn.Linear(inputSize, outputSize)

    def forward(self, x):
        out = self.linear(x)
        return out

#creating the training dat
dataSet = pd.read_csv('summary_weather_and_burned_area.csv')
featuresList = ['TEMP', 'RH', 'WS', 'FFMC', 'DMC', 'DC', 'ISI', 'BUI', 'FWI', 'DSR', 'RAIN_x', 'HECTARES(yesterday)']
#df_x = dataSet[['TEMP', 'RH', 'WS', 'FFMC', 'DMC', 'DC', 'ISI', 'BUI', 'FWI', 'DSR', 'RAIN_x', 'HECTARES(yesterday)']]
for feature in featuresList:
#df_x = dataSet[['DSR', 'ISI', 'RAIN_x']]
    df_y = dataSet[['HECTARES']]
    df_x = dataSet[[feature]]
    #2017-2020 train
        #x_train
    x_train = df_x.loc[0:1000]
        #y_train
    y_train = df_y.loc[0:1000]

    #2021 test
        #x_test
    x_test = df_x.loc[1001:]
        #y_test
    y_test = df_y.loc[1001:]
    # Last Step. x_test put in the "model" and compare with y_test

    inputDim = 1        # takes variable 'x' 
    outputDim = 1    # takes variable 'y'
    learningRate = 0.01
    epochs = 100

    x_train = np.array(x_train, dtype=np.float32)#.reshape(-1, inputDim)
    y_train = np.array(y_train, dtype=np.float32)#.reshape(-1, outputDim)
    #x_train = np.transpose(x_train)
    #y_train = np.transpose(y_train)

    x_test = np.array(x_test, dtype=np.float32).reshape(-1, inputDim)
    y_test = np.array(y_test, dtype=np.float32).reshape(-1, outputDim)

    model = linearRegression(inputDim, outputDim)

    criterion = torch.nn.MSELoss() 
    optimizer = torch.optim.SGD(model.parameters(), lr=learningRate)

    for epoch in range(epochs):
        # Converting inputs and labels to Variable
        if torch.cuda.is_available():
            inputs = Variable(torch.from_numpy(x_train).cuda())
            labels = Variable(torch.from_numpy(y_train).cuda())
        else:
            inputs = Variable(torch.from_numpy(x_train))
            labels = Variable(torch.from_numpy(y_train))

        # Clear gradient buffers because we don't want any gradient from previous epoch to carry forward, dont want to cummulate gradients
        optimizer.zero_grad()

        # get output from the model, given the inputs
        outputs = model(inputs)

        # get loss for the predicted output
        loss = criterion(outputs, labels)
        print(loss)
        # get gradients w.r.t to parameters
        loss.backward()

        # update parameters
        optimizer.step()

        print('epoch {}, loss {}'.format(epoch, loss.item()))

    with torch.no_grad(): # we don't need gradients in the testing phase
        if torch.cuda.is_available():
            predicted = model(Variable(torch.from_numpy(x_train).cuda())).cpu().data.numpy()
        else:
            predicted = model(Variable(torch.from_numpy(x_train))).data.numpy()
        print(predicted)
        plt.clf()
        plt.xlabel(feature)
        plt.ylabel('Burned Area')
        plt.plot(x_train, y_train, 'go', label='True data', alpha=0.5)
        plt.plot(x_train, predicted, '--', label='Predictions', alpha=0.5)
        plt.legend(loc='best')
        plt.show()








