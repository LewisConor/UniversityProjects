using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PressurePlateScript : MonoBehaviour
{
    //Variables
    [SerializeField] Animator animatorOne;
    [SerializeField] Animator animatorTwo;

    //Determines if an Object's Collider has enter This Object's Collider
    void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Box")
        {
            animatorOne.SetBool("doorOpen", true);
            animatorTwo.SetBool("doorOpen", true);
        }
    }

    //Determines if an Object's Collider has left This Object's Collider
    void OnTriggerExit(Collider other)
    {
        if (other.gameObject.tag == "Box")
        {
            animatorOne.SetBool("doorOpen", false);
            animatorTwo.SetBool("doorOpen", false);
        }
    }
}
