#include <painlessMesh.h>
#include <Arduino_JSON.h>

#define   MESH_PREFIX     "caspiannoor"
#define   MESH_PASSWORD   "1234test"
#define   MESH_PORT       5555

IPAddress myIP(0,0,0,0);
IPAddress myAPIP(0,0,0,0);

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;
JSONVar myVar;
String nodeName = "NODE_4"; // Name needs to be unique

const int ledPin = 2 ;
const int ledPin1 = 14;

// Needed for painless library

void sendMessage() { //Send message to all nodes
 String msg =   "50";
 
  
 mesh.sendBroadcast( msg );

  
  //Serial.printf("Send");
//  taskSendMessage.setInterval( random( TASK_SECOND * 1, TASK_SECOND * 5 ));
}

Task taskSendMessage( TASK_SECOND * 1  , TASK_FOREVER, &sendMessage );


void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("startHere: Received from %u msg=%d\n", from, msg.c_str());
//  analogWrite(ledPin , msg.toInt());
//  analogWrite(ledPin1 , msg.toInt());
}


void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}

void setup()
{
  Serial.begin(115200);
  Serial.println(nodeName);
//  mesh.setDebugMsgTypes( ERROR | STARTUP | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages
  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
  myAPIP = IPAddress(mesh.getAPIP());
  Serial.println("My AP IP is " + myAPIP.toString());

  myIP = IPAddress(mesh.getStationIP());
  Serial.println("My IP is " + myIP.toString());

//
//#ifdef ENABLE_LOG
//  Serial.println(JSON.stringify(myVar));
//#endif
//  return JSON.stringify(myVar);

}



void loop()
{
  mesh.update();
  // construnct_json();
}
