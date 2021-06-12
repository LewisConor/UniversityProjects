using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    //Variables
    [SerializeField] int currentScene;

    //Allows the Manager to carry between Levels
    void Awake()
    {
        DontDestroyOnLoad(this.gameObject);
    }

    //Gets data to Set the Current Level
    public void SetCurrentScene(int newScene)
    {
        currentScene = newScene;
    }

    //Returns the Data of the current Level
    public int GetCurrentScene()
    {
        return currentScene;
    }
}
