/******************************************************************
  Author  : Gaël PORTÉ (portegael.pro@gmail.com)
  Date    : Novembre 2nd, 2017
  Title   : sigfox_driver.h
  Project : Iot Bird Feeder
  Desc    : Driver used to send sigfox messages
******************************************************************/
#ifndef _SIGFOX_DRIVER_H_
#define _SIGFOX_DRIVER_H_

#include "Arduino.h"

void SFX_SendMessage(byte *humidity);

#endif // _SIGFOX_DRIVER_H_


