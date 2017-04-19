using UnityEngine;
using System.Collections;

public class OldentidePosition : MonoBehaviour {

	public string zone;
	public float x;
	public float y;
	public float z;
	public float pitch;
	public float yaw;

	public OldentidePosition ( string zone, float x, float y, float z, float pitch, float yaw ) {
		this.zone = zone;
		this.x = x;
		this.y = y;
		this.z = z;
		this.pitch = pitch;
		this.yaw = yaw;
	}

}