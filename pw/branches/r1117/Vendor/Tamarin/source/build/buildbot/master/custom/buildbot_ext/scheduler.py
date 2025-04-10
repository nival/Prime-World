# -*- Mode: Python; indent-tabs-mode: nil -*-
# ***** BEGIN LICENSE BLOCK *****
# Version: MPL 1.1/GPL 2.0/LGPL 2.1
#
# The contents of this file are subject to the Mozilla Public License Version
# 1.1 (the "License"); you may not use this file except in compliance with
# the License. You may obtain a copy of the License at
# http://www.mozilla.org/MPL/
#
# Software distributed under the License is distributed on an "AS IS" basis,
# WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
# for the specific language governing rights and limitations under the
# License.
#
# The Original Code is [Open Source Virtual Machine].
#
# The Initial Developer of the Original Code is
# Adobe System Incorporated.
# Portions created by the Initial Developer are Copyright (C) 2005-2006
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#
# Alternatively, the contents of this file may be used under the terms of
# either the GNU General Public License Version 2 or later (the "GPL"), or
# the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
# in which case the provisions of the GPL or the LGPL are applicable instead
# of those above. If you wish to allow use of your version of this file only
# under the terms of either the GPL or the LGPL, and not to allow others to
# use your version of this file under the terms of the MPL, indicate your
# decision by deleting the provisions above and replace them with the notice
# and other provisions required by the GPL or the LGPL. If you do not delete
# the provisions above, a recipient may use your version of this file under
# the terms of any one of the MPL, the GPL or the LGPL.
#
# ***** END LICENSE BLOCK *****

from zope.interface import implements
from twisted.internet import reactor
from twisted.application import service, internet, strports
from twisted.python import log, runtime
from twisted.protocols import basic
from twisted.cred import portal, checkers
from twisted.spread import pb

from buildbot import interfaces, buildset, util, pbutil
from buildbot.status import builder
from buildbot.sourcestamp import SourceStamp
from buildbot.changes.maildir import MaildirService
from buildbot.process.properties import Properties

from buildbot.scheduler import *


class Scheduler(Scheduler):
    '''The buildbot.scheduler.Scheduler class is sublclassed (with the same name to not have 
        to modify any of the master.cfg code) from the original source to add the ability to 
        handle buildsets'''

    def fireTimer(self):
        # clear out our state
        self.timer = None
        self.nextBuildTime = None
        changes = self.unimportantChanges + self.importantChanges
        self.importantChanges = []
        self.unimportantChanges = []

        # Only add builders to the buildset that are currently online
        buildset_builderNames = []
        for builder_name in self.builderNames:
            # Get a builder from the BotMaster:
            builder = self.parent.botmaster.builders.get(builder_name)
            if builder.builder_status.getState()[0] == 'idle':
                buildset_builderNames.append(builder_name)

        # create a BuildSet, submit it to the BuildMaster
        bs = buildset.BuildSet(buildset_builderNames,
                               SourceStamp(changes=changes),
                               properties=self.properties)
        self.submitBuildSet(bs)

class BuilderDependent(Dependent):
    """This scheduler runs some set of 'downstream' builds when the
    'upstream' scheduler has completed successfully."""
    
    fileIsImportant = None
    
    def __init__(self, name, upstream, callbackInterval, builderNames, builderDependencies, 
                    properties={}, fileIsImportant=None):
        Dependent.__init__(self, name, upstream, builderNames, properties)
        # - each builder must have a dependent that is in the upstream builder
        # - multiple builders can be dependent on the same upstream builder
        self.builderDependencies = builderDependencies
        self.callbackInterval = callbackInterval
        
        if fileIsImportant:
            assert callable(fileIsImportant)
            self.fileIsImportant = fileIsImportant
        
        for builder_name in self.builderNames:
            dependent_builder = ''
            # Get the depenent builder
            for dependent in self.builderDependencies:
                if builder_name == dependent[0]:
                    dependent_builder = dependent[1]
                    break
            
            # Make sure there is a defined dependent builder
            if dependent_builder == '':
                errmsg = "The builder %s has no corresponding dependent builder" % builder_name
                assert False, errmsg
            
            # Make sure that the dependent builder is defined in the upstream scheduler
            if dependent_builder not in self.upstream.listBuilderNames():
                errmsg = "The dependent builder %s is not defined in the upstream scheduler %s" % (dependent_builder, self.upstream.name)
                assert False, errmsg
                
        self.timer = None
        self.source_stamp = None
       
    def upstreamBuilt(self, ss):
        # Only add builders to the buildset that are currently online and if the dependent builder 
        # also built this change.
        
        # If a fileIsImportant function is defined, check the files before determining buildsets
        if self.fileIsImportant:
            startThisBuildSet = False
            # SourceStamp provides us with a tuple of changes, loop through and check them all
            for change in ss.changes:
                if self.fileIsImportant(change):
                    # If any file is important, we start the buildSet
                    startThisBuildSet = True
                    break
            if not startThisBuildSet:
                # no important files found, do not continue with this buildset
                return
        
        if self.source_stamp == None:
            # This is the first time that the ss has been seen, this is NOT a callback
            self.source_stamp = ss
        else:
            # This can either be a callback or a new ss passed in from upstream builder
            try:
                 revision_prev = int(self.source_stamp.revision)
                 revision_curr = int(ss.revision)
            except ValueError:
                errmsg = "BuilderDependent.upstreamBuilt has an unknown ss.revison: %s" % (ss.revision)
                assert False, errmsg

            # ss.revision is an OLDER REV than self.source_stamp.revision
            if revision_curr < revision_prev: 
                # This means we are a callback, and during sleep period a new build request 
                # has come in and is now in control, we can just stop running.
                return
            
            # ss.revision is a NEWER REV than self.source_stamp.revision
            elif revision_curr > revision_prev:
                # This would indicate a new build and we need to merge ss and self.source_stamp
                ss.mergeWith([self.source_stamp])
                self.source_stamp = ss
            
            # Revisions are the same so this is the callback
            # else revision_curr == revision_prev
        
        
        buildset_builderNames = []
        for builder_name in self.builderNames:
            # Get the depenent builder
            for dependent in self.builderDependencies:
                if builder_name == dependent[0]:
                    dependent_builder = dependent[1]
                    break
            
            # Get the dependent builder
            dep_builder = self.parent.getStatus().getBuilder(dependent_builder)
            # Determine the revision of the last build for the dependent builder
            # need to make sure that the builder has at least one previous build
            try:
                dep_ss = dep_builder.getLastFinishedBuild().getSourceStamp()
            except AttributeError:
                dep_ss = SourceStamp()
            
            
            # Only continue the check if the dependent builder built the sourceStamp, 
            if ss.revision == dep_ss.revision:
                # Get a builder from the BotMaster:
                builder = self.parent.botmaster.builders.get(builder_name)
                if builder.builder_status.getState()[0] == 'building':
                    # There is a builder in this scheduler that is active so we need
                    # to NOT start the build yet, but instead callback in X seconds
                    # to see if all of the builders are available.
                    self.timer = reactor.callLater(self.callbackInterval, self.upstreamBuilt, ss)
                    return
                # Add the builder to the set if it is idle (not building and not offline)
                if builder.builder_status.getState()[0] == 'idle':
                    buildset_builderNames.append(builder_name)
                    

        bs = buildset.BuildSet(buildset_builderNames, ss,
                    properties=self.properties)
        self.submitBuildSet(bs)
        
        # Clear the tracked source stamp
        self.source_stamp = None

