using System;
using System.Collections.Generic;

namespace Oldentide.Networking {

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

	public class Packet {
		// Data members:
		public PTYPE packetType;
		public int packetId;
		public int sessionId;
		public char[] dummy;
		public char[] account;
		public char[] saltStringHex;
		public char[] keyStringHex;
		public char[] character0;
		public char[] character1;
		public char[] character2;
		public char[] character3;
		public char[] character4;
		public char[] character5;
		public char[] character6;
		public char[] character7;
		public char[] character8;
		public char[] character9;
		public char[] character;
		public char[] firstName;
	    public char[] lastName;
	    public char[] race;
	    public char[] gender;
	    public char[] profession;
	    public int strength;
	    public int constitution;
	    public int intelligence;
	    public int dexterity;
	    public int axe;
	    public int dagger;
	    public int unarmed;
	    public int hammer;
	    public int polearm;
	    public int spear;
	    public int staff;
	    public int sword;
	    public int archery;
	    public int crossbow;
	    public int sling;
	    public int thrown;
	    public int armor;
	    public int dualWeapon;
	    public int shield;
	    public int bardic;
	    public int conjuring;
	    public int druidic;
	    public int illusion;
	    public int necromancy;
	    public int sorcery;
	    public int shamanic;
	    public int spellcraft;
	    public int summoning;
	    public int focus;
	    public int armorsmithing;
	    public int tailoring;
	    public int fletching;
	    public int weaponsmithing;
	    public int alchemy;
	    public int lapidary;
	    public int calligraphy;
	    public int enchanting;
	    public int herbalism;
	    public int hunting;
	    public int mining;
	    public int bargaining;
	    public int camping;
	    public int firstAid;
	    public int lore;
	    public int pickLocks;
	    public int scouting;
	    public int search;
	    public int stealth;
	    public int traps;
	    public int aeolandis;
	    public int hieroform;
	    public int highGundis;
	    public int oldPraxic;
	    public int praxic;
	    public int runic;
	    public int level;
	    public int hp;
	    public int bp;
	    public int mp;
	    public int ep;
	    public int x;
	    public int y;
	    public int z;
	    public float direction;
	    public char[] command;
	    public char[] message;
	    public int globalMessageNumber;
	    public int data1;
	    public int data2;
	    public int data3;
	    public int data4;
	    public int data5;
		// Constructors:
		public Packet(PTYPE p, int pi, int si) {
			packetType = p;
			packetId = pi;
			sessionId = si;
		}
		// Methods:
		public byte[] Serialize() {
			byte[] sPacket;
			switch(packetType) {
				case Oldentide.Networking.PTYPE.GENERIC:
					List<byte> preFormatter = new List<byte>();
					byte[] bytes = BitConverter.GetBytes((int)packetType);
					foreach (byte b in bytes) {
						preFormatter.Add(b);	
					}
					bytes = BitConverter.GetBytes(packetId);
					foreach (byte b in bytes) {
						preFormatter.Add(b);	
					}
					bytes = BitConverter.GetBytes(sessionId);
					foreach (byte b in bytes) {
						preFormatter.Add(b);	
					}
					sPacket = new byte[612];
					int i = 0;
					foreach (byte b in preFormatter.ToArray()) {
						sPacket[i] = b;
					}
					break;
				case Oldentide.Networking.PTYPE.ACK:
					sPacket = new byte[12];
					break;
				case Oldentide.Networking.PTYPE.CONNECT:
					sPacket = new byte[12];
					break;
				case Oldentide.Networking.PTYPE.DISCONNECT:
	   				sPacket = new byte[12];
					break;
				case Oldentide.Networking.PTYPE.GETSALT:
	    			sPacket = new byte[172];
					break;
				case Oldentide.Networking.PTYPE.CREATEACCOUNT:
	    			sPacket = new byte[300];
					break;
				case Oldentide.Networking.PTYPE.LOGIN:
	    			sPacket = new byte[172];
					break;
				case Oldentide.Networking.PTYPE.LISTCHARACTERS:
	    			sPacket = new byte[264];
					break;
				case Oldentide.Networking.PTYPE.SELECTCHARACTER:
	    			sPacket = new byte[40];
					break;
				case Oldentide.Networking.PTYPE.DELETECHARACTER:
	    			sPacket = new byte[40];
					break;
				case Oldentide.Networking.PTYPE.CREATECHARACTER:
	    			sPacket = new byte[360];
					break;
				case Oldentide.Networking.PTYPE.INITIALIZEGAME:
	    			sPacket = new byte[12];
					break;
				case Oldentide.Networking.PTYPE.UPDATEPC:
	    			sPacket = new byte[176];
					break;
				case Oldentide.Networking.PTYPE.UPDATENPC:
	    			sPacket = new byte[12];
					break;
				case Oldentide.Networking.PTYPE.SENDPLAYERCOMMAND:
	    			sPacket = new byte[512];
					break;
				case Oldentide.Networking.PTYPE.SENDPLAYERACTION:
	    			sPacket = new byte[12];
					break;
				case Oldentide.Networking.PTYPE.SENDSERVERACTION:
	    			sPacket = new byte[12];
					break;
				case Oldentide.Networking.PTYPE.MESSAGE:
	    			sPacket = new byte[552];
					break;
				case Oldentide.Networking.PTYPE.GETLATESTMESSAGE:
					sPacket = new byte[24];
					break;
				default:
					sPacket = new byte[12];
					break;
			}
			return sPacket;
		}
	}

}