using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Canvas : MonoBehaviour
{
    [SerializeField] Text scoreText;
    [SerializeField] Text livesText;
    [SerializeField] Ball ball;
    [SerializeField] GameObject deathScreen;
    [SerializeField] Text deathScoreText;

    void Update()
    {
        if(ball.GetLives() != 0)
        {
            scoreText.text = "Score: " + GameManager.Instance.GetScore().ToString();
            livesText.text = "Lives: " + ball.GetLives().ToString();
        }
        else
        {
            deathScreen.SetActive(true);
            deathScoreText.text = "Score: " + GameManager.Instance.GetScore().ToString();
        }
    }

    public void Restart() { GameManager.Instance.SceneChanger(1); }
    public void MainMenu() { GameManager.Instance.SceneChanger(0); }
}
