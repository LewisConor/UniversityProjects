using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LoadTrigger : MonoBehaviour
{
    //Variables
    bool isLoading = false;

    //Determines if the Player has entered the Colider of the Door to Trigger the Load Level System
    void OnTriggerEnter(Collider other)
    {
        Scene currentScene = SceneManager.GetActiveScene();

        if(other.gameObject.tag == "Player")
        {
            if(this.gameObject.tag == "Hub Load")
            {
                if(currentScene.buildIndex != 1)
                {
                    GameObject.FindGameObjectWithTag("Player").SetActive(false);
                    isLoading = true;
                    SceneManager.LoadSceneAsync(1);
                }
            }
            else if(this.gameObject.tag == "Level Load")
            {
                if (currentScene.buildIndex != 2)
                {
                    GameObject.FindGameObjectWithTag("Player").SetActive(false);
                    isLoading = true;
                    SceneManager.LoadSceneAsync(2);
                }
            }
        }
    }

    //Creates a Box with Text Loading... in the center of the screen
    void OnGUI()
    {
        if(isLoading == true)
        {
            GUIStyle style = new GUIStyle(GUI.skin.box);

            style.fontSize = 25;
            style.fontStyle = FontStyle.BoldAndItalic;
            style.alignment = TextAnchor.MiddleCenter;

            GUI.Box(new Rect(Screen.width / 2 - 100, Screen.height / 2 - 25, 200, 50), "LOADING...", style);
        }
    }
}
