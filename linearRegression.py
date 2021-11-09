#Credits to @Asad Mahmood https://towardsdatascience.com/linear-regression-with-pytorch-eb6dedead817 


#import libraries
import numpy as np
import torch
from torch.autograd import Variable
import pandas as pd


#creating the training data
dataSet = pd.read_csv('summary_weather_and_burned_area.csv')

dataList = [];

date = dataSet['DATE'].tolist()
temp = dataSet['TEMP'].tolist()
rh = dataSet['RH'].tolist()
windSpeed = dataSet['WS'].tolist()
ffmc = dataSet['FFMC'].tolist()
dmc = dataSet['DMC'].tolist()
dc = dataSet['DC'].tolist()
isi = dataSet['ISI'].tolist()
bui = dataSet['BUI'].tolist()
fwi = dataSet['FWI'].tolist()
dsr = dataSet['DSR'].tolist()
rainX = dataSet['RAIN_x'].tolist()
rainY = dataSet['RAIN_y'].tolist()
burnedToday = dataSet['HECTARES'].tolist()
burnedYesterday = dataSet['HECTARES(yesterday)'].tolist()


dataList.append(date)
dataList.append(temp)
dataList.append(rh)
dataList.append(windSpeed)
dataList.append(ffmc)
dataList.append(dmc)
dataList.append(dc)
dataList.append(isi)
dataList.append(bui)
dataList.append(fwi)
dataList.append(dsr)
dataList.append(rainX)
dataList.append(rainY)
dataList.append(burnedToday)


#create training data
x_values = []
y_values = []
i = 0


#load the data into the matrix
while i < len(date):
	dataOfADay = [];
	for n in range(14): #we have 14 types of data
		#data of every day is collected into one list
		dataOfADay.append(dataList[n])

	x_values.append(dataOfADay)
	y_values.append(burnedYesterday[i])
	i = i + 1

x_train = np.array(x_values, dtype=np.float32)
x_train = x_train.reshape(-1, 1)

y_train = np.array(y_values, dtype=np.float32)
y_train = y_train.reshape(-1, 1)



class linearRegression(torch.nn.Module):
    def __init__(self, inputSize, outputSize):
        super(linearRegression, self).__init__()
        self.linear = torch.nn.Linear(inputSize, outputSize)

    def forward(self, x):
        out = self.linear(x)
        return out



inputDim = 14        # takes variable 'x' 
outputDim = 1       # takes variable 'y'
learningRate = 0.01 
epochs = 100

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
plt.plot(x_train, y_train, 'go', label='True data', alpha=0.5)
plt.plot(x_train, predicted, '--', label='Predictions', alpha=0.5)
plt.legend(loc='best')
plt.show()








