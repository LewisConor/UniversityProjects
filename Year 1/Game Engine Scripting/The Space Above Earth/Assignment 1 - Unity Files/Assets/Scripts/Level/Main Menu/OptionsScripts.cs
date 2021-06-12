using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Audio;

public class OptionsScripts : MonoBehaviour
{
    //Variables
    [SerializeField] AudioMixer audioMixer;
    [SerializeField] AudioSource clickEffect;
    [SerializeField] bool isFullscreened;

    //Public Function for the Slider which sets the Master Volume
    public void SetMasterVolume(float volume)
    {
        audioMixer.SetFloat("masterVolume", volume);
        clickEffect.PlayOneShot(clickEffect.clip);
        PlayerPrefs.SetFloat("master", volume);
    }

    //Public Function for the Slider which sets the Music Volume
    public void SetMusicVolume(float volume)
    {
        audioMixer.SetFloat("musicVolume", volume);
        clickEffect.PlayOneShot(clickEffect.clip);
        PlayerPrefs.SetFloat("music", volume);
    }

    //Public Function for the Slider which sets the Effect Volume
    public void SetEffectVolume(float volume)
    {
        audioMixer.SetFloat("effectsVolume", volume);
        clickEffect.PlayOneShot(clickEffect.clip);
        PlayerPrefs.SetFloat("effect", volume);
    }

    //Public Function for the Dropdown Box which sets the Quality
    public void SetQuality(int qualityIndex)
    {
        QualitySettings.SetQualityLevel(qualityIndex);
        clickEffect.PlayOneShot(clickEffect.clip);
    }

    //Public Function for the Dropdown Box which sets the Resolution
    public void SetResolution(int qualityIndex)
    {
        switch (qualityIndex)
        {
            case 0:
                Screen.SetResolution(800, 600, isFullscreened);
                break;
            case 1:
                Screen.SetResolution(1366, 768, isFullscreened);
                break;
            case 2:
                Screen.SetResolution(1920, 1080, isFullscreened);
                break;
            case 3:
                Screen.SetResolution(2560, 1440, isFullscreened);
                break;
        }
    }

    //Public Function for the Toggle Button which sets the Screen FullScreen
    public void SetFullscreen(bool isFullscreen)
    {
        Screen.fullScreen = isFullscreen;
        isFullscreened = isFullscreen;
        clickEffect.PlayOneShot(clickEffect.clip);
    }
}
