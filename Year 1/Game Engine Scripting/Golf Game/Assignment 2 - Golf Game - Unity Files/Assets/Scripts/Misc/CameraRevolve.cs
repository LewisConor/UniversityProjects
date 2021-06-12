using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraRevolve : MonoBehaviour
{
    [Header("Camera Settings", order = 0)]
    [SerializeField] private Transform target;
    [SerializeField] private int speed;

    // Update is called once per frame
    void Update()
    {
        if (GetComponent<Camera>().enabled)
        {
            transform.LookAt(target);
            transform.Translate(Vector3.right * Time.deltaTime * speed);
        }
    }
}
