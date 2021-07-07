using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ball : MonoBehaviour
{
    int lives = 5;
    public int GetLives() { return lives; }


    Rigidbody2D rb;
    bool ballLaunched = false;

    GameObject[] bricks;
    int numOfBricksActive;

    [SerializeField] int launchSpeed = 1;
    [SerializeField] GameObject platform;
    [SerializeField] Vector3 startPos;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        transform.position = startPos;
        rb.velocity = Vector2.zero;

        bricks = GameObject.FindGameObjectsWithTag("Block");
        numOfBricksActive = bricks.Length;
    }

    // Update is called once per frame
    void Update()
    {
        if (!ballLaunched)
        {
            transform.position = new Vector3(platform.transform.position.x, .2f, 0);
        }

        if(numOfBricksActive == 0)
        {
            for (int i = 0; i < bricks.Length; ++i)
            {
                bricks[i].SetActive(true);
                numOfBricksActive++;
            }

            lives += 5;
        }
    }

    public void LaunchBall() { if (!ballLaunched) { /*rb.velocity = new Vector2(Random.Range(-3.0f, 3.0f), 4);*/ rb.AddForce(Vector2.up * launchSpeed); ballLaunched = true; } }

    void OnTriggerEnter2D(Collider2D other)
    {
        lives--;
        platform.GetComponent<Platform>().Reset();
        ballLaunched = false;
        transform.position = startPos;
        rb.velocity = Vector2.zero;
    }

    void OnCollisionExit2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Block")
        {
            if (collision.gameObject.GetComponent<Block>().GetNumOfHits() == 0)
            {
                collision.gameObject.SetActive(false);
                numOfBricksActive--;
                GameManager.Instance.AddScore();
            }
            else
            {
                collision.gameObject.GetComponent<Block>().SubOne();
            }

            GameManager.Instance.AddScore();
        }
    }
}
