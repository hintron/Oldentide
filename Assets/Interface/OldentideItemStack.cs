using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Oldentide.Game {
	public class OldentideItemStack : MonoBehaviour {

		private OldentideItem item;
		private int count;

		// Use this for initialization
		void Start () {
			
		}
		
		// Update is called once per frame
		void Update () {
			
		}

		public OldentideItemStack(OldentideItem item, int count) {
			this.item = item;
			this.count = count;
		}

		public OldentideItem GetItem() {
			return item;
		}

		public int GetCount() {
			return count;
		}

		public void SetItem(OldentideItem item) {
			this.item = item;
		}

		public void SetCount(int count) {
			this.count = count;
		}
	}
}
