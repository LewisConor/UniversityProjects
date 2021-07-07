using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEditor;

public class EditorStart : Editor
{
    [RuntimeInitializeOnLoadMethod(RuntimeInitializeLoadType.BeforeSceneLoad)]
    static void MainMenuStart()
    {
        SceneManager.LoadScene(0);
    }

    [MenuItem("Gold/Reset")]
    static void ResetStats()
    {
        PlayerPrefs.SetInt("gold1", 0);
        PlayerPrefs.SetInt("gold2", 0);
        PlayerPrefs.SetInt("goldPerTap1", 0);
        PlayerPrefs.SetInt("goldPerTap2", 0);
        PlayerPrefs.SetInt("clickerCost1", 0);
        PlayerPrefs.SetInt("clickerCost2", 0);
        PlayerPrefs.SetInt("autoGoldPerSecond1", 0);
        PlayerPrefs.SetInt("autoGoldPerSecond2", 0);
        PlayerPrefs.SetInt("autoClickerCost1", 0);
        PlayerPrefs.SetInt("autoClickerCost2", 0);
    }
}
