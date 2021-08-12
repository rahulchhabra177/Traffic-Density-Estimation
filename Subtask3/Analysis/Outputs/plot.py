import numpy
import csv
import PyGnuplot as gp
from numpy import genfromtxt
runtimes = [[0,0,0,0,0,0],[0,264,160,147,139,134],[0,274,238,241,244,243],[0,267,267,230,227,224],[0,181,175,178,173,176]]
for i in range(1,5):
	for j in range(6):
		file1 = "out"+str(i)+str(j)+".csv";
		output="Method"+str(i)+"-"+str(j)+".png"
		lt=i
		if i==3:
			lt=8
		if i==4:
			lt=9	

		if runtimes[i][j]!=0:
			gp.c('set datafile separator ","')
			gp.c('set grid')
			gp.c('set terminal png size 1920,1080')
			gp.c('set output "'+output+'"')
			gp.c('set title "Traffic Density Evaluation"')
			gp.c('set xlabel"Frame Number"')
			gp.c('set ylabel "Density"')
			gp.c('plot \''+file1+'\' using 1:2 title "Queue Density" with lines linetype '+str(lt))	
			