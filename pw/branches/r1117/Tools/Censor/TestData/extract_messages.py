
import sys

lines = []
lines_filtered = []

with open( sys.argv[1] ) as f:
  for line in f:
    if line.find("<") < 0:
      continue;
    if line.find(">") < 0:
      continue;
    if line.find("\t") < 0:
      continue;
    
    line = line[line.find('>')+1:]
    res = line.split("\t")
    lines_filtered.append(res[0])
    lines.append(res[1])
  f.close()

with open( sys.argv[1] + ".org.txt", "w") as f:
  for line in lines:
    f.write(line)
  f.close()
  
with open( sys.argv[1] + ".filter.txt", "w") as f:
  for line in lines_filtered:
    line = line + '\n'
    f.write(line)
  f.close()