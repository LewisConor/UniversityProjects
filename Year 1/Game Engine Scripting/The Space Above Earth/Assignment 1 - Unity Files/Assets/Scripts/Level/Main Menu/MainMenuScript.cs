using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MainMenuScript : MonoBehaviour
{
    //Variables
    [SerializeField] GameObject MainMenuPanel;
    [SerializeField] GameObject OptionsPanel;
    [SerializeField] AudioSource clickEffect;

    bool isLoading = false;

    //Public Function for Button which Starts the Game
    public void StartGame()
    {
        MainMenuPanel.SetActive(false);
        isLoading = true;
        SceneManager.LoadSceneAsync(1);
        clickEffect.PlayOneShot(clickEffect.clip);
    }

    //Public Function for Button which opens the Options Menu
    public void Options()
    {
        clickEffect.PlayOneShot(clickEffect.clip);
        MainMenuPanel.SetActive(false);
        OptionsPanel.SetActive(true);
    }

    //Public Function for Button which goes back to the Main Menu
    public void Back()
    {
        clickEffect.PlayOneShot(clickEffect.clip);
        OptionsPanel.SetActive(false);
        MainMenuPanel.SetActive(true);
        PlayerPrefs.Save();
    }

    //Public Function for Button which Exits the Game
    public void ExitGame()
    {
        clickEffect.PlayOneShot(clickEffect.clip);
        Application.Quit();

#if UNITY_EDITOR
        UnityEditor.EditorApplication.isPlaying = false;
#endif
    }

    //Creates a Box that says Loading... in the middle of the Screen
    void OnGUI()
    {
        if (isLoading == true)
        {
            GUIStyle style = new GUIStyle(GUI.skin.box);
            style.fontSize = 25;
            style.fontStyle = FontStyle.BoldAndItalic;
            style.alignment = TextAnchor.MiddleCenter;

            GUI.Box(new Rect(Screen.width / 2 - 100, Screen.height / 2 - 25, 200, 50), "LOADING...", style);
        }
    }
}
