using System.Linq;
using UnityEngine;

public class DSAlgorithm : MonoBehaviour
{
    [System.Serializable]
    public struct ColourLayer
    {
        //Identifiers
        public string name;
        public int index;

        //Heights
        [Range(0.0f, 0.9f)]
        public float minHeight;

        [Range(0.0f, 1.0f)]
        public float maxHeight;

        //Colour
        public Color colour;
    }

    //Terrain Variables
    TerrainData terrainData;
    int terrainSize;
    float[,] mapHeights;

    //Modifiable Terrain Variables
    [SerializeField] bool randomCorners = false;
    [SerializeField] [Range(0.9f, 1.1f, order = 0)] float mapRoughness = 1.0f;
    [SerializeField] [Range(0, 512, order = 1)] int seed = 0;

    //Colour Variables
    float[,,] splatMapData;
    [SerializeField] ColourLayer[] colourLayers;

    public void GenerateMap()
    {
        //Gets the Terrain Data and Gets the Terrain Size
        terrainData = GetComponent<Terrain>().terrainData;
        terrainSize = terrainData.heightmapResolution;

        //Start a Random Generator State with a Seed
        Random.InitState(seed);

        //Randomise the First Corners if True
        if (randomCorners)
        {
            //Initalise a new 2D Array
            mapHeights = new float[terrainSize, terrainSize];

            mapHeights[0, 0] = Random.value;
            mapHeights[terrainSize - 1, 0] = Random.value;
            mapHeights[0, terrainSize - 1] = Random.value;
            mapHeights[terrainSize - 1, terrainSize - 1] = Random.value;

            terrainData.SetHeights(0, 0, mapHeights);
        }

        mapHeights = new float[terrainSize, terrainSize];

        float average, range = 0.5f;
        int sideLength, halfSide, x, y;

        //Loop while we have a Side Length more than 1
        for (sideLength = terrainSize - 1; sideLength > 1; sideLength /= 2)
        {
            halfSide = sideLength / 2;

            //The Diamond Step
            for (x = 0; x < terrainSize - 1; x += sideLength)
            {
                for (y = 0; y < terrainSize - 1; y += sideLength)
                {
                    //Get the Corner Average
                    average = mapHeights[x, y];
                    average += mapHeights[x + sideLength, y];
                    average += mapHeights[x, y + sideLength];
                    average += mapHeights[x + sideLength, y + sideLength];
                    average /= 4.0f;

                    //Offset the Average Value by a Random Value;
                    average += (Random.value * (range * 2.0f)) - range;

                    //Apply the Average to the 2D Array
                    mapHeights[x + halfSide, y + halfSide] = average;
                }
            }

            //The Square Step
            for (x = 0; x < terrainSize - 1; x += halfSide)
            {
                for (y = (x + halfSide) % sideLength; y < terrainSize - 1; y += sideLength)
                {
                    //Get the Corner Average
                    average = mapHeights[(x - halfSide + terrainSize - 1) % (terrainSize - 1), y];
                    average += mapHeights[(x + halfSide) % (terrainSize - 1), y];
                    average += mapHeights[x, (y + halfSide) % (terrainSize - 1)];
                    average += mapHeights[x, (y - halfSide + terrainSize - 1) % (terrainSize - 1)];
                    average /= 4.0f;

                    //Offset the Average by a Random Value
                    average += (Random.value * (range * 2.0f)) - range;

                    //Apply the Average to the 2D Array
                    mapHeights[x, y] = average;

                    //If on the Edge, set the height on Opposite Corners
                    if (x == 0)
                    {
                        mapHeights[terrainSize - 1, y] = average;
                    }

                    if (y == 0)
                    {
                        mapHeights[x, terrainSize - 1] = average;
                    }
                }
            }

            //Lower the Random Value Range
            range -= range * 0.5f * mapRoughness;
        }

        //Apply the Map Heights to Terrain
        terrainData.SetHeights(0, 0, mapHeights);
    }

