using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Audio;

public class StartupScript : MonoBehaviour
{
    //Variables
    [SerializeField] float speedMultiplier;

    [SerializeField] Slider masterVolume;
    [SerializeField] Slider musicVolume;
    [SerializeField] Slider effectVolume;
    [SerializeField] AudioMixer mixer;

    [SerializeField] Dropdown resolutionDropdown;
    [SerializeField] Dropdown qualityDropdown;
    [SerializeField] Toggle isFullscreen;
    
    GameManager gameManager;

    //Runs at Runtime
    void Start()
    {
        Time.timeScale = 1;

        //Resets the Resolution Option in Options
        int screenWidth = Screen.currentResolution.width;
        int screenHeight = Screen.currentResolution.height;

        if (screenWidth == 800 && screenHeight == 600)
        {
            resolutionDropdown.SetValueWithoutNotify(0);
        }
        else if(screenWidth == 1366 && screenHeight == 768)
        {
            resolutionDropdown.SetValueWithoutNotify(1);
        }
        else if(screenWidth == 1920 && screenHeight == 1080)
        {
            resolutionDropdown.SetValueWithoutNotify(2);
        }
        else if(screenWidth == 2560 && screenHeight == 1440)
        {
            resolutionDropdown.SetValueWithoutNotify(3);
        }

        //Resets the Quality Setting in Options.
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

        //Resets the FullScreen Option
        isFullscreen.isOn = Screen.fullScreen;

        //Resets the Master Volume based on Player Data
        if (PlayerPrefs.HasKey("master"))
        {
            masterVolume.value = PlayerPrefs.GetFloat("master");
            mixer.SetFloat("masterVolume", PlayerPrefs.GetFloat("master"));
        }

        //Resets the Music Volume based on Player Data
        if (PlayerPrefs.HasKey("music"))
        {
            musicVolume.value = PlayerPrefs.GetFloat("music");
            mixer.SetFloat("musicVolume", PlayerPrefs.GetFloat("music"));
        }

        //Resets the Effects Volume based on Player Data
        if (PlayerPrefs.HasKey("effect"))
        {
            effectVolume.value = PlayerPrefs.GetFloat("effect");
            mixer.SetFloat("effectsVolume", PlayerPrefs.GetFloat("effect"));
        }
    }

    // Update is called once per frame
    void Update()
    {
        //Checks if the Game Manager has been Assigned
        if(gameManager == null)
        {
            gameManager = GameObject.FindGameObjectWithTag("Game Manager").GetComponent<GameManager>();
            gameManager.SetCurrentScene(0);
        }

        //Rotates the Skybox
        RenderSettings.skybox.SetFloat("_Rotation", Time.time * speedMultiplier);
    }
}
