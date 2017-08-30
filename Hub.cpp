#include <Nanoshield_MRF.h>
#include "Hub.h"
/*
	bool hubNode;
	bool endNode;
	bool joinRequest;
	bool heartBeat;
	bool waterLevel;
	float humidity;
	uint16_t panId;
	uint16_t myAddress;
	uint16_t hubAddress;
	*/
Hub::Hub()
{
	hubNode = true;
	endNode = false;
	joinRequest = false;
	acceptJoinRequest = false;
	heartBeat = false;
	waterLevel = false;
	humidity = 0.0;
	panId = 1;
	nodeAddress = 0;
	hubAddress = 300;
}

void Hub::assignAddress()
{
	if(joinRequest)
	{
		NodeSettings newNode;
		newNode.hubNode = false;
		newNode.endNode = true;
		newNode.acceptJoinRequest = true;
		newNode.heartBeat = true;
		newNode.waterLevel = false;
		newNode.humidity = 0.0;
		newNode.panId = panId;
		newNode.nodeAddress = ++AddressAllocated;
		newNode.hubAddress = 300;
	}
}
