using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NpcDefinition : Object {
    public string itemId;
    public Vector3 position;
    public Quaternion orientation;
}

public class ZoneStateManager : MonoBehaviour {

    public GameObject npcContainer;
    private Dictionary<string, string> gamePrefabs = new Dictionary<string, string>() {
        { "guild_master", "NPC/NPC_GuildMaster" }
    };

	// Use this for initialization
	void Start () {

        NpcDefinition testDefinition = new NpcDefinition();
        testDefinition.itemId = "guild_master";
        testDefinition.position = new Vector3(34, 0.4f, 24);
        testDefinition.orientation = Quaternion.Euler(0, -90, 0);
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public void consumeServerPacket() {
        // TODO

    }

    private GameObject createNewNPC(NpcDefinition npcDefinition) {
        string prefabPath = gamePrefabs[npcDefinition.itemId];
        UnityEngine.Object prefab = Resources.Load(prefabPath);
        GameObject npcGameObject = (GameObject)GameObject.Instantiate(
            prefab, npcDefinition.position, npcDefinition.orientation);
        npcGameObject.transform.parent = npcContainer.transform;
        return npcGameObject;
    }

    private void deleteNPC() {
        // TODO
    }
}
