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
	    GETSALT = 5,
	    CREATEACCOUNT = 6,
	    LOGIN = 7,
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

/*
	public unsafe struct PACKET_ACK {
	    PTYPE packetType;
	    int packetId;
	    int sessionId;
	};

	public unsafe struct PACKET_CONNECT {
	    PTYPE packetType;
	    int packetId;
	    int sessionId;
	};

	public unsafe struct PACKET_DISCONNECT {
	    PTYPE packetType;
	    int packetId;
	    int sessionId;
	};

	public unsafe struct PACKET_GETSALT {
	    PTYPE packetType;
	    int packetId;
	    int sessionId;
	    fixed byte account[30];
	    // 512-bit key -> 64 bytes -> 2 bytes per byte for hex -> 128 + 1 null = 129
	    fixed byte saltStringHex[129];
	};

	public unsafe struct PACKET_CREATEACCOUNT {
	    PTYPE packetType;
	    int packetId;
	    int sessionId;
	    fixed byte account[30];
	    // 512-bit key -> 64 bytes -> 2 bytes per byte for hex -> 128 + 1 null = 129
	    fixed byte saltStringHex[129];
	    fixed byte keyStringHex[129];
	};

	public unsafe struct PACKET_LOGIN {
	    PTYPE packetType;
	    int packetId;
	    int sessionId;
	    fixed byte account[30];
	    // 512-bit key -> 64 bytes -> 2 bytes per byte for hex -> 128 + 1 null = 129
	    fixed byte keyStringHex[129];
	};

	public unsafe struct PACKET_LISTCHARACTERS {
	    PTYPE packetType;
	    int packetId;
	    int sessionId;
	    fixed byte byteacter0[25];
	    fixed byte byteacter1[25];
	    fixed byte byteacter2[25];
	    fixed byte byteacter3[25];
	    fixed byte byteacter4[25];
	    fixed byte byteacter5[25];
	    fixed byte byteacter6[25];
	    fixed byte byteacter7[25];
	    fixed byte byteacter8[25];
	    fixed byte byteacter9[25];
	};

	public unsafe struct PACKET_SELECTCHARACTER {
	    PTYPE packetType;
	    int packetId;
	    int sessionId;
	    fixed byte byteacter[25];
	};

	public unsafe struct PACKET_DELETECHARACTER {
	    PTYPE packetType;
	    int packetId;
	    int sessionId;
	    fixed byte byteacter[25];
	};

	public unsafe struct PACKET_CREATECHARACTER {
	    PTYPE packetType;
	    int packetId;
	    int sessionId;
	    fixed byte firstName[25];
	    fixed byte lastName[25];
	    fixed byte race[25];
	    fixed byte gender[25];
	    fixed byte profession[25];
	    int strength;
	    int constitution;
	    int intelligence;
	    int dexterity;
	    int axe;
	    int dagger;
	    int unarmed;
	    int hammer;
	    int polearm;
	    int spear;
	    int staff;
	    int sword;
	    int archery;
	    int crossbow;
	    int sling;
	    int thrown;
	    int armor;
	    int dualWeapon;
	    int shield;
	    int bardic;
	    int conjuring;
	    int druidic;
	    int illusion;
	    int necromancy;
	    int sorcery;
	    int shamanic;
	    int spellcraft;
	    int summoning;
	    int focus;
	    int armorsmithing;
	    int tailoring;
	    int fletching;
	    int weaponsmithing;
	    int alchemy;
	    int lapidary;
	    int calligraphy;
	    int enchanting;
	    int herbalism;
	    int hunting;
	    int mining;
	    int bargaining;
	    int camping;
	    int firstAid;
	    int lore;
	    int pickLocks;
	    int scouting;
	    int search;
	    int stealth;
	    int traps;
	    int aeolandis;
	    int hieroform;
	    int highGundis;
	    int oldPraxic;
	    int praxic;
	    int runic;
	};

	public unsafe struct PACKET_INITIALIZEGAME {
	    PTYPE packetType;
	    int packetId;
	    int sessionId;
	};

	public unsafe struct PACKET_UPDATEPC {
	    PTYPE packetType;
	    int packetId;
	    int sessionId;
	    fixed byte firstName[25];
	    fixed byte lastName[25];
	    fixed byte race[25];
	    fixed byte gender[25];
	    fixed byte profession[25];
	    int level;
	    int hp;
	    int bp;
	    int mp;
	    int ep;
	    int x;
	    int y;
	    int z;
	    float direction;
	};

	public unsafe struct PACKET_UPDATENPC {
	    PTYPE packetType;
	    int packetId;
	    int sessionId;
	};

	public unsafe struct PACKET_SENDPLAYERCOMMAND {
	    PTYPE packetType;
	    int packetId;
	    int sessionId;
	    fixed byte command[500];
	};

	public unsafe struct PACKET_SENDSERVERCOMMAND {
	    PTYPE packetType;
	    int packetId;
	    int sessionId;
	    fixed byte command[500];
	};

	public unsafe struct PACKET_SENDPLAYERACTION {
	    PTYPE packetType;
	    int packetId;
	    int sessionId;
	};

	public unsafe struct PACKET_SENDSERVERACTION {
	    PTYPE packetType;
	    int packetId;
	    int sessionId;
	};
*/

	// mark MessagePackObjectAttribute
	[MessagePackObject]
	public struct PACKET_UNITY {
	    [Key(0)]
		public PTYPE packetType;
	    [Key(1)]
		public int data1;
	    [Key(2)]
		public int data2;
	    [Key(3)]
		public int data3;
	    [Key(4)]
		public int data4;
	    [Key(5)]
		public int data5;
	};



}