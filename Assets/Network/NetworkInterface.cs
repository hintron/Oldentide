using UnityEngine;
using Oldentide.Networking;
using System;
using System.IO;
using System.Collections;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using MessagePack;

public class NetworkInterface : MonoBehaviour {

	public string serverIp = "goblin.oldentide.com";
	public int serverPort = 1337;
	IPEndPoint serverEndPoint;
	IPEndPoint clientEndPoint;
	Socket clientSocket;


	int packetNumber = 1;
	int session = 0;


	// This is the number of bytes that the oldentide header is
	const int HEADER_SIZE = 3;
	const int PACKET_MAX_SIZE = 512;

	// Use this for initialization
	void Start() {
		// Set up Server End Point for sending packets.
		IPHostEntry serverHostEntry = Dns.GetHostEntry(serverIp);
		IPAddress serverIpAddress = serverHostEntry.AddressList[0];
		serverEndPoint = new IPEndPoint(serverIpAddress, serverPort);
		Debug.Log("Server IPEndPoint: " + serverEndPoint.ToString());
		// Set up Client End Point for receiving packets.
		IPHostEntry clientHostEntry = Dns.GetHostEntry(Dns.GetHostName());
		IPAddress clientIpAddress = IPAddress.Any;
		foreach (IPAddress ip in clientHostEntry.AddressList) {
			if (ip.AddressFamily == AddressFamily.InterNetwork) {
				clientIpAddress = ip;
			}
		}
		clientEndPoint = new IPEndPoint(clientIpAddress, serverPort);
		Debug.Log("Client IPEndPoint: " + clientEndPoint.ToString());
		// Create socket for client and bind to Client End Point (Ip/Port).
		clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
		try {
			clientSocket.Bind(clientEndPoint);
		}
		catch (Exception e) {
			Debug.Log("Winsock error: " + e.ToString());
		}
	}



	// For the MessagePack library, using:
	// https://github.com/neuecc/MessagePack-CSharp
	// instead of:
	// https://github.com/msgpack/msgpack-cli

	// To install, simply download the Unity zip from the releases page:
	// https://github.com/neuecc/MessagePack-CSharp/releases
	// Unzip it into a folder NOT under Oldentide/
	// (don't want unity automatically ingesting the files just yet)
	// In the Unity editor, click Assets -> Import Package
	// Select the MessagePack .unitypackage file and click import.
	// e.g. ...\MessagePack.Unity.1.2.0\MessagePack.Unity.1.2.0.unitypackage"
	// Now all the MessagePack files are loaded into the project!
	// To use it in code, put "using MessagePack" at the top of any C# files


	// Update is called once per frame
	void Update() {
		if(Input.GetKeyDown(KeyCode.M)){
			StartCoroutine(ConnectToServer());
			Debug.Log("M press!");
		}
		if(Input.GetKeyDown(KeyCode.L)){
			StartCoroutine(ListCharacters());
			Debug.Log("L press!");
		}
	}


	// TODO: We need a way of canceling pending callbacks that are waiting for a packet,
	// or else the stale callbacks will consume the new return packets that were meant for a
	// newer request.

	IEnumerator ConnectToServer(){
		Debug.Log("Sending a single CONNECT packet via message pack!!");

		PacketConnect pp = new PacketConnect();
		pp.sessionId = session;
		pp.packetId = packetNumber;
		packetNumber++;

		byte [] msgpackData = MessagePackSerializer.Serialize(pp);
		// Synchronously send, since it's UDP
		SendDataTo(clientSocket, serverEndPoint, Oldentide.Networking.PTYPE.CONNECT, msgpackData);

		Debug.Log("Sent CONNECT packet! Receiving packet...");

		// Wait for the response
		ReceiveDataFrom(delegate(byte[] msgpackDataReceived, Oldentide.Networking.PTYPE packetType) {
			Debug.Log("Server responded with packet " + packetType);

			var data = MessagePackSerializer.Deserialize<PacketConnect>(msgpackDataReceived);
			Debug.Log("Connect packet response! sessionId: " + data.sessionId + " ; packetId: " + data.packetId);

			if(data.sessionId != session){
				Debug.Log("Setting new session to " + data.sessionId);
				session = data.sessionId;
			}
			else {
				Debug.Log("Session is already set to " + session);
			}
		});

		yield return null;
	}


	IEnumerator ListCharacters(){
		Debug.Log("ListCharacters()!");
		PacketListcharacters pp = new PacketListcharacters();
		pp.sessionId = session;
		pp.packetId = packetNumber;
		// Set to empty array, NOT null. This makes a difference in messagepack
		pp.characterArray = new string [0];
		packetNumber++;

		byte [] sendMsgpackData = MessagePackSerializer.Serialize(pp);
		SendDataTo(clientSocket, serverEndPoint, Oldentide.Networking.PTYPE.LISTCHARACTERS, sendMsgpackData);

		// Wait for the response
		ReceiveDataFrom(delegate(byte[] msgpackDataReceived, Oldentide.Networking.PTYPE packetType) {
			if(packetType == Oldentide.Networking.PTYPE.ERROR){
				var errData = MessagePackSerializer.Deserialize<PacketError>(msgpackDataReceived);
				Debug.Log("ERROR: " + errData.errorMsg);
				return;
			}
			var data = MessagePackSerializer.Deserialize<PacketListcharacters>(msgpackDataReceived);
			if(data.sessionId != session){
				Debug.Log("Invalid session! Ignoring packet " + packetType);
				return;
			}
			Debug.Log("ListCharacter response! sessionId: " + data.sessionId + " ; packetId: " + data.packetId);

			// TODO: Print out the character list
			foreach (string element in data.characterArray) {
				Debug.Log(element);
        	}
		});


		yield return null;
	}


