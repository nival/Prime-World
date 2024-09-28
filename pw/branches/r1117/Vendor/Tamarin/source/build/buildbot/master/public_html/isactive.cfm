<!---
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
# The Original Code is [Open Source Virtual Machine.].
#
# The Initial Developer of the Original Code is
# Adobe System Incorporated..
# Portions created by the Initial Developer are Copyright (C) 2009
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#   Adobe AS3 Team

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
--->

<cfsetting showDebugOutput="false"/>
<cfparam name="url.builder" default="compile"/>
<cfset buildbot_url = "http://10.171.22.12:8750">

<!--- Create the XML data to post. --->
<cfsavecontent variable="rpcRequestPacket">
<?xml version="1.0"?>
<methodCall>
    <methodName>isBuildSetActive</methodName>
        <params>
            <param>
                <value>
                    <array>
                        <data>
                            <value><string><cfoutput>#url.builder#</cfoutput></string></value>
                        </data>
                    </array>
                </value>
            </param>
        </params>
</methodCall>
</cfsavecontent>

<!---
 Post the XML data to catch page. We are going
 to post this value as an XML object will actually
 just post it as an XML body.
--->
<cfhttp url="#buildbot_url#/xmlrpc"
    method="POST"
    result="rpcResponse">
    <cfhttpparam type="XML"
        value="#rpcRequestPacket.Trim()#"/>
</cfhttp>

<cfset active = false>
<cfif rpcResponse.statusCode EQ "200 OK">
    <cfset response = xmlParse(rpcResponse.fileContent)>
    <cfset active = iif(response.methodResponse.params.param.value.boolean.XmlText EQ "1", true, false)>
</cfif>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
 "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
<head>
    <link href="buildbot.css" rel="stylesheet" type="text/css" />
</head>

<body vlink="#800080"><cfif active>active<cfelse>idle</cfif></body>
