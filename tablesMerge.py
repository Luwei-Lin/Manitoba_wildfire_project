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

def averageMeteorologicalDataByDate(dataFrame):
    '''
    Input: dataFrame(dictionary)
    Function: Analyse and calculate data by mean() or sum() in the same date.
    Output: (dataFrame dict.) summary
    '''
    d = dataFrame[["DATE", "TEMP", "RH", "WS", "FFMC", "DMC", "DC", "ISI", "BUI", "FWI", "DSR", "RAIN"]]
    summary = d.groupby(by = "DATE")[:-1].mean()
    summary_sum = d.gouupby(by = "DATE")[-1].sum()
    summary.merge(summary_sum)
    return summary

def main():
    df = load("raw_data_sets/2021")
    summary = averageMeteorologicalDataByDate(df)
    summary.to_csv(path_or_buf = "data_sets/weather/summary_2021.csv")
main()
