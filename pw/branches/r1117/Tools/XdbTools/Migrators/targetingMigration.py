import MigratorsFramework as MF
import re
from os import path
reload(MF)

params = []
params.append('attackerAllyWeight')
params.append('attackerHeroWeight')
params.append('attackerMasterWeight')
params.append('attackerMeWeight')
params.append('attackerTowerWeight')
params.append('chaseRange')
params.append('currentTargetWeight')
params.append('healthWeight')
params.append('masterTargetWeight')
params.append('rangeWeight')
params.append('targetingRange')
params.append('targetRevisionTime')
params.append('unitTargetWeight')
params.append('unitTypeTableWeight')
params.append('weightMaximumRangePersent')

handledFiles = []
def includeIntoSection(text):
    logicContent = text.children
    # main targeting node
    nod = MF.Node('targetingPars')
    logicContent['targetingPars'] = [nod]
    fName = MF.curFileProcessing.split('\\')[-1][:-4]
    handledFiles.append(fName)
    nod.attrs['href'] = "/GameLogic/" + fName
    nod.attrs['id'] = MF.GetId_GUID()
    # targeting sub-node
    subNod = MF.Node('UnitTargetingParameters')
    nod.children['UnitTargetingParameters'] = [subNod]
    for par in params:
        res = logicContent.get(par, None)
        if res:
            subNod.children[par] = res
            del logicContent[par]

    return text

def main():
    MF.run('UnitLogicParameters', includeIntoSection, MF.dataPath('GameLogic'))
    for hf in handledFiles:
        print(hf)
    print "done"

if __name__ == "__main__":
    main()
