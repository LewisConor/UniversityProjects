using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class MainMenu : MonoBehaviour
{
    [SerializeField] GameManager gameManager;

    [Header("UI Elements", order = 0)]
    [SerializeField] GameObject mainObject;
    [SerializeField] GameObject optionsObject;
    [SerializeField] Slider volumeSlider;

    void Awake()
    {
        gameManager = GameManager.Instance;
    }

    #region Main Menu
    public void Play()
    {
        gameManager.NextScene();
    }

    public void Options()
    {
        mainObject.SetActive(false);
        optionsObject.SetActive(true);

        volumeSlider.value = gameManager.ReturnVolume();
    }

    public void Exit()
    {
        Application.Quit();
    }
    #endregion

    #region Options
    public void SetVolume(float volume)
    {
        GameManager.Instance.SetVolume(volume);
    }

    public void Back()
    {
        PlayerPrefs.Save();
        optionsObject.SetActive(false);
        mainObject.SetActive(true);
    }
    #endregion
}
