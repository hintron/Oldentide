﻿using UnityEngine;
using Oldentide.Networking;
using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;

public class NetworkInterface : MonoBehaviour {

	public string serverIp = "goblin.oldentide.com";
	public int serverPort = 1337;
	IPEndPoint serverEndPoint;
	IPEndPoint clientEndPoint;
	Socket clientSocket;

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

	// Update is called once per frame
	void Update() {

		if(Input.GetKeyDown(KeyCode.S)){
			Debug.Log("Sending a single packet!");
			Debug.Log("Key Code:" + KeyCode.S);
			PACKET_UNITY pp;
			pp.packetType = Oldentide.Networking.PTYPE.UNITY;
			pp.data1 = 0xde;
			pp.data2 = 0xad;
			pp.data3 = 0xbe;
			pp.data4 = 0xef;
			pp.data5 = 255;
			byte[] p = StructureToByteArray(pp);
			//Packet p = new Packet(Oldentide.Networking.PTYPE.UNITY, 15, 25);
			//byte[] toSend = new byte[] {0x12, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13};
			clientSocket.SendTo(p, serverEndPoint);
			Debug.Log("Data sent: " + p.ToString());
			/*byte[] toReceive = new byte[20];
			IPEndPoint sender = new IPEndPoint(IPAddress.Any, 0);
	    	EndPoint senderRemote = (EndPoint)sender;
			clientSocket.ReceiveFrom(toReceive, ref senderRemote);
			int i = 0;
			foreach (byte next in toReceive) {
				Debug.Log("Data received @[" + i + "]: " + next);
				i++;
			}*/
		}
	}

	public byte [] StructureToByteArray(object obj){
    	int len = Marshal.SizeOf(obj);
    	byte [] arr = new byte[len];
    	IntPtr ptr = Marshal.AllocHGlobal(len);
    	Marshal.StructureToPtr(obj, ptr, true);
    	Marshal.Copy(ptr, arr, 0, len);
    	Marshal.FreeHGlobal(ptr);
    	return arr;
	}

	public void ByteArrayToStructure(byte [] bytearray, ref object obj){
    	int len = Marshal.SizeOf(obj);
		IntPtr i = Marshal.AllocHGlobal(len);
    	Marshal.Copy(bytearray,0, i,len);
    	obj = Marshal.PtrToStructure(i, obj.GetType());
    	Marshal.FreeHGlobal(i);
	}

}