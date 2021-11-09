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

x_values = []
i = 0

while i < len(date):
	dataOfADay = [];
	for n in range(14):
		dataOfADay.append(dataList[n])

	x_values.append(dataOfADay)
	i = i + 1





