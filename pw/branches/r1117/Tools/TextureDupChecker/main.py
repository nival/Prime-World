import sys
import os
import fnmatch
import math
import Image
import operator
import ImageStat

def collectFiles(folder, pattern):
    for root, dirs, files in os.walk(folder):
        for name in files:
            if fnmatch.fnmatch(name, pattern):
                yield os.path.join(root, name)
                
def getRMS(h1, h2):
    return math.sqrt(reduce(operator.add, map(lambda a,b: (a-b)**2, h1, h2))/len(h1))
    
def isSimilar(h1, h2):    
    s0 = ImageStat.Stat(h1)
    s1 = ImageStat.Stat(h2)
    names = [
        'rms',
        'var',
        'stddev'
    ]
    
    diff_count = 0
    for name in names:
        a0 = getattr(s0, name)
        a1 = getattr(s1, name)
        if a0 != a1:
            value = getRMS(a0, a1)
            print name, value
            if name == 'stddev' and  value > 5:
                diff_count += 1
                break
                
    return (diff_count == 0)                
        
if __name__ == '__main__':            
    files = list(collectFiles(sys.argv[1], '*.tga'))
    for i in range(len(files)):
        for j in range(i+1, len(files)):
            h1 = Image.open(files[i])
            h2 = Image.open(files[j])
            if h1.size == h2.size and h1.mode == h2.mode:
                diff = Image.difference(h1, h2)
                diff.save(os.path.splitext(files[i])[0]+os.path.splitext(files[j])[0]+'.png')
#                print files[i], h1.mode, files[j], h2.mode
                #rms = getRMS(h1.histogram(), h2.histogram())
                if isSimilar(h1, h2):
                    print 'check', files[i], files[j]
