using UnityEngine;
using UnityEngine.SceneManagement;
using System.Collections;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class LoginManager : MonoBehaviour {

	public void CloseGame () {
		Application.Quit();
	}

	public void Login () {
		IEnumerator coroutine = SubmitLoginForm();
		StartCoroutine(coroutine);
	}

	private IEnumerator SubmitLoginForm () {
		string url = "https://" + GameObject.Find("Server_Address_Box").GetComponent<InputField>().text + "/login";
		Debug.Log(url);
		Debug.Log(GameObject.Find("Password_Box").GetComponent<InputField>().text);
		WWWForm form = new WWWForm();
		form.AddField( "login_username", GameObject.Find("Username_Box").GetComponent<InputField>().text );
		form.AddField( "login_password", GameObject.Find("Password_Box").GetComponent<InputField>().text );
		Debug.Log(form.ToString());
		WWW download  = new WWW(url, form);
		yield return download;
		if(!string.IsNullOrEmpty(download.error)) {
            print( "Error downloading: " + download.error );
        } else {
            Debug.Log(download.text);
        }
	}

	public void ChangeScene (string newScene) {
		SceneManager.LoadScene(newScene, LoadSceneMode.Single);
	}
}
