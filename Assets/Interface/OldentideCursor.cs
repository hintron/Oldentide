using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OldentideCursor : MonoBehaviour {

	public Texture2D cursorTexture;
	public CursorMode CursorMode = CursorMode.Auto;
	public Vector2 hotSpot = Vector2.zero;
	// Use this for initialization
	void OnMouseEnter () {
		Cursor.SetCursor(cursorTexture, hotSpot, CursorMode);
	}
	
	// Update is called once per frame
	void OnMouseExit () {
		Cursor.SetCursor(null, Vector2.zero, CursorMode);
	}
}
