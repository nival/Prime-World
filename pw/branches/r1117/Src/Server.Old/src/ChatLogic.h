/*
 * ChatLogic.h
 *
 *  Created on: 14.10.2008
 *      Author: earnol
 */

#ifndef CHATLOGIC_H_
#define CHATLOGIC_H_

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

class ChatLogic
{
public:
  ChatLogic();
  virtual ~ChatLogic();

  time_t m_nLeaveChannelTimeLeft;
  time_t m_nLeaveChannelTimePrev;
  void perform();
  void notifyLeaveChannel();
};


#endif /* CHATLOGIC_H_ */
