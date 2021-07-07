using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MainMenu : MonoBehaviour
{
    [SerializeField] Text highScoreText;
    [SerializeField] Text highestStageText;

    void Start()
    {
        highScoreText.text = "Highscore: " + GameManager.Instance.GetHighScore();
        highestStageText.text = "Highest Stage: " + GameManager.Instance.GetHighestStage();
    }

    public void StartGame()
    {
        GameManager.Instance.SceneChanger(1);
    }

    public void ExitGame()
    {
        #if UNITY_EDITOR
        UnityEditor.EditorApplication.isPlaying = false;
        #elif UNITY_STANDALONE
        Application.Quit();
        #endif
    }
}
