import matplotlib.pyplot as plt
import pandas as pd

df=pd.read_csv('/home/hkmsdd_user/data.txt', header=None)
df.drop(df.columns[23:36], axis=1, inplace=True)
df.drop([1,12], axis=1, inplace=True)
df.columns=["Time", "A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9", "A10", "B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9", "B10"]
df=df.set_index(df.columns[0])

#print(df.to_string())
dfA=df.iloc[:, 0:10].copy()
dfB=df.iloc[:, 10:20].copy()

diffA=dfA.diff()
diffB=dfB.diff()
diffA.drop(df.index[0], inplace=True)
diffB.drop(df.index[0], inplace=True)


ax=diffA.plot(style='.-', figsize=(16,9))
diffB.plot(style='.--',ax=ax, figsize=(16,9))

plt.ylabel('Counts')
plt.xlabel('Time (JST)')
plt.xticks(rotation=-20)
#plt.yscale('log')
plt.tight_layout()
#plt.show()
plt.savefig('/home/hkmsdd_user/AquaMuonMonitor/SinglesRates.png')
