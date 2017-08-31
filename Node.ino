/**
 * Receive a character string using the MRF24J40 module.
 *
 * Copyright (c) 2015 Circuitar
 * This software is released under the MIT license. See the attached LICENSE file for details.
 */
#include <SPI.h>
#include "Node.h"
#define CS 7;


// Create wireless module object (MRF24J40MA/B/C/D/E)
Nanoshield_MRF mrf(MRF24J40MA,7); // Make sure to select the right module
Node myNode;
Node nodeData;
bool findHub = true;
void setup() {
  Serial.begin(9600);
  myNode.init(mrf, findHub, nodeData);

}
///CHECK INIT()

void loop() 
{
  Serial.println(findHub);
  if(!findHub)
  {
    myNode.checkForHub(mrf, findHub, nodeData);
  }
  else
  {
    myNode.getSensorData(nodeData);
    nodeData.endNode = true;
    nodeData.panId = myNode.panId;
    nodeData.hubAddress = myNode.hubAddress;
    nodeData.nodeAddress = myNode.nodeAddress;
    myNode.sendData(mrf,nodeData);
    delay(2);
  }
  //delay(100);
  /*// If a packet has been received, print the string in it
  if (mrf.receivePacket()) {
    Serial.println(mrf.readString());
    
    // If you want to assign it to a variable, you must use "const":
    //   const char* str = mrf.readString();
    //   Serial.println(str);
    // Note: this is simple and efficient, but you won't be able to overwrite the data in the string
    //       returned by readString(), and when you call receivePacket() again it might be overwritten.
    //       If that doesn't work for you, use example ReadStringIntoBuffer.
  }*/
}

