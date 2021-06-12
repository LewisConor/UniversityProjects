using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class BallControls : MonoBehaviour
{
    [Header("Boolean Checks", order = 0)]
    [SerializeField] bool isNotWall = true;
    [SerializeField] bool wallTimer = false;
    [SerializeField] bool isMoving = false;
    [SerializeField] bool buttonHold = false;
    [SerializeField] bool invertPower = false;

    [Header("Rigidbody Settings", order = 1)]
    [SerializeField] Rigidbody rigidbody;
    [SerializeField] float ballMovementSpeed;
    [SerializeField] float ballMovementThreshold;
    [SerializeField] float ballWallMovementThreshold;

    [Header("Power Settings", order = 2)]
    [SerializeField] float power;
    [SerializeField] float maxPower;
    [SerializeField] float powerScaling;

    [Header("Arrow Settings", order = 3)]
    [SerializeField] GameObject arrow;
    [SerializeField] Vector3 axis;
    [SerializeField] float rotationLeft = -80;
    [SerializeField] float rotationRight = 80;

    [Header("Other Settings", order = 4)]
    [SerializeField] GolfManager golfManager;
    [SerializeField] LevelController levelController;
    [SerializeField] UIManager uiManager;
    [SerializeField] Joystick joystick;
    [SerializeField] Vector3 oldPosition;

    //Misc
    Quaternion zero = new Quaternion(0, 0, 0, 0);

    void Start()
    {
        //Ball Config
        oldPosition = transform.position;

        //Arrow Config
        axis = arrow.transform.up;
        arrow.transform.rotation = new Quaternion(0, 0, 0, 0);
        arrow.transform.position = new Vector3(transform.position.x, transform.position.y, transform.position.z + 2.5f);

        //UI Config
        uiManager.SetMaxPowerSlider(maxPower);
    }

    void Update()
    {
        ballMovementSpeed = rigidbody.velocity.magnitude;

        if (isMoving && isNotWall)
        {
            if (ballMovementSpeed < ballMovementThreshold)
            {
                StopBall();
            }
        }
        else if(isMoving && !isNotWall)
        {
            if (!wallTimer)
            {
                StartCoroutine(BallTimer(2));
            }
        }
        else
        {
            if (joystick.Horizontal <= -.2f)
            {
                arrow.transform.RotateAround(transform.position, axis, rotationLeft * Time.deltaTime);
            }
            else if (joystick.Horizontal >= .2f)
            {
                arrow.transform.RotateAround(transform.position, axis, rotationRight * Time.deltaTime);
            }

            if (buttonHold)
            {
                if (!invertPower)
                {
                    if (power < maxPower)
                    {
                        power += powerScaling;
                    }
                    else if (power >= maxPower)
                    {
                        invertPower = true;
                        power -= powerScaling;
                    }
                }
                else if (invertPower)
                {
                    if (power > 1)
                    {
                        power -= powerScaling;
                    }
                    else if (power <= 1)
                    {
                        power += powerScaling;
                        invertPower = false;
                    }
                }
            }
        }

        uiManager.UpdatePowerSliderValue(power);
    }

    #region Ball Movement
    public void PushBall()
    {
        if (!isMoving)
        {
            uiManager.DisableButton();
            uiManager.DisableJoystick();

            levelController.SwitchCameraToWorld();
            golfManager.AddShot();

            rigidbody.velocity += arrow.transform.forward * power;
            isMoving = true;
        }
    }

    void StopBall()
    {
        rigidbody.constraints = RigidbodyConstraints.FreezeAll;
        rigidbody.constraints = RigidbodyConstraints.None;

        arrow.transform.rotation = zero;
        arrow.transform.position = new Vector3(transform.position.x, transform.position.y, transform.position.z + 2.5f);

        power = 1;
        oldPosition = transform.position;

        levelController.SwitchCameraToArrow();
        uiManager.EnableButton();
        uiManager.EnableJoystick();

        isMoving = false;
    }
    #endregion

    #region Events
    public void OnPointerUp() { buttonHold = false; PushBall(); }
    public void OnPointerDown() { buttonHold = true; }

    void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.tag == "DeathZone")
        {
            transform.SetPositionAndRotation(oldPosition, zero);
            StopBall();
        }
        else if(other.gameObject.tag == "Wall") { isNotWall = false; }
        else if(other.gameObject.tag == "Hole") { golfManager.CalculateScoreWord(); }
    }

    void OnTriggerExit(Collider other)
    {
        if(other.gameObject.tag == "Wall") { isNotWall = true; }
    }
    #endregion

    #region Other Functions
    IEnumerator BallTimer(int timeInput)
    {
        //wallTimer = true;
        int timeLeft = timeInput;

        while (timeLeft > 0)
        {
            yield return new WaitForSeconds(1.0f);
            timeLeft--;
        }

        if (ballMovementSpeed < ballWallMovementThreshold)
        {
            StopBall();
        }

        wallTimer = false;
    }
    #endregion
}