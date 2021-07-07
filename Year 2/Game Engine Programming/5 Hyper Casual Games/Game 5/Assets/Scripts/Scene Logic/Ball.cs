using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class Ball : MonoBehaviour
{
    Rigidbody rb;

    const int min = -2;
    const int max = 2;
    bool switchDirections = false;
    bool ballLaunched = false;

    GameObject button;

    void Start()
    {
        rb = GetComponent<Rigidbody>();
    }

    void Update()
    {
        if (!ballLaunched)
        {
            if(transform.position.x >= max) { switchDirections = true; }
            else if(transform.position.x <= min) { switchDirections = false; }

            if (!switchDirections) { transform.position = new Vector3(transform.position.x + 0.01f, transform.position.y, transform.position.z); }
            else { transform.position = new Vector3(transform.position.x - 0.01f, transform.position.y, transform.position.z); }
        }
    }

    public void LaunchBall() 
    { 
        ballLaunched = true; 
        rb.constraints = RigidbodyConstraints.None; 
        rb.constraints = RigidbodyConstraints.FreezePositionZ; 
        if (button == null) 
        { 
            button = EventSystem.current.currentSelectedGameObject; 
            button.SetActive(false); 
        }
        else
        {
            button.SetActive(false);
        }
    }

    void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.tag == "Death")
        {
            GameManager.Instance.RemoveLife();
            ResetBall();
        }
        else
        {
            GameManager.Instance.AddScore(int.Parse(other.gameObject.name));
            ResetBall();
        }
    }

    void ResetBall()
    {
        transform.position = new Vector3(0, 6, 0);
        rb.constraints = RigidbodyConstraints.FreezePositionY;
        ballLaunched = false;
        button.SetActive(true);
    }
}
