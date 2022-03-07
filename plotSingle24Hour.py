#these first two lines are required for running through cron
import matplotlib as mpl
#mpl.use('Agg')
import matplotlib.pyplot as plt
import pandas as pd
import scipy.stats as sp
import numpy as np

df=pd.read_csv('/home/hkmsdd_user/data.txt', header=None)
df.drop(df.columns[23:36], axis=1, inplace=True)
df.drop([1,12], axis=1, inplace=True)
df.columns=["Time", "A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9", "A10", "B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9", "B10"]
df=df.set_index(df.columns[0])
#converts index to a datetime and then changes from JST to GMT/UTC
df.index=pd.to_datetime(df.index, yearfirst=True) - pd.Timedelta('09:00:00')

#print(df.to_string())
dfA=df.iloc[:, 0:10].copy()
dfB=df.iloc[:, 10:20].copy()

diffA=dfA.diff()
diffB=dfB.diff()
diffA.drop(df.index[0], inplace=True)
diffB.drop(df.index[0], inplace=True)

#print(diffB.groupby(diffB.index.hour).sem())


diffAMean=diffA.groupby(diffA.index.hour).mean()
diffAErr=diffA.groupby(diffA.index.hour).std()
diffBMean=diffB.groupby(diffB.index.hour).mean()
diffBErr=diffB.groupby(diffB.index.hour).std()



ax=diffAMean.plot(yerr=diffAErr, style='-', figsize=(8,6))
diffBMean.plot(yerr=diffBErr, ax=ax, fmt='--', figsize=(8,6))

plt.ylabel('Counts')
plt.xlabel('Hour of the day (GMT)')
plt.xticks(np.arange(0,24,2))
#plt.xticks(rotation=-20)
#plt.yscale('log')
plt.tight_layout()
#plt.show()
plt.savefig('/home/hkmsdd_user/AquaMuonMonitor/SinglesRates24HourAvg.png')
