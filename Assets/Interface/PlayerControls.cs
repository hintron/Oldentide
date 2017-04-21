using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerControls : MonoBehaviour {

	public GameObject characterMenu;
	private bool characterMenuFlag;
	public GameObject inventoryMenu;
	private bool inventoryMenuFlag;
	public GameObject spellbookMenu;
	private bool spellbookMenuFlag;
	public GameObject mapMenu;
	private bool mapMenuFlag;
	public GameObject partyMenu;
	private bool partyMenuFlag;
	public GameObject settingsMenu;
	private bool settingsMenuFlag;
	public GameObject exitMenu;
	private bool exitMenuFlag;

	// Use this for initialization
	void Start () {
		characterMenuFlag = false;
		characterMenu.SetActive(characterMenuFlag);
		inventoryMenuFlag = false;
		inventoryMenu.SetActive(inventoryMenuFlag);
		spellbookMenuFlag = false;
		spellbookMenu.SetActive(spellbookMenuFlag);
		mapMenuFlag = false;
		mapMenu.SetActive(mapMenuFlag);
		partyMenuFlag = false;
		partyMenu.SetActive(partyMenuFlag);
		settingsMenuFlag = false;
		settingsMenu.SetActive(settingsMenuFlag);
		exitMenuFlag = false;
		exitMenu.SetActive(exitMenuFlag);
	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetKeyDown("c")) {
			if (characterMenuFlag) {
				Debug.Log("Character menu closed.");
				characterMenuFlag = false;
			}
			else {
				Debug.Log("Character menu opened.");
				characterMenuFlag = true;
			}
			characterMenu.SetActive(characterMenuFlag);
		}

		if (Input.GetKeyDown("i")) {
			if (inventoryMenuFlag) {
				Debug.Log("Inventory menu closed.");
				inventoryMenuFlag = false;
			}
			else {
				Debug.Log("Inventory menu opened.");
				inventoryMenuFlag = true;
			}
			inventoryMenu.SetActive(inventoryMenuFlag);
		}

		if (Input.GetKeyDown("s")) {
			if (spellbookMenuFlag) {
				Debug.Log("Spellbook menu closed.");
				spellbookMenuFlag = false;
			}
			else {
				Debug.Log("Spellbook menu opened.");
				spellbookMenuFlag = true;
			}
			spellbookMenu.SetActive(spellbookMenuFlag);
		}

		if (Input.GetKeyDown("m")) {
			if (mapMenuFlag) {
				Debug.Log("Map menu closed.");
				mapMenuFlag = false;
			}
			else {
				Debug.Log("Map menu opened.");
				mapMenuFlag = true;
			}
			mapMenu.SetActive(mapMenuFlag);
		}

		if (Input.GetKeyDown("p")) {
			if (partyMenuFlag) {
				Debug.Log("Party menu closed.");
				partyMenuFlag = false;
			}
			else {
				Debug.Log("Party menu opened.");
				partyMenuFlag = true;
			}
			partyMenu.SetActive(partyMenuFlag);
		}

		if (Input.GetKeyDown("q")) {
			if (settingsMenuFlag) {
				Debug.Log("Settings menu closed.");
				settingsMenuFlag = false;
			}
			else {
				Debug.Log("Settings menu opened.");
				settingsMenuFlag = true;
			}
			settingsMenu.SetActive(settingsMenuFlag);
		}

		if (Input.GetKeyDown("escape")) {
			if (exitMenuFlag) {
				Debug.Log("Exit menu closed.");
				exitMenuFlag = false;
			}
			else {
				Debug.Log("Exit menu opened.");
				exitMenuFlag = true;
			}
			exitMenu.SetActive(exitMenuFlag);
		}
	}
}
