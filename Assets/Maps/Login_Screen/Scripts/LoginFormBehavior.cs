using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class LoginFormBehavior : MonoBehaviour {
	EventSystem system;

	void Start () {
        system = EventSystem.current;
    }

	// Update is called once per frame
	void Update () {
		if (Input.GetKeyDown(KeyCode.Tab)) {
			GameObject current = system.currentSelectedGameObject;
			if (current != null) {
				GameObject target = null;
				switch (current.name) {
					case "Username_Box":
						target = GameObject.Find("Password_Box");
						break;
					case "Password_Box":
						target = GameObject.Find("Server_Address_Box");
						break;
					case "Server_Address_Box":
						target = GameObject.Find("Server_Port_Box");
						break;
					case "Server_Port_Box":
						target = GameObject.Find("Login_Button");
						break;
					default:
						break;
				}
				if (target != null) {
					system.SetSelectedGameObject(target, new BaseEventData(system));
				}
			}
		}
	}
}
