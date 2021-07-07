using UnityEngine;
using UnityEngine.UI;

public class Platform : MonoBehaviour
{
    [SerializeField] Slider slider;

    // Update is called once per frame
    void Update()
    {
        transform.position = new Vector3(slider.value, 0, 0);
    }

    public void Reset()
    {
        transform.position = new Vector3(0, .5f, 0);
        slider.value = 0;
    }
}
