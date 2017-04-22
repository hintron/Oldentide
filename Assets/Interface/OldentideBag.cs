using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Oldentide.Game {
	public class OldentideBag : MonoBehaviour {

		private int size;
		private OldentideItemStack[] itemStacks;

		// Use this for initialization
		void Start () {
			
		}
		
		// Update is called once per frame
		void Update () {
			
		}

		public OldentideBag(int size) {
			this.size = size;
			itemStacks = new OldentideItemStack[size];
		}

		public int GetSize() {
			return size;
		}

		public void SetSize(int size) {
			this.size = size;
			// OldentideItemStack[] transfer = itemStacks;
			// items = new OldentideItemStack[size];
			// int i = 0;
			// foreach (OldentideItemStack itemStack in transfer){
			// 	if (itemStack != null) {
			// 		items[i] = itemStack;
			// 		i++;
			// 	}
			// }
		}

		public OldentideItemStack GetItemStack(int index) {
			return itemStacks[index];
		}

		public void SetItemStack(int index, OldentideItemStack itemStack) {
			itemStacks[index] = itemStack;
		}
	}
}
