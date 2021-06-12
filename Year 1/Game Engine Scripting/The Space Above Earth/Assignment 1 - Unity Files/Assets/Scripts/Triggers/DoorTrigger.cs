using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DoorTrigger : MonoBehaviour
{
    //Variables
    [SerializeField] Animator animator1;
    [SerializeField] Animator animator2;

    //Determines if the Player has entered the Colider of the Door to Trigger the Open Animation
    void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Player")
        {
            animator1.SetBool("doorOpen", true);
            animator2.SetBool("doorOpen", true);
        }
    }

    //Determines if the Player has left the Colider of the Door to Trigger the Close Animation
    void OnTriggerExit(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            animator1.SetBool("doorOpen", false);
            animator2.SetBool("doorOpen", false);
        }
    }
}
