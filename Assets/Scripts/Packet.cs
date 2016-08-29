using System;
using System.IO;
using System.Text;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization;

namespace Oldentide.Networking{

	public enum PTYPE {
		GENERIC,
		ACK,
		CONNECT,
		DISCONNECT,
	    GETSALT,
	    CREATEACCOUNT,
	    LOGIN,
	    LISTCHARACTERS,
	    SELECTCHARACTER,
	    DELETECHARACTER,
	    CREATECHARACTER,
	    INITIALIZEGAME,
	    UPDATEPC,
	    UPDATENPC,
	    SENDPLAYERCOMMAND,
	    SENDPLAYERACTION,
	    SENDSERVERACTION,
	    MESSAGE,
	    GETLATESTMESSAGE,
	}

	[Serializable]
	public class Packet {
		
		public Oldentide.Networking.PTYPE packetType;
		public int packetId;
		public int sessionId;
		public byte[] dummy;
		public Packet(Oldentide.Networking.PTYPE p, int pi, int si, byte[] d){
			packetType = p;
			packetId = pi;
			sessionId = si;
			dummy = d;
		}
	}
}