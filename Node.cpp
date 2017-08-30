#include <Nanoshield_MRF.h>
#include "Node.h"
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
Node::Node()
{
	hubNode = false;
	endNode = true;
	joinRequest = false;
	acceptJoinRequest = false;
	heartBeat = false;
	waterLevel = false;
	humidity = 0.0;
	panId = 0;
	nodeAddress = 0;
	hubAddress = 0;
}

void Node::init(Nanoshield_MRF &mrfObject)
{
	if(nodeAddress == 0 && !acceptJoinRequest)
	{
		sendJoinRequest(mrfObject);	
	}
}

void Node::sendJoinRequest(Nanoshield_MRF &mrfObject)
{
	if(!joinRequest && !acceptJoinRequest)
	{
		NodeSettings newNode;
		newNode.hubNode = false;
		newNode.endNode = true;
		newNode.joinRequest = true;
		newNode.acceptJoinRequest = false;
		newNode.heartBeat = true;
		newNode.waterLevel = false;
		newNode.humidity = 0.0;
		newNode.panId = panId;
		newNode.nodeAddress = 0;
		newNode.hubAddress = 300;
		mrfObject.setAddress(newNode.nodeAddress)
		mrfObject.startPacket();
		mrfObject.writeToBuffer(&newNode, sizeof(NodeSettings));
		mrfObject.sendPacket(newNode.hubAddress);
	}

	
}

void Node::setMyAddress()
{
	if(acceptJoinRequest)
	{
		void*data = getdataBuffer(true);
		readSettingFromData(data);
	}
}