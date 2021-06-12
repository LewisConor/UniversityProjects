using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraFollow : MonoBehaviour
{
    [Header("Camera Settings", order = 0)]
    [SerializeField] Transform target;
    [SerializeField] int distance;
    [SerializeField] int height;

    // Update is called once per frame
    void Update()
    {
        transform.position = new Vector3(target.position.x, target.position.y + height, target.position.z - distance);
    }
}
