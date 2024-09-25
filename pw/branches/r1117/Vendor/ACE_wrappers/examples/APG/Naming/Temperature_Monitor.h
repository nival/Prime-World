// $Id: Temperature_Monitor.h 80826 2008-03-04 14:51:23Z wotte $

#ifndef TEMPERATURE_MONITOR_H
#define TEMPERATURE_MONITOR_H

#include "Thermometer.h"
#include "Temperature_Monitor_Options.h"
#include "Naming_Context.h"

class Temperature_Monitor
  {
  public:
    Temperature_Monitor( Temperature_Monitor_Options & opt,
                         Naming_Context & naming_context );

    void monitor();

  protected:
    void record_temperature(float temp);
    void record_failure();
    void reset_device(Name_Binding_Ptr & resetCount);

  private:
    Thermometer * thermometer_;
    Temperature_Monitor_Options & opt_;
    Naming_Context & naming_context_;
  };

#endif /* TEMPERATURE_MONITOR_H */
