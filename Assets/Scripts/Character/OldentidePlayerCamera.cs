using UnityEngine;
using System.Collections;
using UnityStandardAssets.CrossPlatformInput;

public class OldentidePlayerCamera : MonoBehaviour {

	public Transform target;
	public float lookSmooth = 0.09f;
	public Vector3 offsetFromTarget = new Vector3(0, 6, -8);
	public float xTilt = 10;
	public float maxZoom = -12;

	Vector3 destination = Vector3.zero;
	OldentidePlayerController playerController;
	float rotateVel = 0;
	float zoomInput;

	void Start () {
		SetCameraTarget(target);
	}
	
	void SetCameraTarget(Transform t) {
		target = t;
		if (target != null) {
			if (target.GetComponent<OldentidePlayerController>()) {
				playerController = target.GetComponent<OldentidePlayerController>();
			}
			else {
				Debug.LogError("The camera's target needs to have the Oldentide Player Controller.");
			}
		}
		else {
			Debug.LogError("Your camera needs a target.");
		}
	}

	void Update() {
		zoomInput = Input.GetAxis("Mouse ScrollWheel");
		if ((offsetFromTarget.z + zoomInput) > maxZoom && (offsetFromTarget.z + zoomInput) < -2){
			offsetFromTarget.z += zoomInput;
		}
	}

	void LateUpdate() {
		MoveToTarget();
		LookAtTarget();
	}

	void MoveToTarget() {
		destination = playerController.TargetRotation * offsetFromTarget;
		destination += target.position;
		transform.position = destination;
	}

	void LookAtTarget() {
		float eulerYAngle = Mathf.SmoothDampAngle(transform.eulerAngles.y, target.eulerAngles.y, ref rotateVel, lookSmooth);
		transform.rotation = Quaternion.Euler(transform.eulerAngles.x, eulerYAngle, 0);
	}

}
