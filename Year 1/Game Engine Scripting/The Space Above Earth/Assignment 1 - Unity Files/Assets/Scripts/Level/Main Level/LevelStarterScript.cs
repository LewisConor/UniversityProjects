using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LevelStarterScript : MonoBehaviour
{
    //Variables
    GameManager gameManager;
    [SerializeField] float speedMultiplier;

    //Starts on Runtime
    void Start()
    {
        //Finds the Game Manager and assigns it
        gameManager = GameObject.FindGameObjectWithTag("Game Manager").GetComponent<GameManager>();
        
        //Sets the Current Level in Data
        if (gameManager.GetCurrentScene() == 1)
        {
            gameManager.SetCurrentScene(2);
        }
    }

    //Updates every Frame
    void Update()
    {
        //Rotates the Skybox
        RenderSettings.skybox.SetFloat("_Rotation", Time.time * speedMultiplier);
    }
}
