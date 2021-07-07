using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Ball : MonoBehaviour
{
    Rigidbody rb;

    CanvasManager cm;

    [SerializeField] float xMove = 0.0f;
    [SerializeField] int xMin = -5;
    [SerializeField] int xMax = 5;

    [Header("Ball Foward Speed", order = 0)]
    [SerializeField] int power = 1;
    [SerializeField] int minPower = 50;
    [SerializeField] int maxPower = 100;
    [SerializeField] int powerScaling = 1;

    [Header("Ball Up Speed", order = 0)]
    [SerializeField] int upPower = 1;

    bool isHeld = false;
    bool powerReverse = false;
    bool xReverse = false;
    bool isMoving = false;

    bool timerRunning = false;

    Vector3 ballStartPos;
    Quaternion ballStartRot;

    void Start()
    {
        rb = GetComponent<Rigidbody>();

        cm = GameObject.FindGameObjectWithTag("UI").GetComponent<CanvasManager>();

        cm.SetSliderMinMax(minPower, maxPower);

        ballStartPos = transform.position;
        ballStartRot = transform.rotation;
    }

    void Update()
    {
        switch (GameManager.Instance.GetStage())
        {
            case 1:
            {
                xMove = 0;
                break;
            }
            case 2:
            {
                xMove = 0.05f;
                break;
            }
            case 3:
            {
                xMove = 0.1f;
                break;
            }
            case 4:
            {
                xMove = 0.25f;
                break;
            }
            case 5:
            {
                xMove = 0.5f;
                break;
            }
        }


        if (!isMoving)
        {
            if (Input.GetMouseButtonDown(0))
            {
                isHeld = true;
            }

            if (Input.GetMouseButtonUp(0))
            {
                rb.AddForce(new Vector3(0, upPower, (1 + power)), ForceMode.Acceleration);
                isMoving = true;
                isHeld = false;
                power = 0;
            }

            if (isHeld)
            {
                if (power >= maxPower)
                {
                    powerReverse = true;
                }
                if (power <= minPower)
                {
                    powerReverse = false;
                }

                if (!powerReverse)
                {
                    power += powerScaling;
                }
                else
                {
                    power -= powerScaling;
                }

                cm.SetSlider(power);
            }

            if (transform.position.x >= xMax)
            {
                xReverse = true;
            }

            if (transform.position.x <= xMin)
            {
                xReverse = false;
            }

            if (!xReverse)
            {
                transform.position = new Vector3(transform.position.x + xMove, transform.position.y, transform.position.z);
            }
            else
            {
                transform.position = new Vector3(transform.position.x - xMove, transform.position.y, transform.position.z);
            }
        }
        else
        {
            if (!timerRunning)
            {
                timerRunning = true;
                StartCoroutine(TimerTillBallReset(5));
            }
        }
    }

    public void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Goal")
        {
            print("Goal");
            GameManager.Instance.AddScore();
        }
    }


    IEnumerator TimerTillBallReset(int timeInput)
    {        
        int timer = timeInput;

        while(timer > 0)
        {
            yield return new WaitForSeconds(1.0f);
            timer--;
        }

        transform.position = ballStartPos;
        transform.rotation = ballStartRot;

        rb.isKinematic = true;
        isMoving = false;
        rb.isKinematic = false;

        timerRunning = false;
    }
}
