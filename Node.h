/**
 * This is our new Arduino library to use the 2.4GHz MRF24J40 wireless radio from Microchip.
 * It supports communication using the 802.15.4 wireless protocol at the MAC level, and enables
 * use of the MRF24J40MA/B/C/D/E wireless modules from Microchip.
 *
 * Copyright (c) 2015 Circuitar
 * This software is released under the MIT license. See the attached LICENSE file for details.
*/
#ifndef NODE_H
#define NODE_H

#include<stdio.h>
#include<string.h>
#include"Node_Setting.h"
class Node: public NodeSetting
{
	public:
	NODE();
	void sendJoinRequest();
	void sendData(void* data);
	void init();
};

#endif
