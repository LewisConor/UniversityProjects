using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FPSCounter : MonoBehaviour
{
    [SerializeField] Text fPSCounter;

    // Update is called once per frame
    void Update()
    {
        fPSCounter.text = "FPS: " + ((int)(1.0f / Time.smoothDeltaTime)).ToString();
    }
}
