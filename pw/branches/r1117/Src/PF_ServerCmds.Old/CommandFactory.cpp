/*
 * ListenerThread.cpp
 *
 *  Created on: 14.10.2008
 *      Author: earnol
 */

#include "../Server/src/TypeProxy.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "../System/nlist.h"
#include "../System/nstring.h"
#include "../System/nvector.h"
using namespace nstl;
#include "../System/StrProc.h"
#include "../System/Logger.h"
#include "../System/LoggerStream.h"
#include "../System/SystemLog.h"


#include "CommandFactory.h"

char const * const CommandFactory::_internal_Class_Name_ = "CommandFactory";
CommandFactory::TypeInfo const *CommandFactory::getTypeInfo(int) {return &SRegister_ti;};          
CommandFactory::TypeInfo const *CommandFactory::getTypeInfo() {return &SRegister_ti;};             
CommandFactory::TypeInfo CommandFactory::SRegister_ti = CommandFactory::RegisterCmdClass();                

CommandFactory::TypeDB &CommandFactory::getCommandsDB()
{
  static TypeDB m_commandsDB;
  return m_commandsDB;
}

char const * CommandFactory::GetCmdClassName(int) 
{
  return _internal_Class_Name_;
}
CommandFactory *CommandFactory::CreateInstance(unsigned int nID)
{
  CommandFactory *pRet = NULL;
  if(nID < (unsigned int)CommandFactory::getCommandsDB().size())
  {
    pRet = CommandFactory::getCommandsDB()[nID]->m_pCreateFunc(nID);
    NI_ASSERT(pRet->GetCmdClassName() == CommandFactory::getCommandsDB()[nID]->m_sTypeName, "server and client of different versions?");
  }
  return pRet;
}

int CommandFactory::getCommandIDByName(nstl::string const &name)
{
  TypeDB::iterator it = CommandFactory::getCommandsDB().begin();
  int nRet = 0;

  for(; it != CommandFactory::getCommandsDB().end(); it++)
  {
    if(strcmp((*it)->m_sTypeName, name.c_str()) == 0)
    {
      return nRet;
    }
    nRet++;
  }
  return -1;
}


