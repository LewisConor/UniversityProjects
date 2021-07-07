using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    static GameManager instance;

    [SerializeField] int score;
    [SerializeField] int highScore;

    [SerializeField] int stage = 1;
    [SerializeField] int highestStage;

    public static GameManager Instance
    {
        get
        {
            return instance;
        }
    }

    void Awake()
    {
        if(Instance == null)
        {
            instance = this;
            DontDestroyOnLoad(this);
        }

        if (PlayerPrefs.HasKey("highScore"))
        {
            highScore = PlayerPrefs.GetInt("highScore");
        }
        else
        {
            highScore = 0;
        }

        if (PlayerPrefs.HasKey("highestStage"))
        {
            highestStage = PlayerPrefs.GetInt("highestStage");
        }
        else
        {
            highestStage = 1;
        }
    }

    void Update()
    {
        //Stage 1 > 2
        if (score >= 5 && score < 10)
        {
            if(stage != 2)
            {
                stage++;
            }
        }

        //Stage 2 > 3
        if (score >= 10 && score < 15)
        {
            if(stage != 3)
            {
                stage++;
            }
        }

        //Stage 3 > 4
        if (score >= 15 && score < 20)
        {
            if(stage != 4)
            {
                stage++;
            }
        }

        //Stage 4 > 5
        if (score >= 20 && score < 25)
        {
            if(stage != 5)
            {
                stage++;
            }
        }

    }

    public void SceneChanger(int buildIndex)
    {
        if(buildIndex == 0)
        {
            highScore = score;
            highestStage = stage;
            PlayerPrefs.SetInt("highScore", highScore);
            PlayerPrefs.SetInt("highestStage", highestStage);
        }

        SceneManager.LoadScene(buildIndex);
    }

    public void AddScore()
    {
        score++;
    }

    public int GetScore()
    {
        return score;
    }

    public int GetHighScore()
    {
        return highScore;
    }

    public int GetStage()
    {
        return stage;
    }

    public int GetHighestStage()
    {
        return highestStage;
    }
}
