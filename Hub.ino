/**
 * Receive a character string using the MRF24J40 module.
 *
 * Copyright (c) 2015 Circuitar
 * This software is released under the MIT license. See the attached LICENSE file for details.
 */
#include <SPI.h>
#include "Hub.h"
#define CS 7;


// Create wireless module object (MRF24J40MA/B/C/D/E)
Nanoshield_MRF mrf(MRF24J40MA,7); // Make sure to select the right module
bool toggle = true;
Hub myNode;
Hub nodeData;
void setup() {
  Serial.begin(9600);
  myNode.init(mrf);

}
///CHECK INIT()

void loop() 
{
  Serial.println(toggle);
  int i = 0;
  if(toggle)
  {
    i = 0;
    while(i<1)
    {
      myNode.sendBeacon(mrf, nodeData);
      delay(2);
      i++;
    }
    toggle = false;
  }
  else if(toggle)
  {
    i = 0;
    while(i<1)
    {
      myNode.rxData(mrf, nodeData);
      Serial.print("endNode ");
      Serial.print(nodeData.endNode);
      Serial.print(" humidity ");
      Serial.print(nodeData.humidity);
      Serial.print(" waterLevel ");
      Serial.print(nodeData.waterLevel);
      Serial.print(" NodeAddress ");
      Serial.print(nodeData.nodeAddress);
      Serial.print("\n");
      delay(2);
      i++;
    }
    toggle = true;
  }
  //delay(500);
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

