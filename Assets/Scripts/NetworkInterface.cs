using UnityEngine;
using UnityEngine.Networking;
using System.Collections;

public class NetworkInterface:MonoBehaviour {

	public int maxConnections = 100;
	public string ipaddress = "127.0.0.1"; //"73.235.106.150";
	public int socketPort = 1337;
	int myUnreliableChannelId;
	int connectionId;
	int hostId;
	byte packetsSent = 0x00;
	byte error;

	// Use this for initialization
	void Start(){
		NetworkTransport.Init();
		ConnectionConfig config = new ConnectionConfig();
		myUnreliableChannelId = config.AddChannel(QosType.Unreliable);
		HostTopology topology = new HostTopology(config, maxConnections);
		hostId = NetworkTransport.AddHost(topology, socketPort);
		connectionId = NetworkTransport.Connect(hostId, ipaddress, 1337, 0, out error);
		CheckErrorCode();
	}

	// Update is called once per frame
	void Update(){
		int recHostId; 
	    int newConnectionId; 
	    int newChannelId; 
	    byte[] recBuffer = new byte[1024]; 
	    int bufferSize = 1024;
	    int dataSize;
	    NetworkEventType recData = NetworkTransport.Receive(out recHostId, out newConnectionId, out newChannelId, recBuffer, bufferSize, out dataSize, out error);
	    switch (recData)
	    {
	        case NetworkEventType.Nothing:         //1
	            break;
	        case NetworkEventType.ConnectEvent:    //2
	        	Debug.Log("Connection packet came in!");
	            break;
	        case NetworkEventType.DataEvent:       //3
	            break;
	        case NetworkEventType.DisconnectEvent: //4
	            break;
	    }
	    Debug.Log(recBuffer[0]);
		//Debug.Log("Creating packet number: " + packetsSent);
		byte[] message = { 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, packetsSent, 0x00, 0x00, 0x00, 0x00};
		packetsSent++;
		NetworkTransport.Send(hostId, connectionId, myUnreliableChannelId, message, 12, out error);
		CheckErrorCode();
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
}
