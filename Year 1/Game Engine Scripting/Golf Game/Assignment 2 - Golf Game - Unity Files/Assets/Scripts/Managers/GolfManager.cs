using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GolfManager : MonoBehaviour
{
    [Header("Golf Data", order = 0)]
    [SerializeField] int shots = 0;
    [SerializeField] int par = 0;

    enum GOLF_SCORE_WORDS
    {
        HOLE_IN_ONE,
        ALBERTROSS,
        EAGLE,
        BIRDIE,
        PAR,
        BOGEY,
        DOUBLE_BOGEY,
        TRIPLE_BOGEY,
        OVER,
        NONE
    }

    GOLF_SCORE_WORDS setScoreWord = GOLF_SCORE_WORDS.NONE;

    #region Gets and Sets
    public void AddShot() { shots++; GetComponent<UIManager>().SetShots(); }
    public int GetShots() { return shots; }
    public int GetPar() { return par; }
    #endregion

    #region Other Functions
    public void CalculateScoreWord()
    {
        if(shots < par)
        {
            if(shots == 1) { setScoreWord = GOLF_SCORE_WORDS.HOLE_IN_ONE; }
            else if(shots == 2) { setScoreWord = GOLF_SCORE_WORDS.ALBERTROSS; }
            else if(shots < (par - 2) && shots > 2) { setScoreWord = GOLF_SCORE_WORDS.EAGLE; }
            else if(shots == (par - 1)) { setScoreWord = GOLF_SCORE_WORDS.BIRDIE; }
        }
        else if(shots == par) { setScoreWord = GOLF_SCORE_WORDS.PAR; }
        else if(shots > par)
        {
            if(shots == (par + 1)) { setScoreWord = GOLF_SCORE_WORDS.BOGEY; }
            else if(shots == (par + 2)) { setScoreWord = GOLF_SCORE_WORDS.DOUBLE_BOGEY; }
            else if(shots == (par + 3)) { setScoreWord = GOLF_SCORE_WORDS.TRIPLE_BOGEY; }
            else if(shots > (par + 3)) { setScoreWord = GOLF_SCORE_WORDS.OVER; }
        }

        GameManager.Instance.AddShots(shots);
        GetComponent<UIManager>().DisableUI();
        GetComponent<UIManager>().DisplayGolfScore((int)setScoreWord);
        GetComponent<UIManager>().SetTotal();
    }
    #endregion
}