// $Id: RecordingDeviceFactory.cpp 80826 2008-03-04 14:51:23Z wotte $

#include "RecordingDevice.h"
#include "RecordingDeviceFactory.h"
#include "RecordingDevice_Text.h"

RecordingDevice *RecordingDeviceFactory::instantiate (int argc,
                                                      ACE_TCHAR *argv[])
{
  RecordingDevice * device = 0;

  // Determine the implementation based on the values of argv
  // Exclude 2
  device = new TextListenerAcceptor ();
  // Exclude 2
  
  // Initialize the device with the remaining parameters.
  if (device->init (argc, argv) < 0)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("RecordingDeviceFactory::instantiate() - ")
                       ACE_TEXT ("%s->init(argc, argv)"),
                       device->get_name()),
                      0);
  return device;
}
