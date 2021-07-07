using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MainMenu : MonoBehaviour
{
    [SerializeField] Text highScoreText;
    [SerializeField] Text highestStageText;
    public void StartGame()
    {
        GameManager.Instance.SceneChanger(1);
    }

    public void ExitGame()
    {
        GameManager.Instance.SaveData();

        #if UNITY_EDITOR
        UnityEditor.EditorApplication.isPlaying = false;
        #elif UNITY_STANDALONE
        Application.Quit();
        #endif
    }
}
