## Migration to new pin values

from os import path

def xdb_visit(visitor, dirname, names):
##    print dirname
    for n in names:
        if n.endswith('xdb'):
            visitor(path.join(dirname, n))

import re

class EnumReplacer(object):
    def __init__(self, name):
        self.name = name
    def __call__(self, matchobj):
        print matchobj.group(0)
        if matchobj.group(0) in enums[self.name]:
            return enums[self.name][matchobj.group(0)]
        else:
            return matchobj.group(0)
##        if matchobj.group(0) == enums[self.name][0]:
##            return 'None'
##        elif matchobj.group(0) == enums[self.name][1]:
##            return 'Present'
##        else:
##            print 'EEEEEEEEEEEEEEE'
    

class Visitor(object):
    def __init__(self):
        self.enum_replacers = {}
        for en in enums:
            self.enum_replacers[en] = re.compile(r'(?<=%s>)[a-zA-Z]*(?=<)' % (en + 'Value'))
    def __call__(self, file_name):
        print file_name
        fh = open(file_name)
        text = fh.read()
        fh.close()
##        for en, ev in enums.iteritems():
##    ##        ep = re.compile(r'(?<=%s>)[a-zA-Z]*<' % (en + 'value'))
##    
##            ep = re.compile(r'(?<=%s>)[a-zA-Z]*(?=<)' % (en + 'Value'))
    

    ##        ep = re.compile(r'(?<a)aa<')
        for en, ep in self.enum_replacers.iteritems():    
            text = re.sub(ep, EnumReplacer(en), text)
    ##        print text
        fh = open(file_name, 'w')
        fh.write(text)
        fh.close()
        
        

enums = {}
enums['NormalMapPin'] = {}
enums['NormalMapPin']['NoNormalMap'] = 'None'
enums['NormalMapPin']['TangentSpace'] = 'Present'

enums['DiffuseMapPin'] = {}
enums['DiffuseMapPin']['NoDiffuseMap'] = 'None'
enums['DiffuseMapPin']['DiffuseMapPresent'] = 'Present'

enums['DarkMapPin'] = {}
enums['DarkMapPin']['NoDarkMap'] = 'None'
enums['DarkMapPin']['DarkMapPresent'] = 'Present'
enums['SpecularMapPin'] = {}
enums['SpecularMapPin']['NoSpecularMap'] = 'None'
enums['SpecularMapPin']['SpecularMapPresent'] = 'Present'
enums['TemperaturePin'] = {}
enums['TemperaturePin']['NoTemperature'] = 'None'
enums['TemperaturePin']['TemperaturePresent'] = 'Present'
enums['EmissiveMultiplierPin'] = {}
enums['EmissiveMultiplierPin']['NoEmissiveMultiplier'] = 'None'
enums['EmissiveMultiplierPin']['EmissiveMultiplierPresent'] = 'Present'
enums['SkeletalMeshPin'] = {}
enums['SkeletalMeshPin']['NoTransform'] = 'None'
enums['SkeletalMeshPin']['TransformVertices'] = 'Present'
enums['EnvMapPin'] = {}
enums['EnvMapPin']['NonEnv'] = 'None'
enums['EnvMapPin']['EnvPresent'] = 'Present'
enums['ShadowCasterPin'] = {}
enums['ShadowCasterPin']['None'] = 'None'
enums['ShadowCasterPin']['ShadowCaster'] = 'Present'
enums['ShadowReciverPin'] = {}
enums['ShadowReciverPin']['None'] = 'None'
enums['ShadowReciverPin']['ShadowReciver'] = 'Present'
enums['ScrollingUVPin'] = {}
enums['ScrollingUVPin']['NoScrolling'] = 'None'
enums['ScrollingUVPin']['Scrolling'] = 'Present'
enums['AddEmissiveThresholdPin'] = {}
enums['AddEmissiveThresholdPin']['None'] = 'None'
enums['AddEmissiveThresholdPin']['Add'] = 'Present'

enums['OpacityPin'] = {}
enums['OpacityPin']['None'] = 'Opaque'
enums['OpacityPin']['AlphaOpacity'] = 'AlphaOpacity'
enums['OpacityPin']['ColorOpacity'] = 'ColorOpacity'
enums['OrientTypePin'] = {}
enums['OrientTypePin']['None'] = 'NoneType'

##enums['NormalMapPin'] = ['NoNormalMap', 'TangentSpace']
##enums['DiffuseMapPin'] = ['NoDiffuseMap', 'DiffuseMapPresent']
##enums['DarkMapPin'] = ['NoDarkMap', 'DarkMapPresent']
##enums['SpecularMapPin'] = ['NoSpecularMap', 'SpecularMapPresent']
##enums['TemperaturePin'] = ['NoTemperature', 'TemperaturePresent']
##enums['EmissiveMultiplierPin'] = ['NoEmissiveMultiplier', 'EmissiveMultiplierPresent']
##enums['SkeletalMeshPin'] = ['NoTransform', 'TransformVertices']
##enums['EnvMapPin'] = ['NonEnv', 'EnvPresent']
##enums['ShadowCasterPin'] = ['None', 'ShadowCaster']
##enums['ShadowReciverPin'] = ['None', 'ShadowReciver']
##enums['ScrollingUVPin'] = ['NoScrolling', 'Scrolling']
##enums['AddEmissiveThresholdPin'] = ['None', 'Add']
##enums['ObjectColorPin'] = ['NoObjectColor', 'ObjectColorPresent']


data_path = path.normpath(path.join(path.dirname(__file__), '../../../Data'))
print data_path
path.walk(data_path, xdb_visit, Visitor())
print 'OK'