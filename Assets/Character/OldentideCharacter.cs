using UnityEngine;
using System.Collections;

public class OldentideCharacter : MonoBehaviour {

	// Character Description
	protected string name;
	protected string lastname;
	protected string guild;
	protected string race;
	protected string gender;
	protected string face;
	protected string skin;
	protected string zone;
	protected string head;
	protected string chest;
	protected string arms;
	protected string hands;
	protected string legs;
	protected string feet;
	protected string cloak;
	protected string necklace;
	protected string ringOne;
	protected string ringTwo;
	protected string rightHand;
	protected string leftHand;


	// Character Statistics
	protected int id;
	protected int level;
	protected int hp;
	protected int maxHp;
	protected int bp;
	protected int maxBp;
	protected int mp;
	protected int maxMp;
	protected int ep;
	protected int maxEp;
	protected int strength;
	protected int constitution;
	protected int intelligence;
	protected int dexterity;
	protected float weight;
	protected float x;
	protected float y;
	protected float z;
	protected float pitch;
	protected float yaw;

	// Full Constructor
	public OldentideCharacter ( string name, string lastname, string guild, string race,
								string gender, string face, string skin, string zone, string head,
								string chest, string arms, string hands, string legs, string feet,
								string cloak, string necklace, string ringOne, string ringTwo,
								string rightHand, string leftHand, int id, int level, int hp,
								int maxHp, int bp, int maxBp, int mp, int maxMp, int ep, int maxEp,
								int strength, int constitution, int intelligence, int dexterity,
								float weight, float x, float y, float z, float pitch, float yaw ) {
		SetName(name);
	    SetLastname(lastname);
	    SetGuild(guild);
	    SetRace(race);
	    SetGender(gender);
	    SetFace(face);
	    SetSkin(skin);
	    SetZone(zone);
	    SetHead(head);
	    SetChest(chest);
	    SetArms(arms);
	    SetHands(hands);
	    SetLegs(legs);
	    SetFeet(feet);
	    SetCloak(cloak);
	    SetNecklace(necklace);
	    SetRingOne(ringOne);
	    SetRingTwo(ringTwo);
	    SetRightHand(rightHand);
	    SetLeftHand(leftHand);
	    SetId(id);
	    SetLevel(level);
	    SetHp(hp);
	    SetMaxHp(maxHp);
	    SetBp(bp);
	    SetMaxBp(maxBp);
	    SetMp(mp);
	    SetMaxMp(maxMp);
	    SetEp(ep);
	    SetMaxEp(maxEp);
	    SetStrength(strength);
	    SetConstitution(constitution);
	    SetIntelligence(intelligence);
	    SetDexterity(dexterity);
	    SetX(x);
	    SetY(y);
	    SetZ(z);
	    SetPitch(pitch);
	    SetYaw(yaw);
	}

	public OldentidePosition GetPosition () {
		return OldentidePosition(zone, x, y, z, pitch, yaw);
	}

	public void UpdatePosition ( string zone, float x, float y, float z, float pitch, float yaw) {
		SetZone(zone);
		SetX(x);
		SetY(y);
		SetZ(z);
		SetPitch(pitch);
		SetYaw(yaw);
	}

	public void UpdatePosition ( OldentidePosition position ) {
		SetZone(position.zone);
		SetX(position.x);
		SetY(position.y);
		SetZ(position.z);
		SetPitch(position.pitch);
		SetYaw(position.yaw);
	}

	public void Start () {

	}

	public void Update () {

	}

	// Getters

	public string GetName() {
	    return name;
	}

	public string GetLastname() {
	    return lastname;
	}

	public string GetGuild() {
	    return guild;
	}

	public string GetRace() {
	    return race;
	}

	public string GetGender() {
	    return gender;
	}

	public string GetFace() {
	    return face;
	}

	public string GetSkin() {
	    return skin;
	}

	public string GetZone() {
	    return zone;
	}

	public string GetHead() {
	    return head;
	}

	public string GetChest() {
	    return chest;
	}

	public string GetArms() {
	    return arms;
	}

	public string GetHands() {
	    return hands;
	}

	public string GetLegs() {
	    return legs;
	}

	public string GetFeet() {
	    return feet;
	}

	public string GetCloak() {
	    return cloak;
	}

	public string GetNecklace() {
	    return necklace;
	}

