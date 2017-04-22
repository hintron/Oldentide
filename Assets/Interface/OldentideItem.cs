using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Oldentide.Game {
	public class OldentideItem : MonoBehaviour {

		private string itemName;
		private int id;
		private int weight;

		// Use this for initialization
		void Start () {
			
		}
		
		// Update is called once per frame
		void Update () {
			
		}

		public OldentideItem(string itemName, int id, int weight) {
			this.itemName = itemName;
			this.id = id;
			this.weight = weight;
		}

		public string GetItemName() {
			return itemName;
		}

		public int GetId() {
			return id;
		}

		public int GetWeight() {
			return weight;
		}

		public void SetItemName(string itemName) {
			this.itemName = itemName;
		}

		public void SetId(int id) {
			this.id = id;
		}

		public void SetWeight(int weight) {
			this.weight = weight;
		}
	}
}
