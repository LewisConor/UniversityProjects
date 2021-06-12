using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ButtonScript : MonoBehaviour
{
    //Variables
    [SerializeField] Animator animator;
    [SerializeField] GameObject Interact;
    [SerializeField] GameObject WinPanel;
    bool lookAtButton = false;
    bool winScreenActive = false;
    GameManager gameManager;

    // Update is called once per frame
    void Update()
    {
        //General Check incase Game Manager does not get Assigned
        if(gameManager == null)
        {
            gameManager = GameObject.FindGameObjectWithTag("Game Manager").GetComponent<GameManager>();
        }

        //Only Fall in if the Player is looking at the Button
        if(lookAtButton == true)
        {
            //Get which scene the Player is on which determines the Runtime Logic for that scene
            if(gameManager.GetCurrentScene() == 2)
            {
                if (Input.GetKeyDown(KeyCode.E))
                {
                    //Multiple Statement for Each Button to determine its control
                    if (this.gameObject.tag == "OneLeft")
                    {
                        if (animator.GetBool("Right"))
                        {
                            animator.SetBool("Right", false);
                            animator.SetBool("Center", true);
                        }
                        else if (animator.GetBool("Center"))
                        {
                            animator.SetBool("Center", false);
                            animator.SetBool("Left", true);
                        }
                    }
                    else if (this.gameObject.tag == "OneRight")
                    {
                        if (animator.GetBool("Left"))
                        {
                            animator.SetBool("Left", false);
                            animator.SetBool("Center", true);
                        }
                        else if (animator.GetBool("Center"))
                        {
                            animator.SetBool("Center", false);
                            animator.SetBool("Right", true);
                        }
                    }
                    else if (this.gameObject.tag == "TwoSwivelUp")
                    {
                        animator.SetBool("Swivel Up", true);
                        animator.SetBool("Swivel Down", false);
                    }
                    else if (this.gameObject.tag == "TwoSwivelDown")
                    {
                        animator.SetBool("Swivel Down", true);
                        animator.SetBool("Swivel Up", false);
                    }
                    else if (this.gameObject.tag == "ThreeUp")
                    {
                        animator.SetBool("Up", true);
                        animator.SetBool("Down", false);
                    }
                    else if (this.gameObject.tag == "ThreeDown")
                    {
                        animator.SetBool("Up", false);
                        animator.SetBool("Down", true);
                    }
                }
            }
            else if(gameManager.GetCurrentScene() == 1)
            {
                //If player presses E, they will turn on the Win Panel
                if (Input.GetKeyDown(KeyCode.E))
                {
                    GameObject.FindGameObjectWithTag("Player").GetComponent<UnityStandardAssets.Characters.FirstPerson.FirstPersonController>().enabled = false;
                    GameObject.FindGameObjectWithTag("Player").GetComponent<AdditionalPlayerScript>().SetWinScreenData(WinPanel);
                    WinPanel.SetActive(true);
                    Time.timeScale = 0;
                    Cursor.visible = true;
                    Cursor.lockState = CursorLockMode.None;
                }
            }
        }
    }

    //Used to determine if the Player is looking at the Button (aka the Collider for the Button)
    void OnMouseOver()
    {
        Interact.SetActive(true);
        lookAtButton = true;
    }

    //Used to determine if the Player has looked away from the Button (aka the Collider for the Button)
    void OnMouseExit()
    {
        Interact.SetActive(false);
        lookAtButton = false;
    }
}
