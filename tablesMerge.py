#Merge valid data we need from raw_data_sets and raw_data_burned_area
#to one complete .csv file 
import os
import pandas as pd

def load(path):
    """
    Input: file path(String)
    Function: concatenation all files in this path to one dfs
    Output: DataFrame[{"20210101": []}]
    """
    dfs = []
    try:
        for file in os.listdir(path): #Open the file dir (files name list)
            data = pd.read_csv(os.path.join(path, file))#Open "path + filename" and save as dict 
            data["DATE"] = file.split('.')[0]# e.g. data["Date"] = "20210101" as new KV in dict.
            dfs.append(data) #main dataFrame list [{dictionary01 first.csv}, {dict02}...]
        df = pd.concat(dfs)
        return df
    except OSError as fileError:
        print("File path is invalid.")
def loadBurnedArea(path):
    '''
    function: concatenation all burned_area files in this directory to one df
    '''
    dfs = []
    try:
        for file in os.listdir(path):
            data = pd.read_csv(os.path.join(path, file))
            dfs.append(data)
        df = pd.concat(dfs)
        return df
    except Exception as fileError:
        print(fileError)

def averageMeteorologicalDataByDate(dataFrame):
    '''
    Input: dataFrame(dictionary)
    Function: Analyse and calculate data by mean() or sum() in the same date.
    Output: (dataFrame dict.) summary
    '''
    head_list = ["DATE", "TEMP", "RH", "WS", "FFMC", "DMC", "DC", "ISI", "BUI", "FWI", "DSR", "RAIN"]
    d = dataFrame[head_list]
    summary_mean = d.groupby(by = "DATE")[head_list[1:12]].mean()
    summary_sum = d.groupby(by = "DATE")[head_list[11]].sum()
    summary = summary_mean.merge(summary_sum, how = "left", on = "DATE")
    return summary

def summaryWeather(year):
    '''
    Input: year(int)
    Function: Integrate all raw_data_documents into yearly summary
    Output: n/a
    '''
    fileFolderPath = "raw_data_sets/" + str(year)
    dfMeteo = load(fileFolderPath)
    summary = averageMeteorologicalDataByDate(dfMeteo)
    outputFilePath = "data_sets/weather/summary_weather_" + str(year) + ".csv"
    summary.to_csv(path_or_buf = outputFilePath)

def stringfyDate(date):
    '''
    Input: date(string) like 2021-Mar-01
    Function: convert date format to numberic string
    Output: conveted DATE like "20210301"
    '''
    elements = date.split('-')
    assert(len(elements) >= 3), Exception()
        
    months = {"Jan":"01", "Feb":"02", "Mar":"03", "Apr":"04", "May":"05",\
        "Jun": "06", "Jul": "07", "Aug": "08", "Sep": "09", "Oct":"10", \
        "Nov": "11", "Dec": "12"}
    yyyy = elements[0]
    mm = months.get(elements[1])
    dd = elements[2].rjust(2,'0')
    newDate = yyyy + mm + dd
    return newDate

def burnedAreaTotalByDate2021(dataFrame):
    '''
    Function: strip and reshape 2021 raw_data_burned area into yearly summary(2 columns),
    Also, we change Reported format like from "2021-Mar-22" to "20210322"
    '''
    head_list = ["REPORTED", "HECTARES (estimated)"]
    df = dataFrame[head_list]
    df = df.rename(columns={"HECTARES (estimated)":"HECTARES"}, errors="raise")
    d = {"DATE":[]}
    for date in df["REPORTED"]:
        d.get("DATE").append(stringfyDate(date))
    #newDf = pd.DataFrame(data = d)
    
    df.insert(0, "DATE", d.get("DATE"), True) 
    #print(df)
    outputdf = df[["DATE", "HECTARES"]]

    summary = outputdf.groupby(by = "DATE").sum()
    return summary
def makeItFloat(data):
    '''
    input: data (float or string)
    function: check it is string or float
    output: float
    '''
    num = 0.0
    if isinstance(data, float):
        return data
    else:
        numList = data.split(",")
        numString = ''
        for n in numList:
            element = n.strip()
            numString += element
        if numString != '':
            num = float(numString)
    return num


def burnedAreaTotalByDateBefore2021(dataFrame, year):
    '''
    input: year (int), DataFrame
    Function: Strip years before 2021 and integrate into yearly summary (2 columns)
    '''
    head_list = []
    if year == 2020: #2020 is speacial
        head_list = ["REPORTED", "HECTARES (estimated)"]
    else:
        head_list = ["REPORTED", "HECTARES "]

    dataFrame = dataFrame.drop_duplicates()
    print(dataFrame)

    df1 = dataFrame[head_list]
    print(df1)
    #df1 = df1.rename(columns={"HECTARES ":"HECTARES"}, errors="raise")
    
    d = {"DATE":[]}
    d2= {"HECTARES":[]}
    for date in df1["REPORTED"]:
        d.get("DATE").append(stringfyDate(date))
    if year == 2020:
        for data in df1["HECTARES (estimated)"]:
            d2.get("HECTARES").append(makeItFloat(data))
    else:
        for data in df1["HECTARES "]:
            d2.get("HECTARES").append(makeItFloat(data))
    df1.insert(1, "HECTARES", d2.get("HECTARES"), True)
    df1.insert(0, "DATE", d.get("DATE"), True)
    
    df = df1[["DATE", "HECTARES"]].sort_values(by = "DATE")
    #since 2017 there are some "hectares like "3,198.7" cannot sum() directly
    summary = df.groupby(by="DATE").sum()
    return summary

def summaryBurnedArea(year):
    '''
    Function: script 
    '''
    if year == 2021:
        filePath = "raw_data_burned_area/2021/2021_burned_area.csv"
        df_raw = pd.read_csv(filePath)
        df = burnedAreaTotalByDate2021(df_raw)
        df.to_csv("data_sets/burned_area/summary_burned_area_2021.csv")
    else:
        fileFolderPath = "raw_data_burned_area/" + str(year)
        dfArea = loadBurnedArea(fileFolderPath) # recursicely load all files in that path
        summary = burnedAreaTotalByDateBefore2021(dfArea, year) # df after re-integration
        outputFilePath = "data_sets/burned_area/summary_burned_area_" + str(year) + ".csv"
        summary.to_csv(path_or_buf = outputFilePath)

def mergeWeatherBurnedArea():
    '''
    function: merge same year meteorogical data and burned area
    '''
    data1 = pd.read_csv("data_sets/burned_area/summary_burned_area_2021.csv")
    data2 = pd.read_csv("data_sets/weather/summary_weather_2021.csv")
    df = data1.merge(data2, how = 'left', on = 'DATE')
    df.to_csv("data_sets/sample_for_test/2021.csv")

def main():
    years = [2017, 2018, 2019, 2020, 2021]
    for year in years:
        #summaryWeather(year)
        summaryBurnedArea(year)
        #mergeWeather(year)
def test():
    summaryBurnedArea(2020)
    #mergeWeatherBurnedArea()
#test()

main()
