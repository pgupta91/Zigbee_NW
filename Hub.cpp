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
	beacon = false;
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

void Hub::init(Nanoshield_MRF &mrfObject)
{
	mrfObject.begin();
	mrfObject.setPanId(this->panId);	
  	mrfObject.setAddress(this->hubAddress);        // Network address
  	mrfObject.setCoordinator(this->hubNode);
    Serial.print(" hubAddress ");
    Serial.print(this->hubAddress);
    Serial.print(" \n ");
  
}

void Hub::sendBeacon(Nanoshield_MRF &mrfObject, Hub &txNodeData)
{
	txNodeData.beacon = true;
  txNodeData.hubNode = true;
  txNodeData.joinRequest = false;
  txNodeData.acceptJoinRequest = false;
	txNodeData.nodeAddress = 400;
	txNodeData.panId = this->panId;
	txNodeData.hubAddress = this->hubAddress;
  sendData(mrfObject, txNodeData);
}
void Hub::rxData(Nanoshield_MRF &mrfObject, Hub &rxNodeData)
{
	if(mrfObject.receivePacket())
	{
		memcpy(&rxNodeData, mrfObject.getBufferData(true), sizeof(Hub));
	}
	if(rxNodeData.joinRequest && rxNodeData.nodeAddress == 0)
	{
		assignAddress(mrfObject,rxNodeData);
	}
	else
	{
		// save data to file etc....	
	}
	
}
void Hub::assignAddress(Nanoshield_MRF &mrfObject, Hub &nodeData)
{
	nodeData.beacon = false;
	nodeData.hubNode = false;
	nodeData.endNode = true;
	nodeData.acceptJoinRequest = true;
	nodeData.heartBeat = true;
	nodeData.waterLevel = false;
	nodeData.humidity = 0.0;
	nodeData.panId = this->panId;
	nodeData.nodeAddress = ++AddressAllocated;
	nodeData.hubAddress = this->hubAddress;
  Serial.print(" Allocated nodeAddress ");
  Serial.print(nodeData.nodeAddress);
  Serial.print(" AddressAllocated ");
  Serial.print(AddressAllocated);
  Serial.print(" \n ");
	if(!sendData(mrfObject, nodeData))
	{
		--AddressAllocated;
    Serial.print(" Allocation Failed ");
	}
	//delay(2);
}

bool Hub::sendData(Nanoshield_MRF &mrfObject, Hub &nodeData)
{
  mrfObject.startPacket(nodeData.panId, nodeData.hubAddress);
  mrfObject.writeToBuffer(&nodeData, sizeof(Hub));
  if(mrfObject.sendPacket(nodeData.nodeAddress))
  {
    return true;  
  }
  return false;
}
