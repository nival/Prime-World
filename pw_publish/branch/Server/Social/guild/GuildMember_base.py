# -*- coding: utf-8 -*-
#automatically generated file first time, than you can modify it.

#!/usr/bin/env python

class GuildMember_base:
    def serializeToFile( self, file, name ):
        pass

    def getBestHeroRating(self):
        maxRating = 0.0
        for day, ratingInfo in self.HeroRatings.iteritems():
            maxRating = max(maxRating, ratingInfo.HeroRating)
        return maxRating
