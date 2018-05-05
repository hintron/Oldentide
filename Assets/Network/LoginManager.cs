using UnityEngine;
using UnityEngine.SceneManagement;
using System.Collections;
using System.Text.RegularExpressions;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class LoginManager : MonoBehaviour {

	public GameObject failedLogin;
	public GameObject playerInformation;

	void Start () {
		failedLogin.SetActive(false);
	}

	public void CloseGame () {
		Application.Quit();
	}

	public void Login () {
		IEnumerator coroutine = SubmitLoginForm();
		StartCoroutine(coroutine);
	}

	private IEnumerator SubmitLoginForm () {
		string url = GameObject.Find("Server_Address_Box").GetComponent<InputField>().text;
		if (url != "") {
			url = "https://" + url + "/login";
		}
		else {
			url = GameObject.Find("Server_Address_Box").GetComponent<InputField>().placeholder.GetComponent<Text>().text;
			url = "https://" + url + "/login";
		}

		Debug.Log(url);
		Debug.Log(GameObject.Find("Password_Box").GetComponent<InputField>().text);
		WWWForm form = new WWWForm();
		string username = GameObject.Find("Username_Box").GetComponent<InputField>().text;
		string password = GameObject.Find("Password_Box").GetComponent<InputField>().text;
		form.AddField( "login_username", username);
		form.AddField( "login_password", password);
		Debug.Log(form.ToString());
		WWW download  = new WWW(url, form);
		yield return download;
		
		if(!string.IsNullOrEmpty(download.error)) {
            print( "Error downloading: " + download.error );
        } else {
            Debug.Log(download.text);
            string cookie;
            if (download.responseHeaders.TryGetValue("SET-COOKIE", out cookie)) {
            	Regex sessionFinder = new Regex("session_id=([^;]*)");
            	Match sessionId = sessionFinder.Match(cookie);
            	Debug.Log(sessionId.Groups[1].Value);
            	failedLogin.SetActive(false);
            	OldentidePlayerInformation.accountName = username;
            	OldentidePlayerInformation.sessionId = sessionId.Groups[1].Value;
            	//playerInformation.GetComponent("OldentidePlayerInformation.cs").SetAccountName(username);
            	//playerInformation.GetComponent("OldentidePlayerInformation.cs").SetSessionId(sessionId);
            	ChangeScene("Newcomers_Guild");
            }
            else {
            	Debug.Log("User failed to login correctly to the server.");
            	failedLogin.SetActive(true);
            }
        }
	}

	public void ChangeScene (string newScene) {
		SceneManager.LoadScene(newScene, LoadSceneMode.Single);
	}
}
