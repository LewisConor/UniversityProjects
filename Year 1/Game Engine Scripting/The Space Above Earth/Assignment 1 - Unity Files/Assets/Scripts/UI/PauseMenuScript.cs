using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using UnityEngine.Audio;

public class PauseMenuScript : MonoBehaviour
{
    //Variables
    [SerializeField] GameObject pauseMenu;
    [SerializeField] GameObject optionsMenu;

    [SerializeField] Slider masterVolume;
    [SerializeField] Slider musicVolume;
    [SerializeField] Slider effectVolume;
    [SerializeField] AudioMixer mixer;

    [SerializeField] Dropdown resolutionDropdown;
    [SerializeField] Dropdown qualityDropdown;
    [SerializeField] Toggle isFullscreen;

    GameManager gameManager;

    //Public Function for the Button which Resumes the Game
    public void Resume()
    {
        Time.timeScale = 1;
        GameObject.FindGameObjectWithTag("Player").GetComponent<AdditionalPlayerScript>().isPaused = false;
        GameObject.FindGameObjectWithTag("Player").GetComponent<UnityStandardAssets.Characters.FirstPerson.FirstPersonController>().enabled = true;
        pauseMenu.SetActive(false);
    }

    //Public Function for the Button which Opens the Options Menu
    public void Options()
    {
        #region Resets the Resolution Option in Options
        int screenWidth = Screen.currentResolution.width;
        int screenHeight = Screen.currentResolution.height;

        if (screenWidth == 800 && screenHeight == 600)
        {
            resolutionDropdown.SetValueWithoutNotify(0);
        }
        else if (screenWidth == 1366 && screenHeight == 768)
        {
            resolutionDropdown.SetValueWithoutNotify(1);
        }
        else if (screenWidth == 1920 && screenHeight == 1080)
        {
            resolutionDropdown.SetValueWithoutNotify(2);
        }
        else if (screenWidth == 2560 && screenHeight == 1440)
        {
            resolutionDropdown.SetValueWithoutNotify(3);
        }
        #endregion

        #region Resets the Quality Setting in Options.
        int qualityIndex = QualitySettings.GetQualityLevel();

        switch (qualityIndex)
        {
            case 0:
                qualityDropdown.SetValueWithoutNotify(qualityIndex);
                break;
            case 1:
                qualityDropdown.SetValueWithoutNotify(qualityIndex);
                break;
            case 2:
                qualityDropdown.SetValueWithoutNotify(qualityIndex);
                break;
            case 3:
                qualityDropdown.SetValueWithoutNotify(qualityIndex);
                break;
            case 4:
                qualityDropdown.SetValueWithoutNotify(qualityIndex);
                break;
            case 5:
                qualityDropdown.SetValueWithoutNotify(qualityIndex);
                break;
        }
        #endregion

        isFullscreen.isOn = Screen.fullScreen;

        #region Resets the Volume Settings in Options
        if (PlayerPrefs.HasKey("master"))
        {
            masterVolume.value = PlayerPrefs.GetFloat("master");
            mixer.SetFloat("masterVolume", PlayerPrefs.GetFloat("master"));
        }

        if (PlayerPrefs.HasKey("music"))
        {
            musicVolume.value = PlayerPrefs.GetFloat("music");
            mixer.SetFloat("musicVolume", PlayerPrefs.GetFloat("music"));
        }

        if (PlayerPrefs.HasKey("Effect"))
        {
            effectVolume.value = PlayerPrefs.GetFloat("effect");
            mixer.SetFloat("effectsVolume", PlayerPrefs.GetFloat("effect"));
        }
        #endregion

        pauseMenu.SetActive(false);
        optionsMenu.SetActive(true);
    }

    //Public Function for the Button which goes back to the Pause Menu
    public void Back()
    {
        optionsMenu.SetActive(false);
        pauseMenu.SetActive(true);
    }

    //Public Function for the Button which Returns to the Main Menu
    public void Exit()
    {
        SceneManager.LoadSceneAsync(0);
    }
}
