using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    public static GameManager Instance { get; private set; } = null;

    [SerializeField] int score = 0;
    [SerializeField] int lives = 3;

    void Awake()
    {
        if(Instance == null)
        {
            Instance = this;
            DontDestroyOnLoad(this);
        }
    }

    public void SceneChanger(int buildIndex)
    {
        SceneManager.LoadScene(buildIndex);
    }

    public int GetScore() { return score; }
    public void AddScore(int addScore) { score += addScore; }

    public int GetLives() { return lives; }
    public void RemoveLife() { lives--; }

    public void ResetData() { lives = 20; score = 0; }
}
