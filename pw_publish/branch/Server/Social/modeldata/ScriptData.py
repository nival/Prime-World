# -*- coding: utf-8 -*-
import sys, time, datetime, json
from jsonserialize import JSONSerialization
from base.helpers import info, warn, err, ClassDict
from baseclasses import *
from changes import *
from collects import *
from ref import *
from binascii import crc32

class ScriptRef(object):
    def __init__( self, obj ):
        if obj.object != 0:
            self.Id = obj.getID()
            self.Type = obj.realdict[obj.object].__class__.__name__
        else:
            self.Id = None
            self.Type = None



class ScriptList:
    ###XXX Какой смысл в этом классе?!!!
    def __init__( self ):
        self.list = []

    def append( self, val ):
        self.list.append( val )

    def remove( self, val ):
        self.list.remove( val )

    def __getitem__( self, key ):
        return self.list[key]

    def __delitem__( self, key ):
        del self.list[key]

    def __setitem__( self, key, val ):
        self.list[key] = val

    def pop( self ):
        val = self.list.pop()
        return val

    def keys( self ):
        return self.list

    def __len__( self ):
        return self.list.__len__()

    def Count( self ):
        return self.list.__len__()

class ScriptTalentSet():
    def __init__( self, force, stats ):
        self.Talents = []
        self.Force = force
        self.Stats = stats


class ScriptHero( Identified ):
    def __init__(self, heroMd, dbRoot, sex, mdRoot, config):

        # db - static data (pf_editor)
        # md - model data

        self.__dict__["id"] = heroMd.getID()
        heroDb = dbRoot.getStaticHero(heroMd)
        self.ActiveTalentSet = heroMd.ActiveTalentSet
        if heroDb:
            self.TalentSets = []
            self.__defaultTalentSet = []
            for tsIdx in xrange(len(heroMd.TalentSets)):
                # текущий талентсет
                self.TalentSets.append(ScriptTalentSet(0, None))
                for tIdx in heroMd.TalentSets[tsIdx].Talents.keys():
                    talentMd = mdRoot.getTalentByID(heroMd.TalentSets[tsIdx].Talents.get(tIdx))
                    if talentMd:
                        self.TalentSets[tsIdx].Talents.append(ScriptTalent(mdRoot, talentMd, dbRoot, sex))

                self.TalentSets[tsIdx].Stats = heroMd.TalentSets[tsIdx].Stats
                self.TalentSets[tsIdx].Force = heroMd.TalentSets[tsIdx].Force

                # дефолтный талантсет
                talPos = 0
                self.__defaultTalentSet.append({})
                tsTalents = dbRoot.getDefaultSetTalents(config, heroDb, tsIdx)
                for row in tsTalents:#heroDb['talents'][tsIdx]:
                    for talent in row:
                        if talent:
                            self.__defaultTalentSet[tsIdx][talPos] = ClassDict(PersistentId=talent.name)
                        else:
                            self.__defaultTalentSet[tsIdx][talPos] = ClassDict(PersistentId="")
                        talPos += 1

            self.Hired = heroMd.Hired
            self.Level = dbRoot.getHeroExpLevel(heroMd.Experience)
            self.Experience = heroMd.Experience
            if sex == 2:
                self.Cost = heroDb['lobbyData']['CostFemale']
            else:
                self.Cost = heroDb['lobbyData']['CostMale']
            self.PersistentId = heroMd.class_name

    def IsTalentDefault(self, persistentId, tIdx, tsIdx):

        # эта логика скопирована с клиента

        if tsIdx < 0 or tsIdx >= len(self.__defaultTalentSet):
            return False

        defTs = self.__defaultTalentSet[tsIdx]

        if tIdx in defTs:
            return defTs[tIdx].PersistentId == persistentId

        return True

class ScriptBuilding( Identified ):
    def __init__( self, building, SD ):
        staticBuilding = SD.getStaticConstruction( building )
        if staticBuilding:
            self.__dict__["id"] = building.getID()
            self.PersistentId = staticBuilding['persistentId']
            self.ClassType = staticBuilding['classType']
            self.ProductionState = building.ProductionState
            self.Level = building.Level
            self.BoostEndTime = building.BoostEndTime