	////
	/// Util functions
	//

	// Everything below here is analogous to the Utils C++ class in Server - wrappers to
	// the (UDP) socket functions that will be used multiple times

	// Gameplan: Use a delegate function, so the user can pass in their own callback function
	// That way, we can hide the complexities of the other stuff

	// How to use delegates and async callbacks:
	// http://stackoverflow.com/questions/2082615/pass-method-as-parameter-using-c-sharp
	// http://stackoverflow.com/questions/6866347/lambda-anonymous-function-as-a-parameter
	// https://docs.microsoft.com/en-us/dotnet/articles/csharp/programming-guide/statements-expressions-operators/anonymous-functions

	// Create a class to pass data to ReceiveDataFromCallback
	public class CallbackParams{
		public byte[] buffer;
		public Action<byte[], Oldentide.Networking.PTYPE> callback;
		// Note: Action<...> is a no-return delegate; Func<..., retType> has a return type
		// public Func<string, int> callback;
	}

	// Wrapper function for BeginReceiveFrom() that deals with
	// The callback params include the msgpack data and the packetType
	void ReceiveDataFrom(Action<byte[], Oldentide.Networking.PTYPE> callback) {
		// byte[] packetToReceive = new byte[PACKET_MAX_SIZE];
		IPEndPoint sender = new IPEndPoint(IPAddress.Any, 0);
		EndPoint senderRemote = (EndPoint)sender;

		// Use BeginReceiveFrom and EndReceiveFrom:
		// https://msdn.microsoft.com/en-us/library/system.net.sockets.socket.beginreceivefrom(v=vs.110).aspx
		// http://stackoverflow.com/questions/7860398/c-sharp-stateobject-class-location

		CallbackParams so2 = new CallbackParams();
		so2.buffer = new byte[PACKET_MAX_SIZE];
		so2.callback = callback;
		clientSocket.BeginReceiveFrom(so2.buffer, 0, PACKET_MAX_SIZE, 0, ref senderRemote, new AsyncCallback(ReceiveDataFromCallback), so2);
	}

	void ReceiveDataFromCallback(IAsyncResult result){
		// Get the params passed to this callback
		CallbackParams so2 = (CallbackParams) result.AsyncState;

		// // ???? I'm not quite sure why EndReceiveFrom() is even necessary
		// // It seems to work without it just fine
		// // see https://msdn.microsoft.com/en-us/library/system.net.sockets.socket.endreceivefrom(v=vs.110).aspx
		// IPEndPoint sender = new IPEndPoint(IPAddress.Any, 0);
		// EndPoint senderRemote = (EndPoint)sender;
		// // Block and wait for a packet to be put in so2.buffer
		// int read = clientSocket.EndReceiveFrom(result, ref senderRemote);
		// Debug.Log("Got packet, read " + read + " bytes");

		// Get the packet type
		Oldentide.Networking.PTYPE packetType = (Oldentide.Networking.PTYPE) so2.buffer[0];
		// Get the length of the msgpack data
		ushort msgpackLength = BitConverter.ToUInt16(so2.buffer, 1);
		// Copy the msgpack data into the packet
		byte[] data = new byte[msgpackLength];
		Array.Copy(so2.buffer, HEADER_SIZE, data, 0, msgpackLength);

		Debug.Log("Receiving msgpack data: ");
		PrintHexString(data);

		// Return execution back to the original caller, passing back the data
		so2.callback(data, packetType);
	}

	// Use the following to prove that a callback can block and Unity still works
	// System.Threading.Thread.Sleep(10000);

	void SendDataTo(Socket clientSocket, IPEndPoint serverEndPoint, Oldentide.Networking.PTYPE packetType, byte [] msgpackData){
		byte[] packetToSend = new byte[msgpackData.Length + HEADER_SIZE];

		// Prepend header data
		packetToSend[0] = (byte) packetType;
		// Convert msgpack length to a byte array
		byte[] msgpackLength = BitConverter.GetBytes(msgpackData.Length);
		// Copy the 2 bytes of the msgpack length into the packet at location 1
		Array.Copy(msgpackLength, 0, packetToSend, 1, 2);
		// Copy the msgpack data into the packet
		Array.Copy(msgpackData, 0, packetToSend, HEADER_SIZE, msgpackData.Length);

		Debug.Log("Sending packet data: ");
		PrintHexString(packetToSend);
		clientSocket.SendTo(packetToSend, serverEndPoint);
	}

	public void PrintHexString(byte [] bytearray){
		string hexstring = "0x";
		int len = bytearray.Length;
		for (int i = 0; i < len; i++) {
			hexstring += String.Format("{0:X2}", bytearray[i]);
		}
		Debug.Log(hexstring);
	}

}