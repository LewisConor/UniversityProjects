using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class AdditionalPlayerScript : MonoBehaviour
{
    //Variables
    GameManager gameManager;
    [SerializeField] GameObject pauseMenu;
    [SerializeField] GameObject winScreen;
    public bool isPaused;

    //Runs at Runtime
    void Start()
    {
        //Assigns the Game Manager
        gameManager = GameObject.FindGameObjectWithTag("Game Manager").GetComponent<GameManager>();
    }

    // Update is called once per frame
    void Update()
    {
        //Checks if the Player has Pressed Escape
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            //Checks which scene the player is on
            if(gameManager.GetCurrentScene() == 1)
            {
                //Checks if the Win Screen is Active for Scene 1 (the Hub Level)
                if (!winScreen.activeSelf)
                {
                    //If not active, then the Pause Menu can be used.
                    if (isPaused == false)
                    {
                        GameObject.FindGameObjectWithTag("Player").GetComponent<UnityStandardAssets.Characters.FirstPerson.FirstPersonController>().enabled = false;
                        Time.timeScale = 0;
                        pauseMenu.SetActive(true);
                        isPaused = true;
                        Cursor.visible = true;
                        Cursor.lockState = CursorLockMode.None;
                    }
                    else
                    {
                        if (pauseMenu.activeSelf)
                        {
                            GameObject.FindGameObjectWithTag("Player").GetComponent<UnityStandardAssets.Characters.FirstPerson.FirstPersonController>().enabled = true;
                            Time.timeScale = 1;
                            pauseMenu.SetActive(false);
                            isPaused = false;
                            Cursor.visible = false;
                        }
                    }
                }
                else
                {
                    //Else returns to Main Menu
                    SceneManager.LoadSceneAsync(0);
                }
            }
            else
            {
                //Pause Menu can be used on other Level
                if (isPaused == false)
                {
                    GameObject.FindGameObjectWithTag("Player").GetComponent<UnityStandardAssets.Characters.FirstPerson.FirstPersonController>().enabled = false;
                    Time.timeScale = 0;
                    pauseMenu.SetActive(true);
                    isPaused = true;
                    Cursor.visible = true;
                    Cursor.lockState = CursorLockMode.None;
                }
                else
                {
                    if (pauseMenu.activeSelf)
                    {
                        GameObject.FindGameObjectWithTag("Player").GetComponent<UnityStandardAssets.Characters.FirstPerson.FirstPersonController>().enabled = true;
                        Time.timeScale = 1;
                        pauseMenu.SetActive(false);
                        isPaused = false;
                        Cursor.visible = false;
                    }
                }
            }
        }
    }

    //Sends the Win Screen Object to Other Scripts
    public void SetWinScreenData(GameObject gameObject)
    {
        winScreen = gameObject;
    }
}
