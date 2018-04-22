using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Oldentide.Game;

public class InventoryController : MonoBehaviour {

	private int mites; // Basic unit of money.
	private int sterlings; // 1 Sterling = 50 Mites.
	private int pines; // 1 Pind = 16 Sterlings.
	private int metrads; // 1 Metrad = 20 Pines.
	private int bagZeroSize;
	private int bagOneSize;
	private int bagTwoSize;
	private int bagThreeSize;
	private OldentideBag[] bags;

	// Use this for initialization
	void Start () {
		bagZeroSize = 60;
		bagOneSize = 0;
		bagTwoSize = 0;
		bagThreeSize = 0;
		bags = new OldentideBag[4];
		bags[0] = new OldentideBag(bagZeroSize);
		bags[1] = new OldentideBag(bagOneSize);
		bags[2] = new OldentideBag(bagTwoSize);
		bags[3] = new OldentideBag(bagThreeSize);
	}
	
	// Update is called once per frame
	void Update () {
		
	}

	public void ChangeBagSize(int bagNumber, int bagSize) {
		bags[bagNumber].SetSize(bagSize);
	}

	public OldentideBag GetBag(int bagNumber) {
		return bags[bagNumber];
	}

	public void MoveItemStack(int startBag, int startIndex, int finalBag, int finalIndex, int count) {
		OldentideItemStack startItemStack = bags[startBag].GetItemStack(startIndex);
		OldentideItemStack finalItemStack = bags[finalBag].GetItemStack(finalIndex);
		if (startItemStack.GetItem().GetId() == finalItemStack.GetItem().GetId()) {
			if (startItemStack.GetCount() == count) {
				bags[startBag].SetItemStack(startIndex, null);
				bags[finalBag].GetItemStack(finalIndex).SetCount(count);
			}
			else if (startItemStack.GetCount() > count) {
				bags[startBag].GetItemStack(startIndex).SetCount(startItemStack.GetCount() - count);	
				bags[finalBag].GetItemStack(finalIndex).SetCount(count);
			}
		}
		else if (startItemStack != null && finalItemStack == null) {
			if (startItemStack.GetCount() == count) {
				bags[startBag].SetItemStack(startIndex, null);
				bags[finalBag].SetItemStack(finalIndex, startItemStack);
			}
			else if (startItemStack.GetCount() > count) {
				bags[startBag].GetItemStack(startIndex).SetCount(startItemStack.GetCount() - count);	
				startItemStack.SetCount(startItemStack.GetCount() - count);
				bags[finalBag].SetItemStack(finalIndex, startItemStack);
			}
		}
		else {
			Debug.Log("Player tried to move something incorrectly.");
		}
	}
}
