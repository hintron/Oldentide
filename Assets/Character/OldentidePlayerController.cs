using UnityEngine;
using System.Collections;

public class OldentidePlayerController : MonoBehaviour {

	public float inputDelay = 0.1f;
	public float forwardVel = 12;
	public float rotateVel = 100;
	
	Quaternion targetRotation;
	Rigidbody rBody;
	float forwardInput;
	float turnInput;	

	public Quaternion TargetRotation {
		get { return targetRotation; }
	}

	void Start() {
		targetRotation = transform.rotation;
		if (GetComponent<Rigidbody>()) {
			rBody = GetComponent<Rigidbody>();
		}
		else {
			Debug.LogError("The Oldentide Player Controller's target needs a Rigidbody.");
		}
		forwardInput = turnInput = 0;
	}

	void GetInput() {
		forwardInput = Input.GetAxis("Vertical");
		turnInput = Input.GetAxis("Horizontal");
	}

	void Update() {
		GetInput();
		Turn();
	}

	void FixedUpdate() {
		Run();
	}

	void Run() {
		if (Mathf.Abs(forwardInput) > inputDelay) {
			rBody.velocity = transform.forward * forwardInput * forwardVel;
		}
		else {
			rBody.velocity = Vector3.zero;
		}
	}

	void Turn() {
		if (Mathf.Abs(turnInput) > inputDelay) {
			targetRotation *= Quaternion.AngleAxis(rotateVel * turnInput * Time.deltaTime, Vector3.up);
		}
		transform.rotation = targetRotation;
	}

}
