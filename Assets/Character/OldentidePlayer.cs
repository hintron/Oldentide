using UnityEngine;
using System.Collections;

public class OldentidePlayer : OldentideCharacter MonoBehaviour {

	// Character Description
	private string account;
	private string profession;
	private int dp;

	// Martial Skills
	private int axe;
	private int dagger;
	private int unarmed;
	private int hammer;
	private int polearm;
	private int spear;
	private int staff;
	private int sword;
	private int archery;
	private int crossbow;
	private int sling;
	private int thrown;
	private int armor;
	private int dualWeapon;
	private int shield;
	
	// Spell Skills
	private int bardic;
	private int conjuring;
	private int druidic;
	private int illusion;
	private int necromancy;
	private int sorcery;
	private int shamanic;
	private int summoning;
	private int spellcraft;
	private int focus;

	// Crafting and Gathering Skills
	private int armorsmithing;
	private int tailoring;
	private int fletching;
	private int weaponsmithing;
	private int alchemy;
	private int lapidary;
	private int calligraphy;
	private int enchanting;
	private int herbalism;
	private int hunting;
	private int mining;

	// Generic Skills
	private int bargaining;
	private int camping;
	private int firstAid;
	private int lore;
	private int pickLocks;
	private int scouting;
	private int search;
	private int stealth;
	private int traps;

	// Language Skills
	private int aeolandis;
	private int hieroform;
	private int highGundis;
	private int oldPraxic;
	private int praxic;
	private int runic;

	// Full Constructor
	public OldentidePlayer ( string account, string profession, string session, int axe,
							 int dagger, int unarmed, int hammer, int polearm, int spear,
							 int staff, int sword, int archery, int crossbow, int sling,
							 int thrown, int armor, int dualWeapon, int shield, int bardic,
							 int conjuring, int druidic, int illusion, int necromancy,
							 int sorcery, int shamanic, int summoning, int spellcraft,
							 int focus, int armorsmithing, int tailoring, int fletching,
							 int weaponsmithing, int alchemy, int lapidary, int calligraphy,
							 int enchanting, int herbalism, int hunting, int mining,
							 int bargaining, int camping, int firstAid, int lore, int pickLocks,
							 int scouting, int search, int stealth, int traps, int aeolandis,
							 int hieroform, int highGundis, int oldPraxic, int praxic, int runic ) 
	   :OldentideCharacter ( string name, string lastname, string guild, string race,
	   						 string gender, string face, string skin, string zone, int id, 
	   						 int level, int dp, int hp, int maxHp, int bp, int maxBp, int mp,
	   						 int maxMp, int ep, int maxEp, int strength, int constitution, 
	   						 int intelligence, int dexterity, float weight, float x, float y,
	   						 float z, float pitch, float yaw ) {
		SetAccount(account);
	    SetProfession(profession);
	    SetSession(session);
	    SetAxe(axe);
	    SetDagger(dagger);
	    SetUnarmed(unarmed);
	    SetHammer(hammer);
	    SetPolearm(polearm);
	    SetSpear(spear);
	    SetStaff(staff);
	    SetSword(sword);
	    SetArchery(archery);
	    SetCrossbow(crossbow);
	    SetSling(sling);
	    SetThrown(thrown);
	    SetArmor(armor);
	    SetDualWeapon(dualWeapon);
	    SetShield(shield);
	    SetBardic(bardic);
	    SetConjuring(conjuring);
	    SetDruidic(druidic);
	    SetIllusion(illusion);
	    SetNecromancy(necromancy);
	    SetSorcery(sorcery);
	    SetShamanic(shamanic);
	    SetSummoning(summoning);
	    SetSpellcraft(spellcraft);
	    SetFocus(focus);
	    SetArmorsmithing(armorsmithing);
	    SetTailoring(tailoring);
	    SetFletching(fletching);
	    SetWeaponsmith(weaponsmithing);
	    SetAlchemy(alchemy);
	    SetLapidary(lapidary);
	    SetCalligraphy(calligraphy);
	    SetEnchanting(enchanting);
	    SetHerbalism(herbalism);
	    SetHunting(hunting);
	    SetMining(mining);
	    SetBargaining(bargaining);
	    SetCamping(camping);
	    SetFirstAid(firstAid);
	    SetLore(lore);
	    SetPickLocks(pickLocks);
	    SetScouting(scouting);
	    SetSearch(search);
	    SetStealth(stealth);
	    SetTraps(traps);
	    SetAeolandis(aeolandis);
	    SetHieroform(hieroform);
	    SetHighGundis(highGundis);
	    SetOldPraxic(oldPraxic);
	    SetPraxic(praxic);
	    SetRunic(runic);
	}

