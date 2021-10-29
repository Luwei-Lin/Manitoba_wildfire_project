import os
import sys
import requests
import pandas as pd
from bs4 import BeautifulSoup

def convertVersion2(URL, year, date):
    """
    Input: url(String), year(int), date(String)
    Function: Since the year before 2019 of the Manitoba web site is a little different from 2020. It is CSS. So we modify the scraper.
    OutPut: n/a
    """
    try:
        r = requests.get(URL)
    except Exception as urlError:
        pass
    data = []
    list_header = []
    header = []
    
    soup = BeautifulSoup(r.content, "html.parser")
    header = soup.find_all('b')[0:13]

    if len(header) == 0:
        return 

    for items in header:
        try:
            list_header.append(items.get_text())
        except Exception:
            print("parse title error")

    HTML_data = soup.find_all("table")[1].find_all("tr")[1:]

    for element in HTML_data:
        sub_data = []
        for sub_element in element:
            try:
                validString = sub_element.get_text()
                if validString != '\n':
                    sub_data.append(sub_element.get_text())
            except:
                continue
        data.append(sub_data)
    
    dataFrame = pd.DataFrame(data = data, columns = list_header)
    
    csvName = date + '.csv'
    filePath = "raw_data_sets/" + str(year) + '/' + csvName

    dataFrame.to_csv(path_or_buf=filePath)


def convert(URL, year, date):
    """
    Input: url(String), year(int), date(String)
    Function: convert HTML table to .csv recursively 
    Ouput: n/a
    """
    try:
        r = requests.get(URL)
    except Exception as urlError:
        pass
    data = []
    list_header = []
    header = []
    
    soup = BeautifulSoup(r.content, "html.parser")
    header = soup.find_all("table")[0].find_all("th")
    
    if len(header) == 0:
        return 

    for items in header:
        try:
            list_header.append(items.get_text())
        except Exception:
            print("parse title error")

    HTML_data = soup.find_all("table")[0].find_all("tr")[1:]

    for element in HTML_data:
        sub_data = []
        for sub_element in element:
            try:
                validString = sub_element.get_text()
                if validString != '\n':
                    sub_data.append(sub_element.get_text())
            except:
                continue
        data.append(sub_data)
    
    dataFrame = pd.DataFrame(data = data, columns = list_header)
    
    csvName = date + '.csv'
    filePath = "raw_data_sets/" + str(year) + '/' + csvName

    dataFrame.to_csv(path_or_buf=filePath)

def stringDate(year, month, day):
    """
    Input: int year, int month, int day
    Function: String(year), String(month), String(day). Concatenation
    Output: Stirng "yyyymmdd"
    """
    dd = str(day).rjust(2, '0')
    mm = str(month).rjust(2, '0')
    yyyy = str(year)
    yyyymmdd = yyyy + mm + dd
    return yyyymmdd

def listDate(year)->list:
    """
    Input: year(int)
    Function: Store all dates of this year as String format in the list
    Output: list(all dates) like ["20210101", "20210102"...]
    """
    dateList = []
    months = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
    if year == 2019:
        months = months[3:]
    elif year == 2021:
        months = months[:11]

    for month in months:
        if month in [1, 3, 5, 7, 8, 10, 12]:#31 days
            if year != 2021:
                for day in range(1, 32):
                    yyyymmdd = stringDate(year, month, day)
                    dateList.append(yyyymmdd)
            else:
                for day in range(1, 26):
                    yyyymmdd = stringDate(year, month, day)
                    dateList.append(yyyymmdd)
        elif month in [4, 6, 9, 11]:
            for day in range(1, 31):
                yyyymmdd = stringDate(year, month, day)
                dateList.append(yyyymmdd)
            for day in range(22, 31):
                yyyymmdd = stringDate(year, month, day)
                dateList.append(yyyymmdd)
        elif (year & 10 == 0 and year % 4 == 0) or (year % 100 == 0 and year % 400 == 0):#29 days in Feb
            for day in range(1, 30):
                yyyymmdd = stringDate(year, month, day)
                dateList.append(yyyymmdd)
        else:
            for day in range(1, 29):# 28 days in Feb
                yyyymmdd = stringDate(year, month, day)
                dateList.append(yyyymmdd)

    return dateList


def main():
    years = [2017, 2018, 2019, 2020, 2021]
    for year in years:
        yyyy = str(year)
        dates = listDate(year)
        if year == 2020 or year == 2021:
            for date in dates:
                URL = "https://www.gov.mb.ca/conservation_fire/Wx-Report/" + yyyy + '/' + date + "-obs-wxrep.html"
                try:
                    convert(URL, year, date)
                except:
                    continue
        else: # 2019 before different html format
            for date in dates:
                URL = "https://www.gov.mb.ca/conservation_fire/Wx-Report/" + yyyy + '/' + date + "-obs-wxrep.html"
                try:
                    convertVersion2(URL, year, date)
                except:
                    continue
        

def test():
    URL = "https://www.gov.mb.ca/conservation_fire/Wx-Report/2018/20180501-obs-wxrep.html"
    convertVersion2(URL, 2018, "20180501")

main()
#test()
