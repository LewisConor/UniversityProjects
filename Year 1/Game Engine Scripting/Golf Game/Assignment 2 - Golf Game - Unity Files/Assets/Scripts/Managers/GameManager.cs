using UnityEngine;
using UnityEngine.Audio;
using UnityEngine.SceneManagement;

public class GameManager : Singleton<GameManager>
{
    [Header("Game Variables", order = 0)]
    [SerializeField] int currentScene = 0;
    [SerializeField] AudioMixer audioMixer;
    [SerializeField] AudioSource audioSource;

    [Header("Player Stats", order = 1)]
    [SerializeField] string username;
    [SerializeField] int score = 0;

    protected GameManager() { }

    #region Startup
    void Awake()
    {
        DontDestroyOnLoad(this);

        if (PlayerPrefs.HasKey("volume"))
        {
            float volume = PlayerPrefs.GetFloat("volume");
            Debug.Log("Volume Found, Volume at: " + volume);
            audioMixer.SetFloat("volume", volume);
        }
        else
        {
            Debug.LogWarning("Volume not Found, Setting Default Values");
            audioMixer.SetFloat("volume", 0.0f);
            PlayerPrefs.SetFloat("volume", 0.0f);
            PlayerPrefs.Save();
        }

        if (PlayerPrefs.HasKey("username"))
        {
            username = PlayerPrefs.GetString("username");
        }

        SceneManager.LoadSceneAsync(1);
        currentScene++;
        audioSource.Play();
    }
    #endregion 

    #region Audio
    public void SetVolume(float volume)
    {
        audioMixer.SetFloat("volume", volume);
        print("Volume Set");
    }

    public float ReturnVolume()
    {
        float volume;
        audioMixer.GetFloat("volume", out volume);
        print("Volume: " + volume);

        return volume;
    }
    #endregion

    #region Scene Management
    public void BackToMainMenu() { SceneManager.LoadSceneAsync(1); currentScene = 1; }
    public void NextScene() { currentScene++; SceneManager.LoadSceneAsync(currentScene); }
    public int GetCurrentScene() { return currentScene; }
    #endregion

    #region Other Functions
    public void AddShots(int shots) { score += shots; }
    public int GetScore() { return score; }
    #endregion
}