    //Add a new Terrain Layer
    void AddNewLayer(TerrainLayer terrainLayer)
    {
        //Take old Layer Array
        TerrainLayer[] oldLayers = terrainData.terrainLayers;

        //Make new Layer Array with +1
        TerrainLayer[] newLayers = new TerrainLayer[oldLayers.Length + 1];

        //Copy old array into new Array
        System.Array.Copy(oldLayers, newLayers, oldLayers.Length);

        //Add Layer to new Array
        newLayers[oldLayers.Length] = terrainLayer;

        //Set new Array to Layers
        terrainData.terrainLayers = newLayers;
    }

    //Converts Colour into Texture2D
    Texture2D ConvertColour(Color colour, int width, int height)
    {
        //Make new 2D Texture with Point Filter Mode and Clamp Wrap Mode
        Texture2D texture = new Texture2D(width, height);
        texture.filterMode = FilterMode.Point;
        texture.wrapMode = TextureWrapMode.Clamp;

        //Array of Colour Pixels
        Color[] colourMap = texture.GetPixels();

        //Adds Colour to cach Pixel
        for (int i = 0; i < colourMap.Length; ++i)
        {
            colourMap[i] = colour;
        }

        //Sets the Pixels from Array and Applies to Texture
        texture.SetPixels(colourMap);
        texture.Apply();

        //Return this Texture
        return texture;
    }

    //Gets the Max Height of our Terrain
    private float GetMaxHeight(TerrainData terrainData, int heightmapResolution)
    {
        float maxHeight = 0f;

        //Loop till Highest Height has been found
        for (int x = 0; x < heightmapResolution; x++)
        {
            for (int y = 0; y < heightmapResolution; y++)
            {
                if (terrainData.GetHeight(x, y) > maxHeight)
                {
                    maxHeight = terrainData.GetHeight(x, y);
                }
            }
        }

        //Return Max Height
        return maxHeight;
    }

    public void GenerateColour()
    {
        if (!terrainData) { terrainData = GetComponent<Terrain>().terrainData; }

        //Clears old Layers
        if (terrainData.terrainLayers.Length > 0)
        {
            terrainData.terrainLayers = null;
        }

        //Checks the Colour Array for Colours to add to Layers
        for (int i = 0; i < colourLayers.Length; ++i)
        {
            //New Layer
            TerrainLayer terrainLayer = new TerrainLayer();

            //Convert Colour into Texture2D
            terrainLayer.diffuseTexture = ConvertColour(colourLayers[i].colour, 512, 512);

            //Add a new Terrain
            AddNewLayer(terrainLayer);
        }

        //Initalise new 3D Array
        splatMapData = new float[terrainData.alphamapWidth, terrainData.alphamapHeight, terrainData.alphamapLayers];

        float maxHeight = GetMaxHeight(terrainData, terrainData.heightmapResolution);

        for (int x = 0; x < terrainData.alphamapWidth; ++x)
        {
            for (int y = 0; y < terrainData.alphamapHeight; ++y)
            {
                // Normalise the X and Y coordinates between 0 and 1
                float y_01 = y / (float)terrainData.alphamapHeight;
                float x_01 = x / (float)terrainData.alphamapWidth;

                //Get the height from the Y and X of the Heightmap which requires a Int value
                float height = terrainData.GetHeight(Mathf.RoundToInt(y_01 * terrainData.heightmapResolution), Mathf.RoundToInt(x_01 * terrainData.heightmapResolution));

                //Normalise the Height by dividing it by Max Height
                float normHeight = height / maxHeight;

                // Setup an array to record the mix of texture weights at this point
                float[] splatWeights = new float[terrainData.alphamapLayers];

                for (int i = 0; i < colourLayers.Length; i++)
                {
                    //Compares the Normalised Height vs the Height defined
                    if (normHeight >= colourLayers[i].minHeight && normHeight <= colourLayers[i].maxHeight)
                    {
                        splatWeights[colourLayers[i].index] = 1.0f;
                    }
                }

                // Sum of all textures weights must add to 1, so calculate normalization factor from sum of weights
                float z = splatWeights.Sum();

                // Loop through each terrain texture
                for (int i = 0; i < terrainData.alphamapLayers; i++)
                {
                    // Normalize so that sum of all texture weights = 1
                    splatWeights[i] /= z;

                    // Assign this point to the splatmap array
                    splatMapData[x, y, i] = splatWeights[i];
                }
            }
        }

        //Apply Splat Map Data to Alphamaps
        terrainData.SetAlphamaps(0, 0, splatMapData);
    }
}