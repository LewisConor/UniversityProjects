using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class Sudoku : MonoBehaviour
{
    [Header("Sudoku Components", order = 0)]
    [SerializeField] string selectedCell = "01";
    [SerializeField] Transform parent;
    [SerializeField] Text timerText;
    [SerializeField] Text mistakesText;

    [Header("Finished Components", order = 1)]
    [SerializeField] GameObject finishedPanel;
    [SerializeField] Text timeTookText;

    int[,] solvedSudokuGrid = new int[9, 9];
    int[,] sudokuGrid = new int[9, 9];
    bool[,] mistakesSudokuGrid = new bool[9, 9];
    GameObject[,] sudokuGridObject = new GameObject[9, 9];

    float secondsCount = 0.0f;
    int minutesCount = 0;
    bool finished = false;

    // Start is called before the first frame update
    void Start()
    {
        Random.InitState(System.Guid.NewGuid().GetHashCode());

        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                solvedSudokuGrid[i, j] = (i * 3 + i / 3 + j) % 9 + 1;
                sudokuGrid[i, j] = 0;
                mistakesSudokuGrid[i, j] = false;
            }
        }

        for (int repeat = 0; repeat < 10; repeat++)
        {
            ChangeTwoCell(solvedSudokuGrid, Random.Range(1, 10), Random.Range(1, 10));
        }

        int unMaskRand = Random.Range(30, 40);

        for (int i = 0; i < 80; ++i)
        {
            int rand1 = Random.Range(0, 9);
            int rand2 = Random.Range(0, 9);
            sudokuGrid[rand1, rand2] = solvedSudokuGrid[rand1, rand2];
        }

        foreach (Transform child in parent)
        {
            foreach (Transform subChild in child)
            {
                sudokuGridObject[int.Parse(child.name), int.Parse(subChild.name)] = subChild.gameObject;

                if (sudokuGrid[int.Parse(child.name), int.Parse(subChild.name)] == 0)
                {
                    subChild.GetChild(0).gameObject.GetComponent<Text>().text = "";
                }
                else
                {
                    subChild.GetChild(0).gameObject.GetComponent<Text>().text = sudokuGrid[int.Parse(child.name), int.Parse(subChild.name)].ToString();
                    sudokuGridObject[int.Parse(child.name), int.Parse(subChild.name)].GetComponent<Button>().interactable = false;
                }
            }
        }
    }

    void Update()
    {
        if(finished != true)
        {
            int finishedCounter = 0;
            for (int i = 0; i < 9; ++i)
            {
                for(int j = 0; j < 9; ++j)
                {
                    if(sudokuGrid[i,j] == solvedSudokuGrid[i, j])
                    {
                        finishedCounter++;
                    }
                }
            }

            if (finishedCounter == 81)
            {
                finished = true;
            }
        }

        if (finished)
        {
            finishedPanel.SetActive(true);
            timeTookText.text = "Time Taken: " + minutesCount.ToString("00") + ":" + secondsCount.ToString("00");
        }
        else
        {
            UpdateTimerUI();

            int mistakeCount = 0;

            for (int i = 0; i < 9; ++i)
            {
                for (int j = 0; j < 9; j++)
                {
                    if (mistakesSudokuGrid[i, j])
                    {
                        mistakeCount++;
                    }
                }
            }

            mistakesText.text = "Mistakes: " + mistakeCount.ToString();
        }

        
    }

    public void SelectCell() { selectedCell = EventSystem.current.currentSelectedGameObject.transform.parent.name + EventSystem.current.currentSelectedGameObject.name; }

    public void ChangeCell(int number)
    {
        sudokuGrid[int.Parse(selectedCell[0].ToString()), int.Parse(selectedCell[1].ToString())] = number;
        sudokuGridObject[int.Parse(selectedCell[0].ToString()), int.Parse(selectedCell[1].ToString())].transform.GetChild(0).GetComponent<Text>().text = number.ToString();

        if(number != solvedSudokuGrid[int.Parse(selectedCell[0].ToString()), int.Parse(selectedCell[1].ToString())])
        {
            mistakesSudokuGrid[int.Parse(selectedCell[0].ToString()), int.Parse(selectedCell[1].ToString())] = true;
        }
        else
        {
            if (mistakesSudokuGrid[int.Parse(selectedCell[0].ToString()), int.Parse(selectedCell[1].ToString())])
            {
                mistakesSudokuGrid[int.Parse(selectedCell[0].ToString()), int.Parse(selectedCell[1].ToString())] = false;
            }
        }
    }

    void ChangeTwoCell(int[,] grid, int findValue1, int findValue2)
    {
        int xParm1, yParm1, xParm2, yParm2;
        xParm1 = yParm1 = xParm2 = yParm2 = 0;
        for (int i = 0; i < 9; i += 3)
        {
            for (int k = 0; k < 9; k += 3)
            {
                for (int j = 0; j < 3; j++)
                {
                    for (int z = 0; z < 3; z++)
                    {
                        if (grid[i + j, k + z] == findValue1)
                        {
                            xParm1 = i + j;
                            yParm1 = k + z;

                        }
                        if (grid[i + j, k + z] == findValue2)
                        {
                            xParm2 = i + j;
                            yParm2 = k + z;

                        }
                    }
                }
                grid[xParm1, yParm1] = findValue2;
                grid[xParm2, yParm2] = findValue1;
            }
        }
    }

    
    void UpdateTimerUI()
    {
        //set timer UI
        secondsCount += Time.deltaTime;
        timerText.text = "Time Spent: " + minutesCount.ToString("00") + ":" + secondsCount.ToString("00");
        if (secondsCount >= 60)
        {
            minutesCount++;
            secondsCount = 0;
        }
    }

    public void Restart()
    {
        GameManager.Instance.SceneChanger(1);
    }

    public void MainMenu()
    {
        GameManager.Instance.SceneChanger(0);
    }
}