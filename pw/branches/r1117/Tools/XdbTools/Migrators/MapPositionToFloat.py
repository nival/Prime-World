from os import path
import re
from math import sin, cos
from sys import argv


def node_pattern(name):
    pattern = re.compile(r'[\n\t]*<' + name + '>(.*?)</' + name + '>', re.DOTALL | re.MULTILINE)
    pattern = re.compile(r'[\r\n\t]*<' + name + '>(.*?)</' + name + '>', re.DOTALL | re.MULTILINE)
    return pattern

def node_content_pattern(name):
    pattern = re.compile(r'(?<=<' + name + '>)(.*?)(?=</' + name + '>)', re.DOTALL | re.MULTILINE)
    return pattern


class Replacer(object):

    def __init__(self):
        self.count = 0
        
    def __call__(self, match_obj):
        pass


class DataReplacer(Replacer):
    
    def __call__(self, match_obj):
        self.data = match_obj.group(1)

        
class PositionReplacer(Replacer):
    
    def __call__(self, match_obj):
        text = match_obj.group(1)        
        
        pattern = node_pattern('x')
        rr = DataReplacer()
        text = re.sub(pattern, rr, text)
        self.x = rr.data
        
        pattern = node_pattern('y')
        rr = DataReplacer()
        text = re.sub(pattern, rr, text)
        self.y = rr.data


class CoordReplacer(Replacer):
    
    def __init__(self, c):
        self.c = c
    
    def __call__(self, match_obj):
        c = float(match_obj.group(1))
        return str(c + self.c * 2.5)

    
class LocationReplacer(Replacer):
    
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
    def __call__(self, match_obj):
        text = match_obj.group(0)
        
        pattern = node_content_pattern('x')
        rr = CoordReplacer(self.x)
        text = re.sub(pattern, rr, text)
        
        pattern = node_content_pattern('y')
        rr = CoordReplacer(self.y)
        text = re.sub(pattern, rr, text)
        return text


##class RotationCoordReplacer(Replacer):
    
##    def __init__(self, c):
##        self.c = c
    
##    def __call__(self, match_obj):
##        return str(c + self.c * 2.5)

class Quaternion:
    
    def __init__(self, *coords):
        self.x = coords[0]
        self.y = coords[1]
        self.z = coords[2]
        self.w = coords[3]
        
class RotationReplacer(Replacer):
    
    def __init__(self, angle):
        self.q = Quaternion(0, 0, sin(angle / 2), cos(angle / 2))
    
    def __call__(self, match_obj):
        text = match_obj.group(0)
        
        c_n = ('x' , 'y', 'z', 'w')
        r = Quaternion(*[self.get_coord(text, c) for c in c_n])

        pattern = node_content_pattern('x')
        text = re.sub(pattern, str(self.q.w*r.x + r.w*self.q.x + (self.q.y*r.z - self.q.z*r.y)), text)

        pattern = node_content_pattern('y')
        text = re.sub(pattern, str(self.q.w*r.y + r.w*self.q.y + (self.q.z*r.x - self.q.x*r.z)), text)

        pattern = node_content_pattern('z')
        text = re.sub(pattern, str(self.q.w*r.z + r.w*self.q.z + (self.q.x*r.y - self.q.y*r.x)), text)

        pattern = node_content_pattern('w')
        text = re.sub(pattern, str(self.q.w*r.w - (self.q.x*r.x + self.q.y*r.y + self.q.z*r.z)), text)
        
        return text
    
    def get_coord(self, text, c_n):
        pattern = node_content_pattern(c_n)
        mo = re.search(pattern, text)
        return float(mo.group(1))

    
class PlaceReplacer(Replacer):
    
    def __init__(self, x, y, angle):
        self.x = x
        self.y = y
        self.angle = angle
    
    def __call__(self, match_obj):
        text = match_obj.group(0)
        
        pattern = node_pattern('location')
        rr = LocationReplacer(self.x, self.y)
        text = re.sub(pattern, rr, text)

        pattern = node_pattern('rotation')
        rr = RotationReplacer(self.angle)
        text = re.sub(pattern, rr, text)
        
        return text
    
    
class ItemReplacer(Replacer):
    
    def __call__(self, match_obj):
        text = match_obj.group(0)
        
        pattern = node_pattern('position')
        rr = PositionReplacer()
        text = re.sub(pattern, rr, text)
        x, y = float(rr.x), float(rr.y)

        pattern = node_pattern('orientation')
        rr = DataReplacer()
        text = re.sub(pattern, rr, text)
        orients = {'South' : 0, 'East' : 1.5707963, 'North' : 3.14159265, 'West' : 4.71238898}
        orient = orients[rr.data]

        pattern = node_pattern('place')
        rr = PlaceReplacer(x, y, orient)
        text = re.sub(pattern, rr, text)

        return text

            
class RecursiveReplacer(Replacer):

    def __call__(self, match_obj):
        text = match_obj.group(0)
        pattern = node_pattern('Item')
        rr = ItemReplacer()
        text = re.sub(pattern, rr, text)
        if rr.count != 0:
            self.count += 1
        return text

    
##file_name = "z:/pf\Data\Maps\Multiplayer\PF\PF.ADMP.xdb"            
file_name = argv[1]
fh = open(file_name)
text = fh.read()
fh.close()
text = re.sub(node_pattern('objects'), RecursiveReplacer(), text)
#print text
fh = open(file_name, 'w')
fh.write(text)
fh.close()