	// Player Creation Constructor
	public OldentidePlayer ( string name, string lastname, string account, string profession,
							 string race, string gender, string face, string skin ) {

	}

	public void Start () {

	}

	public void Update () {

	}

	// Getters

	public string GetAccount() {
	    return account;
	}

	public string GetProfession() {
	    return profession;
	}

	public string GetSession() {
		return session;
	}

	public int GetDp() {
	    return dp;
	}

	public int GetSession() {
	    return session;
	}

	public int GetAxe() {
	    return axe;
	}

	public int GetDagger() {
	    return dagger;
	}

	public int GetUnarmed() {
	    return unarmed;
	}

	public int GetHammer() {
	    return hammer;
	}

	public int GetPolearm() {
	    return polearm;
	}

	public int GetSpear() {
	    return spear;
	}

	public int GetStaff() {
	    return staff;
	}

	public int GetSword() {
	    return sword;
	}

	public int GetArchery() {
	    return archery;
	}

	public int GetCrossbow() {
	    return crossbow;
	}

	public int GetSling() {
	    return sling;
	}

	public int GetThrown() {
	    return thrown;
	}

	public int GetArmor() {
	    return armor;
	}

	public int GetDualWeapon() {
	    return dualWeapon;
	}

	public int GetShield() {
	    return shield;
	}

	public int GetBardic() {
	    return bardic;
	}

	public int GetConjuring() {
	    return conjuring;
	}

	public int GetDruidic() {
	    return druidic;
	}

	public int GetIllusion() {
	    return illusion;
	}

	public int GetNecromancy() {
	    return necromancy;
	}

	public int GetSorcery() {
	    return sorcery;
	}

	public int GetShamanic() {
	    return shamanic;
	}

	public int GetSummoning() {
	    return summoning;
	}

	public int GetSpellcraft() {
	    return spellcraft;
	}

	public int GetFocus() {
	    return focus;
	}

	public int GetArmorsmithing() {
	    return armorsmithing;
	}

	public int GetTailoring() {
	    return tailoring;
	}

	public int GetFletching() {
	    return fletching;
	}

	public int GetWeaponsmithing() {
	    return weaponsmithing;
	}

	public int GetAlchemy() {
	    return alchemy;
	}

	public int GetLapidary() {
	    return lapidary;
	}

	public int GetCalligraphy() {
	    return calligraphy;
	}

	public int GetEnchanting() {
	    return enchanting;
	}

	public int GetHerbalism() {
	    return herbalism;
	}

	public int GetHunting() {
	    return hunting;
	}

	public int GetMining() {
	    return mining;
	}

	public int GetBargaining() {
	    return bargaining;
	}

	public int GetCamping() {
	    return camping;
	}

	public int GetFirstAid() {
	    return firstAid;
	}

	public int GetLore() {
	    return lore;
	}

	public int GetPickLocks() {
	    return pickLocks;
	}

	public int GetScouting() {
	    return scouting;
	}

	public int GetSearch() {
	    return search;
	}

	public int GetStealth() {
	    return stealth;
	}

	public int GetTraps() {
	    return traps;
	}

	public int GetAeolandis() {
	    return aeolandis;
	}

	public int GetHieroform() {
	    return hieroform;
	}

	public int GetHighGundis() {
	    return highGundis;
	}

	public int GetOldPraxic() {
	    return oldPraxic;
	}

	public int GetPraxic() {
	    return praxic;
	}

	public int GetRunic() {
	    return runic;
	}

	// Setters

	public void SetAccount(string account) {
	    this.account = account;
	}

	public void SetProfession(string profession) {
	    this.profession = profession;
	}

	public void SetSession(string session) {
		this.session = session;
	}

	public void SetDp(int dp) {
	    this.dp = dp;
	}

	public void SetAxe(int axe) {
	    this.axe = axe;
	}

