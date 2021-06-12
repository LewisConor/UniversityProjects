using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SkyBoxMovement : MonoBehaviour
{
    [SerializeField] float speedMultiplier;

    // Update is called once per frame
    void Update()
    {
        //Rotates the Skybox
        RenderSettings.skybox.SetFloat("_Rotation", Time.time * speedMultiplier);
    }
}
