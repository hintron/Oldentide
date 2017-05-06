using System;
using System.Collections.Generic;
using MessagePack;

namespace Oldentide.Networking {

	public enum PTYPE {
	    // Reserve 0 for null/uninitialized
		GENERIC = 1,
		ACK = 2,
		CONNECT = 3,
		DISCONNECT = 4,
	    ERROR = 5,
	    // CREATEACCOUNT = 6,
	    // LOGIN = 7,
	    LISTCHARACTERS = 8,
	    SELECTCHARACTER = 9,
	    DELETECHARACTER = 10,
	    CREATECHARACTER = 11,
	    INITIALIZEGAME = 12,
	    UPDATEPC = 13,
	    UPDATENPC = 14,
	    SENDPLAYERCOMMAND = 15,
	    SENDSERVERCOMMAND = 16,
	    SENDPLAYERACTION = 17,
	    SENDSERVERACTION = 18,
	    UNITY = 19,
	};

	[MessagePackObject]
	public class PacketAck {
	    [Key(0)]
	    public int packetId;
	    [Key(1)]
	    public int sessionId;
	};

	[MessagePackObject]
	public class PacketConnect {
	    [Key(0)]
	    public int packetId;
	    [Key(1)]
	    public int sessionId;
	};

	[MessagePackObject]
	public class PacketDisconnect {
	    [Key(0)]
	    public int packetId;
	    [Key(1)]
	    public int sessionId;
	};

	[MessagePackObject]
	public class PacketListcharacters {
	    [Key(0)]
	    public int packetId;
	    [Key(1)]
	    public int sessionId;
	    [Key(2)]
	    public string [] characterArray;
	};

	[MessagePackObject]
	public class PacketError {
	    [Key(0)]
	    public int packetId;
	    [Key(1)]
	    public int sessionId;
	    [Key(2)]
	    public string errorMsg;
	    // TODO: Implement error number system
	    // [Key(3)]
	    // public int errorNumber;
	};

	// public class PacketSelectcharacter {
	//     public int packetId;
	//     public int sessionId;
	//     string byteacter;
	// };

	// public class PacketDeletecharacter {
	//     public int packetId;
	//     public int sessionId;
	//     string byteacter;
	// };

	// public class PacketCreatecharacter {
	//     public int packetId;
	//     public int sessionId;
	//     string firstName;
	//     string lastName;
	//     string race;
	//     string gender;
	//     string profession;
	//     // TODO: Create an attributes map -> map<string, int> attributes
	//     int strength;
	//     int constitution;
	//     int intelligence;
	//     int dexterity;
	//     int axe;
	//     int dagger;
	//     int unarmed;
	//     int hammer;
	//     int polearm;
	//     int spear;
	//     int staff;
	//     int sword;
	//     int archery;
	//     int crossbow;
	//     int sling;
	//     int thrown;
	//     int armor;
	//     int dualWeapon;
	//     int shield;
	//     int bardic;
	//     int conjuring;
	//     int druidic;
	//     int illusion;
	//     int necromancy;
	//     int sorcery;
	//     int shamanic;
	//     int spellcraft;
	//     int summoning;
	//     int focus;
	//     int armorsmithing;
	//     int tailoring;
	//     int fletching;
	//     int weaponsmithing;
	//     int alchemy;
	//     int lapidary;
	//     int calligraphy;
	//     int enchanting;
	//     int herbalism;
	//     int hunting;
	//     int mining;
	//     int bargaining;
	//     int camping;
	//     int firstAid;
	//     int lore;
	//     int pickLocks;
	//     int scouting;
	//     int search;
	//     int stealth;
	//     int traps;
	//     int aeolandis;
	//     int hieroform;
	//     int highGundis;
	//     int oldPraxic;
	//     int praxic;
	//     int runic;
	// };

	// public class PacketInitializegame {
	//     public int packetId;
	//     public int sessionId;
	// };

	// public class PacketUpdatepc {
	//     public int packetId;
	//     public int sessionId;
	//     string firstName;
	//     string lastName;
	//     string race;
	//     string gender;
	//     string profession;
	//     int level;
	//     int hp;
	//     int bp;
	//     int mp;
	//     int ep;
	//     int x;
	//     int y;
	//     int z;
	//     float direction;
	// };

	// public class PacketUpdatenpc {
	//     public int packetId;
	//     public int sessionId;
	// };

	// public class PacketSendplayercommand {
	//     public int packetId;
	//     public int sessionId;
	//     string command;
	// };

	// public class PacketSendservercommand {
	//     public int packetId;
	//     public int sessionId;
	//     string command;
	// };

	// public class PacketSendplayeraction {
	//     public int packetId;
	//     public int sessionId;
	// };

	// public class PacketSendserveraction {
	//     public int packetId;
	//     public int sessionId;
	// };

	// mark MessagePackObjectAttribute
	[MessagePackObject]
	public class PacketUnity {
	    [Key(0)]
	    public int packetId;
	    [Key(1)]
	    public int sessionId;
	    [Key(2)]
		public int data1;
	    [Key(3)]
		public int data2;
	    [Key(4)]
		public int data3;
	    [Key(5)]
		public int data4;
	    [Key(6)]
		public int data5;
	};



}