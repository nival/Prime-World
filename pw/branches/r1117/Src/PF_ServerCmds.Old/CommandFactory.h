/*
 * ListenerThread.h
 *
 *  Created on: 14.10.2008
 *      Author: earnol
 */

#ifndef COMMANDFACTORY_H_
#define COMMANDFACTORY_H_

#include <typeinfo>
#include "../System/nvector.h"
#include "../System/nstring.h"
#include "../System/nlist.h"
#include "../System/basic.h"


#define REG_COMMAND_H_FACTORY(clName)                                                       \
  static  CommandFactory::TypeInfo SRegister_ti;                                            \
  friend  class ClientThread;                                                               \
  friend  class ClientSenderThread;                                                         \
  friend  class DatabaseThread;                                                             \
  static  char const *GetCmdClassName(int);                                                 \
  static  char const * const _internal_Class_Name_;                                         \
  static  CommandFactory::TypeInfo const *getTypeInfo(int);                                 \
public:                                                                                     \
  virtual CommandFactory::TypeInfo const *getTypeInfo();                                    \
  virtual char const *GetCmdClassName() {return clName::GetCmdClassName(1);}                \
  static CommandFactory::TypeInfo RegisterCmdClass()                                        \
{                                                                                           \
  return CommandFactory::TypeInfo(clName::GetCmdClassName(1), (CommandFactory::CommandCreateFunc)clName::CreateInstance);\
}


#define REG_COMMAND_H(clName, clpName)                                                     \
  REG_COMMAND_H_FACTORY(clName)                                                            \
  clName(unsigned int nId, CreatParamForFactory &crp): clpName(nId, crp)                   \
  {                                                                                        \
    initCommonFields();                                                                    \
  }                                                                                        \
  static clName *CreateInstance(unsigned int nID) {CreatParamForFactory crp; return new clName(nID, crp);}              \
  static clName *DynamicCast(LobbyCommand *pCmd)                                                                        \
  {                                                                                                                     \
    NI_ASSERT((getTypeInfo(1)->m_nCommandID != -1) && (-1 != pCmd->getCommandID()), "Initialized command.")             \
    if(getTypeInfo(1)->m_nCommandID == pCmd->getCommandID())                               \
      return (clName *)pCmd;                                                               \
    else                                                                                   \
      return NULL;                                                                         \
  }


#define REG_COMMAND_CPP(clName)                                                              \
  char const * clName::GetCmdClassName(int) {return _internal_Class_Name_;};                 \
  CommandFactory::TypeInfo const *clName::getTypeInfo(int) {return &SRegister_ti;};          \
  CommandFactory::TypeInfo const *clName::getTypeInfo() {return &SRegister_ti;};             \
  char const * const clName::_internal_Class_Name_ = #clName;                                \
  CommandFactory::TypeInfo clName::SRegister_ti = clName::RegisterCmdClass();                \


class CommandFactory: public CObjectBase
{
  OBJECT_BASIC_METHODS(CommandFactory);

public:
  //obtain command ID for lobby command factory
         int getCommandID() const                         {return m_nCommandID;}
  static int GetCommandID(CommandFactory &factoryCommand) {return factoryCommand.m_nCommandID;}

  struct CreatParamForFactory {};
  typedef CommandFactory* (*CommandCreateFunc)(unsigned int);
  struct TypeInfo
  {
    static bool Lexicogphical(TypeInfo const *elem1, TypeInfo const *elem2)
    {
      return strcmp(elem1->m_sTypeName, elem2->m_sTypeName) < 0;
    }
    TypeInfo(char const * const str, CommandCreateFunc  pCreateFunc):m_sTypeName(str), m_pCreateFunc(pCreateFunc), m_nCommandID(-1)
    {
      CommandFactory::getCommandsDB().push_back(this);
      nstl::sort(CommandFactory::getCommandsDB().begin(), CommandFactory::getCommandsDB().end(), Lexicogphical);
      TypeDB::iterator b = CommandFactory::getCommandsDB().begin();
      TypeDB::iterator e = CommandFactory::getCommandsDB().end();
      for(unsigned int nI = 0; b != e; nI++, b++)
      {
        (*b)->m_nCommandID = nI;
      }
    }
    char const * const m_sTypeName;
    CommandCreateFunc  m_pCreateFunc;
    int                m_nCommandID;
  private:
    TypeInfo& operator = ( const TypeInfo&) {return *this;}
  };

  CommandFactory(int nId, CreatParamForFactory &):  m_nCommandID(nId) {}
  CommandFactory(): m_nCommandID(-1)
  {
    //default constructor
  }
protected:
   int getCommandIDByName(nstl::string const &name);
  void setCommandIDByName(nstl::string const &name) {m_nCommandID = getCommandIDByName(name);}
  void setCommandID()                               {m_nCommandID = getTypeInfo()->m_nCommandID;}
private:
  int     m_nCommandID;    //command ID to be created

  typedef nstl::vector<TypeInfo *> TypeDB;
  static TypeDB &getCommandsDB();
public: static CommandFactory *CreateInstance(unsigned int nID);
  REG_COMMAND_H_FACTORY(CommandFactory);
};

#endif /* COMMANDFACTORY_H_ */
