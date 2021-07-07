using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Pins : MonoBehaviour
{
    const float min = -0.5f;
    const float max = 0.5f;
    bool switchDirections = false;

    // Update is called once per frame
    void Update()
    {
       if(GameManager.Instance.GetScore() >= 300)
       {
            if(transform.position.x >= max) { switchDirections = true; }
            else if(transform.position.x <= min ) { switchDirections = false; }

            if (!switchDirections) { transform.position = new Vector3(transform.position.x + 0.001f, transform.position.y, transform.position.z); }
            else { transform.position = new Vector3(transform.position.x - 0.001f, transform.position.y, transform.position.z); }
       } 
    }
}
