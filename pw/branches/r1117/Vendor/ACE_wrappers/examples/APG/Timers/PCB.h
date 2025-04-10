/* -*- C++ -*- */
// $Id: PCB.h 80826 2008-03-04 14:51:23Z wotte $

#if !defined(PCB_H)
#define PCB_H

// Listing 1 code/ch20
class PCB
{
public:
  PCB ();
  virtual ~PCB ();

  // Set/get the timer id that is being handled by this instance.
  void setID (long timerID);
  long getID (void) const;

  // Handle a timeout event, cancel, and close.
  virtual int handleEvent (const void *arg);
  virtual int handleCancel (void);
  virtual int handleClose (void);
 
private:
  long timerID_;
  int count_;
};
// Listing 1

#endif /*PCB_H*/