class ScriptFriend():
    def __init__(self, friend):
        self.Id = friend
        
class ScriptTalent( Identified ):
    def __init__( self, modeldata, talent, SD, sex ):

        staticTalent = SD.getStaticTalent( talent )
        if staticTalent:
            self.__dict__["id"] = talent.getID()
            self.DefaultForHero = ScriptRef(talent.defaultForHero)
            self.Soulbound = ScriptRef(talent.Soulbound)
            self.PersistentId = staticTalent['persistentId']
            self.Level = SD.getTalentLevel( talent )
            self.initHeroes(modeldata, SD)

    def initHeroes(self, modeldata, SD):
        for heroId in modeldata.Heroes:
            hero = modeldata.getHeroByID( heroId )
            staticHero = SD.getStaticHero( hero )
            if self.DefaultForHero.Id == heroId:
                setattr(self.DefaultForHero, "PersistentId", staticHero['persistentId'])
            elif self.Soulbound.Id == heroId:
                setattr(self.Soulbound, "PersistentId", staticHero['persistentId'])

    def IsDefaultForHero(self, persistentId):
        if self.DefaultForHero is not None:
            attr = getattr(self.DefaultForHero,"PersistentId", None)
            return attr is not None and attr == persistentId
        return False



class ScriptData( object ):
    def __init__( self, modeldata, SD, sex, config ):
        self.modeldata = modeldata
        self.UserInventory = ScriptList()
        for talentId in self.modeldata.UserInventory:
            talent = self.modeldata.getTalentByID( talentId )
            self.UserInventory.append( ScriptTalent( modeldata, talent, SD, sex ) )

        self.Lord = ClassDict( Fame=self.modeldata.LordInfo.Fame, Gender=sex, Level=SD.getFameLevel(self.modeldata.LordInfo.Fame),
                               LevelOfExpansion=self.modeldata.LordInfo.LevelOfExpansion, Resources=self.modeldata.Resources,
                               NumberOfWins=self.modeldata.LordInfo.GuardInfo.NumberOfWins, UserInventory=self.UserInventory,
                               MinutesSinceLastLogin=(datetime.datetime.fromtimestamp(self.modeldata.LordInfo.CurrentLoginTime) - datetime.datetime.fromtimestamp(self.modeldata.LordInfo.LastLoginTime)).seconds/60,
                               Statistics=self.modeldata.Statistics, TutorialState=self.modeldata.LordInfo.TutorialState,
                               ServerTime=self.modeldata.ServerTime)

        self.Heroes = ScriptList()
        for heroId in self.modeldata.Heroes:
            hero = self.modeldata.getHeroByID( heroId )
            self.Heroes.append( ScriptHero( hero, SD, sex, modeldata, config ) )

        self.Buildings = ScriptList()
        for buildingId in self.modeldata.Buildings:
            building = self.modeldata.getConstructionByID( buildingId )
            self.Buildings.append( ScriptBuilding( building, SD ) )
            
        refResolver(self)
        i = 1
    
    def getObj(self, ref):
        if not ref or not ref.Id or not ref.Type:
            return None
        
        if ref.Type == "Hero":
            for item in self.Heroes:
                if item.id == ref.Id:
                    return item
            return None
        
        #if ref.Type == "Construction":
        #    for item in self.Buildings:
        #        if item.Id == ref.Id:
        #            return item
        #    return None
        
        #if ref.Type == "Talent":
        #    for item in self.UserInventory:
        #        if item.Id == ref.Id:
        #            return item
        #    for hero in self.Heroes:
        #        for item in hero.TalentSet:
        #            if item.Id == ref.Id:
        #                return item 
        #    return None
        
              
class refResolver():
    def __init__(self, obj):
        self.resolveObject(obj, obj)
        
    def resolveObject(self, obj, scriptData):
        for field,value in obj.__dict__.iteritems():
            objType = value.__class__.__name__
            if "Script" in objType:                
                if objType == "ScriptRef":
                    setattr(obj, field, scriptData.getObj(value))
                elif objType == "ScriptList":
                    self.resolveList(value, scriptData)
                else:
                    self.resolveObject(value, scriptData)

    def resolveList(self, obj, scriptData):
        for item in obj:
            self.resolveObject(item, scriptData)
                
        
        
