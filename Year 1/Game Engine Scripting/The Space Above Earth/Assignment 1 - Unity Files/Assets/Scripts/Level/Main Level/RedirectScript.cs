using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RedirectScript : MonoBehaviour
{
    //Variables
    [SerializeField] GameObject ErrorInteract;
    [SerializeField] GameObject PanelOne;
    [SerializeField] GameObject PanelTwo;
    [SerializeField] BoxCollider doorCollider;
    [SerializeField] BoxCollider levelCollider;
    bool hasSeenError = false;

    //Determines if an Object's Collider has enter This Object's Collider
    void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.tag == "Player")
        {
            ErrorInteract.SetActive(true);
            if (!hasSeenError)
            {
                PanelOne.SetActive(false);
                PanelTwo.SetActive(false);
                doorCollider.enabled = false;
                levelCollider.enabled = true;
                hasSeenError = true;
            }
        }
    }

    //Determines if an Object's Collider has left This Object's Collider
    void OnTriggerExit(Collider other)
    {
        if (other.gameObject.tag == "Player")
        {
            ErrorInteract.SetActive(false);
        }
    }
}
