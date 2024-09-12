from os import path
import re
import sys

pattern = re.compile(r'<y>([0-9]+)</y>')

f = open(sys.argv[1], "rt")
f1 = open(sys.argv[2], "wt")

def replFunc(mo):
	print mo.group(1)
	x = float(mo.group(1)) / 320.0
	return '<y>'+str(x)+'</y>'
	

for l in f:
	res = pattern.sub(replFunc, l)
	f1.write(res)