using UnityEngine;
using UnityEngine.SceneManagement;
using System.Collections;

public class LoginManager : MonoBehaviour {

	public void ChangeScene (string newScene) {
		SceneManager.LoadScene(newScene, LoadSceneMode.Single);
	}

}
