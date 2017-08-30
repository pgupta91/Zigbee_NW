/**
 * This is our new Arduino library to use the 2.4GHz MRF24J40 wireless radio from Microchip.
 * It supports communication using the 802.15.4 wireless protocol at the MAC level, and enables
 * use of the MRF24J40MA/B/C/D/E wireless modules from Microchip.
 *
 * Copyright (c) 2015 Circuitar
 * This software is released under the MIT license. See the attached LICENSE file for details.
*/
#ifndef NODE_SETTING_H
#define NODE_SETTING_H
//#include "Nanoshield_MRF.h"
class NodeSetting
{
	public:
	bool hubNode;
	bool endNode;
	bool joinRequest;
	bool acceptJoinRequest;
	bool heartBeat;
	bool waterLevel;
	float humidity;
	uint16_t panId;
	uint16_t nodeAddress;
	uint16_t hubAddress;
	
	//void readSettingFromData(void* data);
    void sleepMCU() = 0;
	//char* writeSettingToData();
};
#endif