using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace TileGridEditor
{
    public class TileGrid : Grid
    {
        //Variables
        public Grid DynamicGrid;
        public Image[,] images;

        public ImageSource penImageSource;

        MainWindow main;

        bool imageCheck = false;

        int previousColumnCount = 0;
        int previousRowCount = 0;

        //Start Method
        public void Start(MainWindow instanceWindow, Grid instanceGrid)
        {
            main = instanceWindow;
            DynamicGrid = instanceGrid;
        }

        //Creates Dynamic Grid
        public void CreateGrid(int columns, int rows)
        {
            //Checks if it is Hidden, if so make Visable
            if(DynamicGrid.Visibility == Visibility.Hidden)
            {
                DynamicGrid.ShowGridLines = true;
                DynamicGrid.Visibility = Visibility.Visible;
                main.gridBorder.Visibility = Visibility.Visible;
            }

            //IF there are pre-existing images on the tile grid, if so remove them
            if (imageCheck == true)
            {
                for (int x = 0; x <= previousColumnCount - 1; x++)
                {
                    for (int y = 0; y <= previousRowCount - 1; y++)
                    {
                        if (images[x, y].Source != null)
                        {
                            images[x, y].Source = null;
                        }
                    }
                }
            }

            previousColumnCount = columns;
            previousRowCount = rows;

            //Clears all Definitions
            DynamicGrid.ColumnDefinitions.Clear();
            DynamicGrid.RowDefinitions.Clear();

            //Sets the Width and Height and creates the Column and Row Definitions
            DynamicGrid.Width = (columns * 32);
            DynamicGrid.Height = (rows * 32);

            for (int x = 0; x < columns; x++)
            {
                DynamicGrid.ColumnDefinitions.Add(new ColumnDefinition());
            }

            for (int y = 0; y < rows; y++)
            {
                DynamicGrid.RowDefinitions.Add(new RowDefinition());
            }

            //Creates the Array for the Grid
            imageCheck = false;
            images = null;
            images = new Image[columns, rows];
            for (int x = 0; x < columns; x++)
            {
                for (int y = 0; y < rows; y++)
                {
                    Image image = new Image();
                    Grid.SetColumn(image, x);
                    Grid.SetRow(image, y);

                    DynamicGrid.Children.Add(image);

                    images[x, y] = image;
                }
            }
            imageCheck = true;
        }

        //Resets the Source Image with the New Image
        public void ImageReset(ImageSource source)
        {
            penImageSource = source;
        }

        //Clears the Grid
        public void GridReset()
        {
            //Clears the Image Array
            for (int x = 0; x < DynamicGrid.ColumnDefinitions.Count; x++)
            {
                for (int y = 0; y < DynamicGrid.RowDefinitions.Count; y++)
                {
                    images[x, y].Source = null;
                }
            }

            //Removes the Row and Column Definitions
            for (int y = previousRowCount - 1; y >= 0; y--)
            {
                DynamicGrid.RowDefinitions.RemoveAt(y);
            }

            for (int x = previousColumnCount - 1; x >= 0; x--)
            {
                DynamicGrid.ColumnDefinitions.RemoveAt(x);
            }

            //Resets all Data on Grid and Hides it
            DynamicGrid.Children.Clear();
            DynamicGrid.ShowGridLines = false;
            DynamicGrid.Visibility = Visibility.Hidden;
            main.gridBorder.Visibility = Visibility.Hidden;
        }

        //Handles Using Tool
        public void UseTool(int gridX, int gridY, ImageSource penImage)
        {
            //Checks which Tool is in Use and Use X and Y to Apply
            switch (main.selectedTool)
            {
                case MainWindow.Tool.Pen:
                    if (penImage == null)
                    {
                        break;
                    }
                    else
                    {
                        if (gridX > (DynamicGrid.ColumnDefinitions.Count - 1) || gridY > (DynamicGrid.RowDefinitions.Count - 1))
                        {
                            break;
                        }
                        else
                        {
                            images[gridX, gridY].Source = penImage;
                            break;
                        }
                    }
                    

                case MainWindow.Tool.Eraser:
                    if (gridX > (DynamicGrid.ColumnDefinitions.Count -1) || gridY > (DynamicGrid.RowDefinitions.Count - 1))
                    {
                        break;
                    }
                    else
                    {
                        images[gridX, gridY].Source = null;
                        break;
                    }
            }
        }
    }
}