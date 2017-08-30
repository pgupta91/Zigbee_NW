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
#include"Node_Setting.h"
class Hub: public NodeSetting
{
	public:
	Hub();
	static uint16_t AddressAllocated;
	void assignAddress();
	void sendData(void* data);
};
uint16_t Hub:: AddressAllocated = 0;

#endif
