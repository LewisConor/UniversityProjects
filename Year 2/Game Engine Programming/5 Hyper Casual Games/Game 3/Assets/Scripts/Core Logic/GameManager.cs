using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    static GameManager m_instance;
    public static GameManager Instance { get { return m_instance; } }
    
    long gold;
    long goldPerTap;
    long clickerCost;
    long autoGoldPerSecond;
    long autoClickerCost;

    void Awake()
    {
        if(m_instance == null)
        {
            DontDestroyOnLoad(this);
            m_instance = this;
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        LoadData();
        InvokeRepeating("AutoClicker", 0.0f, 1.0f);
    }

    void AutoClicker() { if (SceneManager.GetActiveScene().buildIndex == 1) { gold += autoGoldPerSecond; } }

    void OnApplicationQuit()
    {
        SaveData();
    }

    public void SaveData()
    {
        int[] goldSplit = longToInt(gold);
        PlayerPrefs.SetInt("gold1", goldSplit[0]);
        PlayerPrefs.SetInt("gold2", goldSplit[1]);

        int[] gptSplit = longToInt(goldPerTap);
        PlayerPrefs.SetInt("goldPerTap1", gptSplit[0]);
        PlayerPrefs.SetInt("goldPerTap2", gptSplit[1]);

        int[] ccSplit = longToInt(clickerCost);
        PlayerPrefs.SetInt("clickerCost1", ccSplit[0]);
        PlayerPrefs.SetInt("clickerCos2", ccSplit[1]);

        int[] agptSplit = longToInt(autoGoldPerSecond);
        PlayerPrefs.SetInt("autoGoldPerSecond1", agptSplit[0]);
        PlayerPrefs.SetInt("autoGoldPerSecond2", agptSplit[1]);

        int[] accSplit = longToInt(autoClickerCost);
        PlayerPrefs.SetInt("autoClickerCost1", accSplit[0]);
        PlayerPrefs.SetInt("autoClickerCost2", accSplit[1]);
    }

    void LoadData()
    {
        int[] goldSplit = { PlayerPrefs.GetInt("gold1"), PlayerPrefs.GetInt("gold2") };
        gold = intToLong(goldSplit);

        int[] gptSplit = { PlayerPrefs.GetInt("goldPerTap1"), PlayerPrefs.GetInt("goldPerTap2") };
        goldPerTap = intToLong(gptSplit);

        if (goldPerTap == 0)
        {
            goldPerTap = 1;
        }

        int[] ccSplit = { PlayerPrefs.GetInt("clickerCost1"), PlayerPrefs.GetInt("clickerCost2") };
        clickerCost = intToLong(ccSplit);

        if (clickerCost == 0)
        {
            clickerCost = 10;
        }

        int[] agptSplit = { PlayerPrefs.GetInt("autoGoldPerSecond1"), PlayerPrefs.GetInt("autoGoldPerSecond2") };
        autoGoldPerSecond = intToLong(agptSplit);

        int[] accSplit = { PlayerPrefs.GetInt("autoClickerCost1"), PlayerPrefs.GetInt("autoClickerCost2") };
        autoClickerCost = intToLong(accSplit);

        if (autoClickerCost == 0)
        {
            autoClickerCost = 100;
        }
    }

    public void SceneChanger(int sceneID)
    {
        SceneManager.LoadScene(sceneID);
    }

    public long GetGold() { return gold; }
    public long GetGoldPerTap() { return goldPerTap; }
    public long GetClickerCost() { return clickerCost; }
    public long GetAutoGoldPerSecond() { return autoGoldPerSecond; }
    public long GetAutoClickerCost() { return autoClickerCost; }

    public void AddToGold(long addGold) { gold += addGold; }
    public void SubFromGold(long subGold) { gold -= subGold; }
    public void AddGoldPerTap() { goldPerTap += 2; }
    public void AddClickerCost() { clickerCost += (3 * goldPerTap); }
    public void AddAutoGoldPerSecond() { autoGoldPerSecond += 3; }
    public void AddAutoClickerCost() { if (autoGoldPerSecond == 0) { autoClickerCost += 9; } else { autoClickerCost += (9 * autoGoldPerSecond); } }

    int[] longToInt(long a_long)
    {
        int i1 = (int)(a_long & uint.MaxValue);
        int i2 = (int)(a_long >> 32);
        return new int[] { i1, i2 };
    }

    long intToLong(int[] a_i)
    {
        long l = a_i[1];
        l = l << 32;
        l = l | (uint)a_i[0];
        return l;
    }

    
}
