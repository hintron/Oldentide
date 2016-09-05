using UnityEngine;
using System.Collections;

public class CharacterMenu : MonoBehaviour {

	public GUISkin characterMenuSkin;

	// IMGUI interface initialization.
	void OnGUI() {
		GUI.skin = characterMenuSkin;
		GUI.Window(0, new Rect(0, 0, 300, 600), ToDrag, "");
	}

	void ToDrag(int windowId) {
		GUI.DragWindow(new Rect(0, 0, 10000, 20));
	}
	
}