	public void SetDagger(int dagger) {
	    this.dagger = dagger;
	}

	public void SetUnarmed(int unarmed) {
	    this.unarmed = unarmed;
	}

	public void SetHammer(int hammer) {
	    this.hammer = hammer;
	}

	public void SetPolearm(int polearm) {
	    this.polearm = polearm;
	}

	public void SetSpear(int spear) {
	    this.spear = spear;
	}

	public void SetStaff(int staff) {
	    this.staff = staff;
	}

	public void SetSword(int sword) {
	    this.sword = sword;
	}

	public void SetArchery(int archery) {
	    this.archery = archery;
	}

	public void SetCrossbow(int crossbow) {
	    this.crossbow = crossbow;
	}

	public void SetSling(int sling) {
	    this.sling = sling;
	}

	public void SetThrown(int thrown) {
	    this.thrown = thrown;
	}

	public void SetArmor(int armor) {
	    this.armor = armor;
	}

	public void SetDualWeapon(int dualWeapon) {
	    this.dualWeapon = dualWeapon;
	}

	public void SetShield(int shield) {
	    this.shield = shield;
	}

	public void SetBardic(int bardic) {
	    this.bardic = bardic;
	}

	public void SetConjuring(int conjuring) {
	    this.conjuring = conjuring;
	}

	public void SetDruidic(int druidic) {
	    this.druidic = druidic;
	}

	public void SetIllusion(int illusion) {
	    this.illusion = illusion;
	}

	public void SetNecromancy(int necromancy) {
	    this.necromancy = necromancy;
	}

	public void SetSorcery(int sorcery) {
	    this.sorcery = sorcery;
	}

	public void SetShamanic(int shamanic) {
	    this.shamanic = shamanic;
	}

	public void SetSummoning(int summoning) {
	    this.summoning = summoning;
	}

	public void SetSpellcraft(int spellcraft) {
	    this.spellcraft = spellcraft;
	}

	public void SetFocus(int focus) {
	    this.focus = focus;
	}

	public void SetArmorsmithing(int armorsmithing) {
	    this.armorsmithing = armorsmithing;
	}

	public void SetTailoring(int tailoring) {
	    this.tailoring = tailoring;
	}

	public void SetFletching(int fletching) {
	    this.fletching = fletching;
	}

	public void SetWeaponsmith(int weaponsmithing) {
	    this.weaponsmithing = weaponsmithing;
	}

	public void SetAlchemy(int alchemy) {
	    this.alchemy = alchemy;
	}

	public void SetLapidary(int lapidary) {
	    this.lapidary = lapidary;
	}

	public void SetCalligraphy(int calligraphy) {
	    this.calligraphy = calligraphy;
	}

	public void SetEnchanting(int enchanting) {
	    this.enchanting = enchanting;
	}

	public void SetHerbalism(int herbalism) {
	    this.herbalism = herbalism;
	}

	public void SetHunting(int hunting) {
	    this.hunting = hunting;
	}

	public void SetMining(int mining) {
	    this.mining = mining;
	}

	public void SetBargaining(int bargaining) {
	    this.bargaining = bargaining;
	}

	public void SetCamping(int camping) {
	    this.camping = camping;
	}

	public void SetFirstAid(int firstAid) {
	    this.firstAid = firstAid;
	}

	public void SetLore(int lore) {
	    this.lore = lore;
	}

	public void SetPickLocks(int pickLocks) {
	    this.pickLocks = pickLocks;
	}

	public void SetScouting(int scouting) {
	    this.scouting = scouting;
	}

	public void SetSearch(int search) {
	    this.search = search;
	}

	public void SetStealth(int stealth) {
	    this.stealth = stealth;
	}

	public void SetTraps(int traps) {
	    this.traps = traps;
	}

	public void SetAeolandis(int aeolandis) {
	    this.aeolandis = aeolandis;
	}

	public void SetHieroform(int hieroform) {
	    this.hieroform = hieroform;
	}

	public void SetHighGundis(int highGundis) {
	    this.highGundis = highGundis;
	}

	public void SetOldPraxic(int oldPraxic) {
	    this.oldPraxic = oldPraxic;
	}

	public void SetPraxic(int praxic) {
	    this.praxic = praxic;
	}

	public void SetRunic(int runic) {
	    this.runic = runic;
	}
}