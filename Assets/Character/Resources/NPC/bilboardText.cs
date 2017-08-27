using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class bilboardText : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        Camera mainCamera = Camera.main;
        Vector3 v = mainCamera.transform.position - transform.position;
        v.x = v.z = 0.0f;
        transform.LookAt(mainCamera.transform.position - v);
        transform.Rotate(0, 180, 0);
    }
}
