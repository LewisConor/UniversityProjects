using UnityEngine;
using UnityEditor;

[CustomEditor(typeof(DSAlgorithm))]
public class DSAEditor : Editor
{
    DSAlgorithm dSAlgorithm;

    private void OnEnable()
    {
        dSAlgorithm = (DSAlgorithm)target;
    }

    public override void OnInspectorGUI()
    {
        DrawDefaultInspector();
        if(GUILayout.Button("Generate Map")) { dSAlgorithm.GenerateMap(); }
        if(GUILayout.Button("Generate Colour")) { dSAlgorithm.GenerateColour(); }
    }
}
