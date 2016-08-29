using UnityEngine;
using UnityEngine.Networking;
using System.Collections;
using System;
using System.IO;
using System.Text;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization;
using Oldentide.Networking;

public class NetworkInterface : MonoBehaviour {

	public int maxConnections = 100;
	public string ipaddress = "127.0.0.1"; //"73.235.106.150";
	public int socketPort = 1337;
	public byte packetsSent = 0x00;
	public byte error;
	int myUnreliableChannelId;
	int connectionId;
	int hostId;

	// Use this for initialization
	void Start(){
		NetworkTransport.Init();
		ConnectionConfig config = new ConnectionConfig();
		myUnreliableChannelId = config.AddChannel(QosType.Unreliable);
		HostTopology topology = new HostTopology(config, maxConnections);
		hostId = NetworkTransport.AddHost(topology, socketPort);
		Debug.Log("Pre connect connectionId: " + connectionId);
		connectionId = NetworkTransport.Connect(hostId, ipaddress, 1337, 0, out error);
		Debug.Log("Post connect connectionId: " + connectionId);
		CheckErrorCode();
	}

	// Update is called once per frame
	void Update(){
		//sendPacket();
		receivePacket();
	}

	// Update log file with error code...
	void CheckErrorCode(){
		switch(error){
			case 0:
				Debug.Log("Error code says OK");
				break;
			case 1:
				Debug.Log("Error code says WrongHost");
				break;
			case 2:
				Debug.Log("Error code says WrongConnection");
				break;
			case 3:
				Debug.Log("Error code says WrongChannel");
				break;
			case 4:
				Debug.Log("Error code says NoResources");
				break;
			case 5:
				Debug.Log("Error code says BadMessage");
				break;
			case 6:
				Debug.Log("Error code says Timeout");
				break;
			case 7:
				Debug.Log("Error code says MessageToLong");
				break;
			case 8:
				Debug.Log("Error code says WrongOperation");
				break;
			case 9:
				Debug.Log("Error code says VersionMismatch");
				break;
			case 10:
				Debug.Log("Error code says CRCMismatch");
				break;
			case 11:
				Debug.Log("Error code says DNSFailure");
				break;
		}
	}

	/*void sendPacket(){
		//Debug.Log("Creating packet number: " + packetsSent);
		byte[] payload = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
		Packet toSend = new Packet(PTYPE.CONNECT, packetsSent, 0, payload);
		packetsSent++;
		byte[] buffer = new byte[1024];
		Stream stream = new MemoryStream(toSend);
		IFormatter formatter = new BinaryFormatter();
		formatter.Serialize(stream, toSend);
		NetworkTransport.Send(hostId, connectionId, myUnreliableChannelId, buffer, 1024, out error);
		CheckErrorCode();
	}*/

	void receivePacket(){
		int recHostId; 
	    int newConnectionId; 
	    int newChannelId; 
	    byte[] recBuffer = new byte[1024]; 
	    int bufferSize = 1024;
	    int dataSize;
	    /*
	    NetworkEventType recEvent = NetworkTransport.Receive(out recHostId, out newConnectionId, out newChannelId, recBuffer, bufferSize, out dataSize, out error);
	    switch (recEvent)
	    {
	        case NetworkEventType.Nothing:         //1
	        	Debug.Log("A Nothing packet came in!");
	            break;
	        case NetworkEventType.ConnectEvent:    //2
	        	Debug.Log("Connection packet came in!");
	            break;
	        case NetworkEventType.DataEvent:       //3
	            break;
	        case NetworkEventType.DisconnectEvent: //4
	            break;
	        case NetworkEventType.BroadcastEvent: //5
	        	break;
	    }
	    Debug.Log("Recieved Host ID: " + recHostId);
	    Debug.Log("New Connection ID: " + newConnectionId);
	    Debug.Log("New Channel ID: " + newChannelId);
	    Debug.Log("Rec Buffer contents:");
	    for (int i = 0; i < 10; i++){
	    	Debug.Log(recBuffer[i]);
	    }
	    Debug.Log("Data size: " + dataSize);
	    */
	}
}
