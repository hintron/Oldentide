using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Simplified_Controller : MonoBehaviour {

	public GameObject cube;
	public float speed = 50f;

	void start() {
		cube = GetComponent<GameObject>();
	}

	// Update is called once per frame
	void Update() {
		var x = Input.GetAxis("Horizontal") * Time.deltaTime * speed;
        var z = Input.GetAxis("Vertical") * Time.deltaTime * speed;
		transform.Translate(x,0f,z);
	}
}