	public string GetRingOne() {
	    return ringOne;
	}

	public string GetRingTwo() {
	    return ringTwo;
	}

	public string GetRightHand() {
	    return rightHand;
	}

	public string GetLeftHand() {
	    return leftHand;
	}

	public int GetId() {
		return id;
	}

	public int GetLevel() {
	    return level;
	}

	public int GetHp() {
	    return hp;
	}

	public int GetMaxHp() {
	    return maxHp;
	}

	public int GetBp() {
	    return bp;
	}

	public int GetMaxBp() {
	    return maxBp;
	}

	public int GetMp() {
	    return mp;
	}

	public int GetMaxMp() {
	    return maxMp;
	}

	public int GetEp() {
	    return ep;
	}

	public int GetMaxEp() {
	    return maxEp;
	}

	public int GetStrength() {
	    return strength;
	}

	public int GetConstitution() {
	    return constitution;
	}

	public int GetIntelligence() {
	    return intelligence;
	}

	public int GetDexterity() {
	    return dexterity;
	}

	public float GetWeight() {
	    return weight;
	}

	public float GetX() {
	    return x;
	}

	public float GetY() {
	    return y;
	}

	public float GetZ() {
	    return z;
	}

	public float GetPitch() {
	    return pitch;
	}

	public float GetYaw() {
	    return yaw;
	}

	// Setters

	public void SetName(string name) {
	    this.name = name;
	}

	public void SetLastname(string lastname) {
	    this.lastname = lastname;
	}

	public void SetGuild(string guild) {
	    this.guild = guild;
	}

	public void SetRace(string race) {
	    this.race = race;
	}

	public void SetGender(string gender) {
	    this.gender = gender;
	}

	public void SetFace(string face) {
	    this.face = face;
	}

	public void SetSkin(string skin) {
	    this.skin = skin;
	}

	public void SetZone(string zone) {
	    this.zone = zone;
	}

	public void SetHead(string head){
	    this.head = head;
	}

	public void SetChest(string chest){
	    this.chest = chest;
	}

	public void SetArms(string arms){
	    this.arms = arms;
	}

	public void SetHands(string hands){
	    this.hands = hands;
	}

	public void SetLegs(string legs){
	    this.legs = legs;
	}

	public void SetFeet(string feet){
	    this.feet = feet;
	}

	public void SetCloak(string cloak){
	    this.cloak = cloak;
	}

	public void SetNecklace(string necklace){
	    this.necklace = necklace;
	}

	public void SetRingOne(string ringOne){
	    this.ringOne = ringOne;
	}

	public void SetRingTwo(string ringTwo){
	    this.ringTwo = ringTwo;
	}

	public void SetRightHand(string rightHand){
	    this.rightHand = rightHand;
	}

	public void SetLeftHand(string leftHand){
	    this.leftHand = leftHand;
	}

	public void SetId(int id) {
		this.id = id;
	}

	public void SetLevel(int level) {
	    this.level = level;
	}

	public void SetHp(int hp) {
	    this.hp = hp;
	}

	public void SetMaxHp(int maxHp) {
	    this.maxHp = maxHp;
	}

	public void SetBp(int bp) {
	    this.bp = bp;
	}

	public void SetMaxBp(int maxBp) {
	    this.maxBp = maxBp;
	}

	public void SetMp(int mp) {
	    this.mp = mp;
	}

	public void SetMaxMp(int maxMp) {
	    this.maxMp = maxMp;
	}

	public void SetEp(int ep) {
	    this.ep = ep;
	}

	public void SetMaxEp(int maxEp) {
	    this.maxEp = maxEp;
	}

	public void SetStrength(int strength) {
	    this.strength = strength;
	}

	public void SetConstitution(int constitution) {
	    this.constitution = constitution;
	}

	public void SetYntelligence(int intelligence) {
	    this.public intelligence = public intelligence;
	}

	public void SetDexterity(int dexterity) {
	    this.dexterity = dexterity;
	}

	public void SetWeight(float weight) {
	    this.weight = weight;
	}

	public void SetX(float x) {
	    this.x = x;
	}

	public void SetY(float y) {
	    this.y = y;
	}

	public void SetZ(float z) {
	    this.z = z;
	}

	public void SetPitch(float pitch) {
	    this.pitch = pitch;
	}

	public void SetYaw(float yaw) {
	    this.yaw = yaw;
	}

}