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
#include "Nanoshield_MRF.h"
//~/Desktop/Project/test/Zigbee_NW/Source/Nod
#include"/home/snapiotlenovo1/Desktop/Project/test/Zigbee_NW/Source/Node_Setting.h"
//#include "/home/snapiotlenovo1/Desktop/Project/test/Zigbee_NW/Source/Nanoshield_MRF.h"
class Node: public NodeSetting
{
	public:
	Node();
	bool sendJoinRequest(Nanoshield_MRF &mrfObject, Node &nodeData);
	bool sendData(Nanoshield_MRF &mrfObject, Node &nodeData);
	void init(Nanoshield_MRF &mrfObject,bool &findHub, Node &nodeData);
	void checkForHub(Nanoshield_MRF &mrfObject, bool&findHub, Node &creatNode);
  void sleepMCU();
  void getSensorData(Node &nodeData);
  void resetNodeData(Node &nodeData);
  
};

#endif
