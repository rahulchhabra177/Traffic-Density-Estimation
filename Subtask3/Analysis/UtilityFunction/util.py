import numpy
import csv
from numpy import genfromtxt
runtimes = [[0,0,0,0,0,0],[0,264,160,147,139,134],[0,274,238,241,244,243],[0,267,267,230,227,224],[0,181,175,178,173,176]]
for i in range(1,5):
	with open("utility"+str(i)+".csv", 'w', newline='') as file:

		for j in range(6):
			file1 = "out"+str(i)+str(j)+".csv"
			if runtimes[i][j]!=0:
				data = genfromtxt(file1,dtype=float,delimiter=',',skip_footer=1)
				origData = genfromtxt("out.csv",dtype=float,delimiter=',',skip_footer=1)

				def utility(data):
					qError= 0.0
					n=data.shape[0]
					for i in range(0,n):
						qError += abs(data[i][1]-origData[i][1])
					if qError==0:
					    return -1
					else:
						return n/qError

				util=utility(data)

				writer = csv.writer(file)
				writer.writerow([runtimes[i][j],util])