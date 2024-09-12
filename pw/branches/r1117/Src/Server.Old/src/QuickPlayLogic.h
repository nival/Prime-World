/*
 * ListenerThread.h
 *
 *  Created on: 14.10.2008
 *      Author: earnol
 */

#ifndef QUICKPLAYLOGIC_H_
#define QUICKPLAYLOGIC_H_

#include "TypeProxy.h"
#include <time.h>
#include "../../System/basic.h"
#include "ServerThread.h"
#include "../../Net/TSList.h"
#include "../../System/Ring.h"
#include "../../System/Singleton.h"
#include "../../System/nstring.h"
#include "mysql.h"
#include "SQLStream.h"
#include "DatabaseThread.h"

class QuickPlayLogic
{
public:
  QuickPlayLogic();
  virtual ~QuickPlayLogic();

  //perform quick play logic
  time_t m_nQuickPlayTimeLeft;
  time_t m_nQuickPlayTimePrev;
  void perform();
  bool formQuickGames();
  void notifyQuickGamesClients();
};


#endif /* QUICKPLAYLOGIC_H_ */
