/**
 * This is our new Arduino library to use the 2.4GHz MRF24J40 wireless radio from Microchip.
 * It supports communication using the 802.15.4 wireless protocol at the MAC level, and enables
 * use of the MRF24J40MA/B/C/D/E wireless modules from Microchip.
 *
 * Copyright (c) 2015 Circuitar
 * This software is released under the MIT license. See the attached LICENSE file for details.
*/
#ifndef HUB_H
#define HUB_H

#include<stdio.h>
#include<string.h>
//#include"./Node_Setting.h"
#include "Nanoshield_MRF.h"
#include"/home/snapiotlenovo1/Desktop/Project/test/Zigbee_NW/Source/Node_Setting.h"
//#include "/home/snapiotlenovo1/Desktop/Project/test/Zigbee_NW/Source/Nanoshield_MRF.h"
class Hub: public NodeSetting
{
	public:
	Hub();
	void assignAddress(Nanoshield_MRF &mrfObject, Hub &nodeData);
	void sendData(void* data);
	void init(Nanoshield_MRF &mrfObject);
  bool sendData(Nanoshield_MRF &mrfObject, Hub &nodeData);
  void sendBeacon(Nanoshield_MRF &mrfObject, Hub &txNodeData);
  void rxData(Nanoshield_MRF &mrfObject, Hub &rxNodeData);
};
static uint16_t AddressAllocated = 0;

#endif
