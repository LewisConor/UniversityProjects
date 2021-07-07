using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Block : MonoBehaviour
{
    [SerializeField] int maxHits;
    int numOfHits = 0;

    // Start is called before the first frame update
    void Start()
    {
        maxHits = Random.Range(1, 3);
        numOfHits = maxHits;
        GetComponent<Renderer>().material.color = new Color(Random.Range(0.0f, 1.0f), Random.Range(0.0f, 1.0f), Random.Range(0.0f, 1.0f), 1);
    }

    public int GetNumOfHits() { return numOfHits; }
    public void SubOne() { numOfHits--; GetComponent<Renderer>().material.color = new Color(Random.Range(0.0f, 1.0f), Random.Range(0.0f, 1.0f), Random.Range(0.0f, 1.0f), 1); }
}
