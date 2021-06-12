using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HubScript : MonoBehaviour
{
    //Variables
    [SerializeField] float speedMultiplier;
    [SerializeField] GameObject playerPosOne;
    [SerializeField] GameObject playerPosTwo;
    [SerializeField] GameObject buttonObject;
    [SerializeField] BoxCollider levelCollider;
    [SerializeField] BoxCollider doorCollider;
    GameManager gameManager;
    int previousScene;

    //Runs at Runtime
    void Start()
    {
        //Assigns the Game Manager
        gameManager = GameObject.FindGameObjectWithTag("Game Manager").GetComponent<GameManager>();

        //Checks which Scene the Player has come from and Sets which Character Pos is active
        if(gameManager.GetCurrentScene() == 0)
        {
            previousScene = gameManager.GetCurrentScene();
            playerPosOne.SetActive(true);
            gameManager.SetCurrentScene(1);
        }
        else if (gameManager.GetCurrentScene() == 2)
        {
            previousScene = gameManager.GetCurrentScene();

            buttonObject.SetActive(true);
            levelCollider.enabled = false;
            doorCollider.enabled = false;

            gameManager.SetCurrentScene(1);

            StartCoroutine(Timer());
            playerPosTwo.SetActive(true);
        }
    }

    void Update()
    {
        //Rotates the Skybox
        RenderSettings.skybox.SetFloat("_Rotation", Time.time * speedMultiplier);
    }

    //Simple 2 Second Timer
    IEnumerator Timer()
    {
        //Waits for 2 Seconds
        yield return new WaitForSeconds(2);
    }
}
