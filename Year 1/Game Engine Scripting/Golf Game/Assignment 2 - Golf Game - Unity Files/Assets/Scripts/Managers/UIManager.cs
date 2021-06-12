using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIManager : MonoBehaviour
{
    [Header("Main UI Elements", order = 0)]
    [SerializeField] GameObject mainUI;
    [SerializeField] Button pushButton;
    [SerializeField] Joystick joystick;
    [SerializeField] Slider powerSlider;
    [SerializeField] Text scoreText;
    [SerializeField] Text shotsText;
    [SerializeField] Text parText;

    [Header("Score UI Elements", order = 1)]
    [SerializeField] GameObject scoreScreen;
    [SerializeField] GameObject wordParent;
    [SerializeField] GameObject[] golfWordObjects;
    [SerializeField] Text totalText;
    [SerializeField] GameObject nextHole;

    [Header("Pause UI Elements", order = 2)]
    [SerializeField] GameObject pauseMenu;

    void Start()
    {
        SetWordArray();
        SetPar();
        SetScore();
    }

    #region Main UI
    public void EnableButton() { pushButton.interactable = true; }
    public void DisableButton() { pushButton.interactable = false; }

    public void EnableJoystick() { joystick.enabled = true; }
    public void DisableJoystick() { joystick.enabled = false; }

    public void SetMaxPowerSlider(float maxPower) { powerSlider.maxValue = maxPower; }
    public void UpdatePowerSliderValue(float currentPower) { powerSlider.value = currentPower; }

    public void SetPar() { parText.text = "Par: " + GetComponent<GolfManager>().GetPar().ToString(); }
    public void SetScore() { scoreText.text = "Score: " + GameManager.Instance.GetScore().ToString(); }
    public void SetShots() { shotsText.text = "Shots: " + GetComponent<GolfManager>().GetShots().ToString(); }

    public void EnableUI() { mainUI.SetActive(true); }
    public void DisableUI() { mainUI.SetActive(false); }
    #endregion

    #region Score UI
    public void SetWordArray()
    {
        int i = 0;
        foreach (Transform wordTransform in wordParent.GetComponentInChildren<Transform>())
        {
            golfWordObjects[i] = wordTransform.gameObject;
            i++;
        }
    }
    public void DisplayGolfScore(int wordNum) 
    { 
        scoreScreen.SetActive(true); 
        golfWordObjects[wordNum].SetActive(true); 

        if(GameManager.Instance.GetCurrentScene() == 10)
        {
            nextHole.SetActive(false);
        }
    }
    public void SetTotal() { totalText.text = "Total Score: " + GameManager.Instance.GetScore().ToString(); }
    public void NextHole() { GameManager.Instance.NextScene(); }
    #endregion

    #region Pause UI
    public void OpenPauseMenu()
    {
        Time.timeScale = 0;
        DisableUI();
        pauseMenu.SetActive(true);
    }

    public void ResumeGame()
    {
        Time.timeScale = 1;
        EnableButton();
        pauseMenu.SetActive(false);
    }

    public void ExitGame()
    {
        Time.timeScale = 1;
        GameManager.Instance.BackToMainMenu();
    }
    #endregion
}