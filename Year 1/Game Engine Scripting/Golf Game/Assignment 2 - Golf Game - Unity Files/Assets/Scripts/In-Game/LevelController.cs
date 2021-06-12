using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LevelController : MonoBehaviour
{
    [Header("Cameras", order = 0)]
    [SerializeField] Camera mainCamera;
    [SerializeField] Camera arrowCamera;
    [SerializeField] Camera cineCamera;

    [Header("Other", order = 1)]
    [SerializeField] GameObject arrow;
    [SerializeField] int cinematicTimer;
    
    void Start()
    {
        StartCoroutine(LevelStartup(cinematicTimer));
    }

    #region Camera Controller
    public void SwitchCameraToArrow() { arrow.SetActive(true); arrowCamera.enabled = true; mainCamera.enabled = false; }
    public void SwitchCameraToWorld() { arrow.SetActive(false); arrowCamera.enabled = false; mainCamera.enabled = true; }
    #endregion

    #region Other Functions
    IEnumerator LevelStartup(int timeInput)
    {
        int timeLeft = timeInput;

        while (timeLeft > 0)
        {
            yield return new WaitForSeconds(1.0f);
            timeLeft--;
        }

        GetComponent<UIManager>().EnableUI();
        cineCamera.enabled = false;
        arrowCamera.enabled = true;
        arrow.SetActive(true);
    }
    #endregion
}