# This script calculates how many error reports are in each subdirectory
# and how many error reports are in total.
# Edit in_dir and out_file parameters as you need.

import os

in_dir = "D:/Projects/CrashRpt/valid_reports"
out_file = "stats.txt"


f = open(out_file, "w")

def get_txt_file_count(dirname):
   count = 0
   for root, dirs, files in os.walk(dirname, True):
     for file in files:
        if file[-4:] != ".txt":
            continue;
        count += 1
     break;
   return count

multimap = dict()
for root, dirs, files in os.walk(in_dir):
   for dir in dirs:
      dir_name = os.path.join(root, dir)
      report_count_in_dir = get_txt_file_count(dir_name)
      if report_count_in_dir in multimap.keys():
         multimap[report_count_in_dir].append(dir)
      else:
         multimap[report_count_in_dir] = [dir]

ordered_list = list(multimap.keys())
ordered_list.sort()
ordered_list.reverse()

total_count = 0
total_groups = 0
for count in ordered_list:
  total_groups += len(multimap[count]);
  total_count += count * len(multimap[count])

f.write("Total %d reports (100%%) in %d directories\n"%(total_count, total_groups))

n = 1
for key in ordered_list:
  for dir in multimap[key]:
   percent = key/total_count*100
   f.write("%d. %d reports (%0.1f%%) in '%s'\n"%(n, key, percent, dir))
   n = n+1

f.close()