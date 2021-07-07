using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;
using UnityEngine.UI;

public class MainScene : MonoBehaviour
{
    [SerializeField] Text goldText;
    [SerializeField] Text goldPerTapText;
    [SerializeField] Text autoGoldPerSecondText;
    [SerializeField] Text clickerCostText;
    [SerializeField] Text autoClickerCostText;

    void Update()
    {
        goldText.text = String.Format("{0:n0}", GameManager.Instance.GetGold()) + " Gold";
        goldPerTapText.text = "Gold Per Tap: " + String.Format("{0:n0}", GameManager.Instance.GetGoldPerTap()) + " Gold";
        autoGoldPerSecondText.text = "Gold Per Second: " + String.Format("{0:n0}", GameManager.Instance.GetAutoGoldPerSecond()) + " Gold";
        clickerCostText.text = "Upgrade Cost: " + String.Format("{0:n0}", GameManager.Instance.GetClickerCost()) + " Gold";
        autoClickerCostText.text = "Upgrade Cost: " + String.Format("{0:n0}", GameManager.Instance.GetAutoClickerCost()) + " Gold";
    }

    public void AddToGold()
    {
        GameManager.Instance.AddToGold(GameManager.Instance.GetGoldPerTap());
    }

    public void UpgradeClicker()
    {
        if (!(GameManager.Instance.GetGold() < GameManager.Instance.GetClickerCost()))
        {
            GameManager.Instance.SubFromGold(GameManager.Instance.GetClickerCost());
            GameManager.Instance.AddClickerCost();
            GameManager.Instance.AddGoldPerTap();
        }
    }

    public void UpgradeAutoClicker()
    {
        if (!(GameManager.Instance.GetGold() < GameManager.Instance.GetAutoClickerCost()))
        {
            GameManager.Instance.SubFromGold(GameManager.Instance.GetAutoClickerCost());
            GameManager.Instance.AddAutoClickerCost();
            GameManager.Instance.AddAutoGoldPerSecond();
        }
    }
}
