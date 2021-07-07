using UnityEngine;
using UnityEngine.UI;

public class Canvas : MonoBehaviour
{
    [SerializeField] GameObject mainScreen;
    [SerializeField] Text livesText;
    [SerializeField] Text mainScoreText;

    [SerializeField] GameObject deathScreen;
    [SerializeField] Text deathScoreText;

    void Update()
    {
        if (mainScreen.activeSelf)
        {
            livesText.text = "Lives: " + GameManager.Instance.GetLives().ToString();
            mainScoreText.text = "Score: " + GameManager.Instance.GetScore().ToString();

            if (GameManager.Instance.GetLives() == 0)
            {
                mainScreen.SetActive(false);
                deathScreen.SetActive(true);
            }
        }
        else
        {
            deathScoreText.text = "Score: " + GameManager.Instance.GetScore().ToString();
        }
    }

    public void Restart() { GameManager.Instance.SceneChanger(1); GameManager.Instance.ResetData(); }
    public void MainMenu() { GameManager.Instance.SceneChanger(0); GameManager.Instance.ResetData(); }
}
