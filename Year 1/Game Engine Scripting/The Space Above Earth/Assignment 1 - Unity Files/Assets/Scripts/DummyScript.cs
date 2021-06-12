using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DummyScript : MonoBehaviour
{
    //
    [SerializeField] GameObject referenceObject;

    public GameObject GetObject()
    {
        return referenceObject;
    }
}
