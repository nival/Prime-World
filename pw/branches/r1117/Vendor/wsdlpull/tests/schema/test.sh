#!/bin/bash
#script to test schema validator
type schema
schema first-building-blocks.xsd -i first.xml >/dev/null;echo $?;
schema list.xsd -i list.xml >/dev/null ;echo $?;
schema choice.xsd -i choice.xml >/dev/null ;echo $?;
schema po.xsd -i po.xsi >/dev/null ;echo $?;
schema import.xsd -i import.xml >/dev/null ; echo $?;
schema validate.xsd -i validate.xml >/dev/null ; echo $?;
schema union.xsd -i union.xml >/dev/null ; echo $?;
