# param 1: file name 
# param 2-N: different block sizes

import matplotlib
matplotlib.use('Agg')
import sys
import subprocess
import numpy as np
import string
import pylab


file_name = (sys.argv[1]);
blocks = (sys.argv[2:]);
i=0;
naive = []
size =[]

print("This script executes matrix multiplication for the matrixes in file",
        "'" + file_name + "'", "using the naive strategy and the blocked",
        "strategy for block sizes:", ", ".join(sys.argv[2:]))
        

num_lines = sum(1 for line in open(file_name))
num_blocks = sum(1 for i in (blocks))

with open(file_name, 'r') as f:
	lines = f.read().splitlines()

def get_info(lines, line_num):
	line = lines[line_num]
	return line.split( )

for j in blocks:
	blocked=[]
	for i in range(0,num_lines,+1):
		Size, MatriceA, MatriceB = get_info(lines,i)
		blocked.append(subprocess.check_output(["./matrix_multiplication","blocked",Size,MatriceA, MatriceB, j]))
		blockedFloat = [float(i) for i in blocked]
	pylab.plot(blockedFloat ,label=j)
	
for i in range(0,num_lines,+1):
		Size, MatriceA, MatriceB = get_info(lines,i)
		naive.append(subprocess.check_output(["./matrix_multiplication","Naive",Size,MatriceA, MatriceB]))
		size.append(Size)
		naiveFloat = [float(i) for i in naive]

pylab.xlabel('Matrix size')
pylab.ylabel('Time to compute matrix multiplication (seconds)')
pylab.title('Naive vs. Blockled time for matrix multiplication')
pylab.plot(size,naiveFloat,label='naive')
pylab.legend()
pylab.savefig('graph.png')	
pylab.show()
