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
	beacon = false;
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

void Node::init(Nanoshield_MRF &mrfObject, bool &findHub, Node &nodeData)
{
	mrfObject.begin();
	if(nodeData.nodeAddress == 0 && !nodeData.acceptJoinRequest)
	{
		findHub = false;
	}
}

void Node::checkForHub(Nanoshield_MRF &mrfObject, bool&findHub, Node &nodeData)
{
  resetNodeData(nodeData);
 	mrfObject.setPanId(0);	
  	mrfObject.setAddress(0);        // Network address
  	mrfObject.setCoordinator(0); // Module is coordinator
  	mrfObject.setPromiscuous(1);
	int numtry = 0;
	while(numtry < 10)
	{
		numtry++;
		if(mrfObject.receivePacket())
		{
			memcpy(&nodeData, mrfObject.getBufferData(true), sizeof(Node));
      if(nodeData.beacon)
			{
        Serial.print(" beacon ");
        Serial.print(nodeData.beacon);
        Serial.print(" hubAddress ");
        Serial.print(this->hubAddress);
        Serial.print(" \n ");
				this->hubAddress = 	nodeData.hubAddress;
				this->panId = nodeData.panId;
				if(sendJoinRequest(mrfObject, nodeData))
				{
          findHub = true;
					break;
				}
			}
		}
		delay(1);
	}
 mrfObject.setPromiscuous(0);
}

bool Node::sendJoinRequest(Nanoshield_MRF &mrfObject, Node &nodeData)
{
	nodeData.beacon = false;
	nodeData.hubNode = false;
	nodeData.endNode = true;
	nodeData.joinRequest = true;
	nodeData.acceptJoinRequest = false;
	nodeData.heartBeat = false;
	nodeData.waterLevel = false;
	nodeData.humidity = 0.0;
	nodeData.panId = this->panId;
	nodeData.nodeAddress = 0;
	nodeData.hubAddress = this->hubAddress;
	if(sendData(mrfObject,nodeData))
	{	
	  //delay(100);
		if(mrfObject.receivePacket())
		{
			delay(2);
			memcpy(&nodeData, mrfObject.getBufferData(true), sizeof(Node));
			if(nodeData.acceptJoinRequest && nodeData.nodeAddress != 0)
			{
				this->nodeAddress = nodeData.nodeAddress;
        Serial.print(" nodeAddress ");
        Serial.print(this->nodeAddress);
        Serial.print(" \n ");
				return true;
			}
		}
	}
	return false;
}

void Node::resetNodeData(Node &nodeData)
{
  memset(&nodeData,0,sizeof(Node));
}

void Node::getSensorData(Node &nodeData)
{
  resetNodeData(nodeData);
  nodeData.waterLevel = true;
  nodeData.humidity = 35.0;  
}

bool Node::sendData(Nanoshield_MRF &mrfObject, Node &nodeData)
{
  mrfObject.startPacket(nodeData.panId, nodeData.nodeAddress);
  mrfObject.writeToBuffer(&nodeData, sizeof(Node));
  if(mrfObject.sendPacket(nodeData.hubAddress))
  {
    return true;  
  }
  return false;
}


