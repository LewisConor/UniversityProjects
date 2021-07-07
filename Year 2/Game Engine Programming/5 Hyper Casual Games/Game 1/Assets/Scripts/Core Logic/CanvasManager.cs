using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CanvasManager : MonoBehaviour
{
    [SerializeField] Text score;

    [SerializeField] Text stage;
    [SerializeField] Slider powerBar;

    void Update()
    {
        score.text = "Score: " + GameManager.Instance.GetScore();
        stage.text = "Stage: " + GameManager.Instance.GetStage();
    }

    public Slider GetSlider()
    {
        return powerBar;
    }

    public void SetSliderMinMax(int min, int max)
    {
        powerBar.minValue = min;
        powerBar.maxValue = max;
    }

    public void SetSlider(int value)
    {
        powerBar.value = value;
    }

    public Text GetText()
    {
        return score;
    }

    public void GiveUp()
    {
        GameManager.Instance.SceneChanger(0);
    }
}
