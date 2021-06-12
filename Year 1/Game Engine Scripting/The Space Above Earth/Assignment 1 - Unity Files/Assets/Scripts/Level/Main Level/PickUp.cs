using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PickUp : MonoBehaviour
{
    //Variables
    [SerializeField] Transform onHand;
    [SerializeField] GameObject Interact;
    bool isLooking = false;
    bool hasPickedUp = false;

    //Used to determine if the Player is looking at the object (aka the Collider for the Object)
    void OnMouseEnter()
    {
        if (!hasPickedUp)
        {
            Interact.SetActive(true);
        }

        isLooking = true;        
    }

    //Used to determine if the Player has stopped looking at the object (aka the Collider for the Object)
    void OnMouseExit()
    {
        Interact.SetActive(false);
        isLooking = false;
    }

    //Used to determine if the Player is holding down Left Clicked at the object (aka the Collider for the Object)
    void OnMouseDown()
    {
        Interact.SetActive(false);
        this.gameObject.GetComponent<Rigidbody>().useGravity = false;
        this.gameObject.GetComponent<Rigidbody>().isKinematic = true;
        this.transform.position = onHand.position;
        this.transform.parent = GameObject.Find("FPSController").transform;
        this.transform.parent = GameObject.Find("FirstPersonCharacter").transform;
        hasPickedUp = true;
    }

    //Used to determine if the Player has let go of Left Clicked at the object (aka the Collider for the Object)
    void OnMouseUp()
    {
        this.transform.parent = null;
        this.gameObject.GetComponent<Rigidbody>().useGravity = true;
        this.gameObject.GetComponent<Rigidbody>().isKinematic = false;
        hasPickedUp = false;
    }
}
