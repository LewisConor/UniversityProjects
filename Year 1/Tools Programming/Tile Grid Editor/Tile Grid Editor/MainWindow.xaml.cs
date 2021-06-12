using Microsoft.Win32;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace TileGridEditor
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        //Variables
        public enum Tool { Pen, Eraser }
        public Tool selectedTool = Tool.Pen;

        public TileGrid tileGrid = new TileGrid();

        bool penIsDown = false;

        public bool levelOpen = false;

        public string USRDIR;
        public string LVLDIR;
        public string SPRITEDIR;
        public string CUSTOMSPRITEDIR;
        public string LVLNAME;

        public string[,] XYImage;

        public List<string> tileMapPaths = new List<string>();
        public List<string> tileMapNames = new List<string>();

        //Window Initalizer plus Extra Logic
        public MainWindow()
        {
            InitializeComponent();
            DirectoryCheck();

            //Passes Main Grid Data to the Grid Class
            tileGrid.Start(this, DynamicGrid);

            //Adds Mouse Functions to it's assigning Events on Grid
            DynamicGrid.MouseDown += OnMouseDown;
            DynamicGrid.MouseUp += OnMouseUp;
            DynamicGrid.MouseMove += OnMouseMove;

            //Sprite Menu Pass Though and Assigning Function to Event
            spriteMenu.mainWindow = this;
            spriteMenu.SelectedItem += OnSelectedItem;
        }

        //Checks if the Data Directory Exists
        void DirectoryCheck()
        {
            USRDIR = (Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments) + @"\Grid Editor");
            if(!Directory.Exists(USRDIR))
            {
                Directory.CreateDirectory(USRDIR);
            }
        }

        //Handles New Map Window
        private void HandleNew(object sender, RoutedEventArgs e)
        {
            //Checks if there is a Level Open, if so Ask if they want to Save Current Level, else Open New Window
            if (levelOpen)
            {
                MessageBoxResult result = MessageBox.Show("Save Level before Creating new Level?", "Save Level", MessageBoxButton.YesNoCancel, MessageBoxImage.Question);

                if(result == MessageBoxResult.Yes)
                {
                    HandleSaveByCode();
                    HandleLevelCloseByCode();
                    NewMap newMap = new NewMap();
                    newMap.ShowDialog();
                }
                else if(result == MessageBoxResult.No)
                {
                    HandleLevelCloseByCode();
                    NewMap newMap = new NewMap();
                    newMap.ShowDialog();
                }
            }
            else
            {
                NewMap newMap = new NewMap();
                newMap.ShowDialog();
            }
        }

        //Handles Saving to File by Menu Item
        private void HandleSave(object sender, RoutedEventArgs e)
        {
            //Gathers Data from Level Grid
            int numberOfX = DynamicGrid.ColumnDefinitions.Count;
            int numberOfY = DynamicGrid.RowDefinitions.Count;

            //Creates Data Array for Saving
            GridData[] AllGridData = new GridData[numberOfX * numberOfY];
            SpriteData[] AllSpriteData = new SpriteData[spriteMenu.tabController.Items.Count];

            //Begins Creating Grid Data for Each X and Y of Level Grid
            int counter = 0;
            for (int x = 0; x < numberOfX; x++)
            {
                for (int y = 0; y < numberOfY; y++)
                {
                    GridData gridData = new GridData
                    {
                        numOfX = numberOfX,
                        numOfY = numberOfY,
                        XPos = x,
                        YPos = y,
                        SpriteFilePath = XYImage[x, y]
                    };
                    AllGridData[counter] = gridData;
                    counter++;
                }
            }

            //Begins Creating Sprite Data for Each Sprite Menu Tab
            for (int i = 0; i < spriteMenu.tabController.Items.Count; i++)
            {
                SpriteData spriteData = new SpriteData
                {
                    tileMapName = tileMapNames[i],
                    tileMapPath = tileMapPaths[i]
                };
                AllSpriteData[i] = spriteData;
            }

            //If a Save File Exists then Remove all Data and Re-Write Data through JSON Serialiser
            if (File.Exists(Path.Combine(LVLDIR, LVLNAME) + ".json"))
            {
                File.WriteAllText(Path.Combine(LVLDIR, LVLNAME) + ".json", string.Empty);

                FileStream fileStream = new FileStream(Path.Combine(LVLDIR, LVLNAME) + ".json", FileMode.Open);
                StreamWriter streamWriter = new StreamWriter(fileStream);

                streamWriter.WriteLine(JsonConvert.SerializeObject(AllGridData));
                streamWriter.WriteLine(JsonConvert.SerializeObject(AllSpriteData));

                streamWriter.Flush();
                fileStream.Close();
            }
            else
            {
                FileStream fileStream = new FileStream(Path.Combine(LVLDIR, LVLNAME) + ".json", FileMode.Create);
                StreamWriter streamWriter = new StreamWriter(fileStream);

                streamWriter.WriteLine(JsonConvert.SerializeObject(AllGridData));
                streamWriter.WriteLine(JsonConvert.SerializeObject(AllSpriteData));

                streamWriter.Flush();
                fileStream.Close();
            }

            MessageBox.Show("Level Saved to: " + Path.Combine(LVLDIR, LVLNAME) + ".json", "Level Saved", MessageBoxButton.OK, MessageBoxImage.Information);
        }

        //Handle Saving to File by Code
        public void HandleSaveByCode()
        {
            //Gathers Data from Level Grid
            int numberOfX = DynamicGrid.ColumnDefinitions.Count;
            int numberOfY = DynamicGrid.RowDefinitions.Count;

            //Creates Data Array for Saving
            GridData[] AllGridData = new GridData[numberOfX * numberOfY];
            SpriteData[] AllSpriteData = new SpriteData[spriteMenu.tabController.Items.Count];

            //Begins Creating Grid Data for Each X and Y of Level Grid
            int counter = 0;
            for (int x = 0; x < numberOfX; x++)
            {
                for (int y = 0; y < numberOfY; y++)
                {
                    GridData gridData = new GridData
                    {
                        numOfX = numberOfX,
                        numOfY = numberOfY,
                        XPos = x,
                        YPos = y,
                        SpriteFilePath = XYImage[x, y]
                    };
                    AllGridData[counter] = gridData;
                    counter++;
                }
            }

            //Begins Creating Sprite Data for Each Sprite Menu Tab
            for (int i = 0; i < spriteMenu.tabController.Items.Count; i++)
            {
                SpriteData spriteData = new SpriteData
                {
                    tileMapName = tileMapNames[i],
                    tileMapPath = tileMapPaths[i]
                };
                AllSpriteData[i] = spriteData;
            }

            //If a Save File Exists then Remove all Data and Re-Write Data through JSON Serialiser
            if (File.Exists(Path.Combine(LVLDIR, LVLNAME) + ".json"))
            {
                File.WriteAllText(Path.Combine(LVLDIR, LVLNAME) + ".json", string.Empty);

                FileStream fileStream = new FileStream(Path.Combine(LVLDIR, LVLNAME) + ".json", FileMode.Open);
                StreamWriter streamWriter = new StreamWriter(fileStream);

                streamWriter.WriteLine(JsonConvert.SerializeObject(AllGridData));
                streamWriter.WriteLine(JsonConvert.SerializeObject(AllSpriteData));

                streamWriter.Flush();
                fileStream.Close();
            }
            else
            {
                FileStream fileStream = new FileStream(Path.Combine(LVLDIR, LVLNAME) + ".json", FileMode.Create);
                StreamWriter streamWriter = new StreamWriter(fileStream);

                streamWriter.WriteLine(JsonConvert.SerializeObject(AllGridData));
                streamWriter.WriteLine(JsonConvert.SerializeObject(AllSpriteData));

                streamWriter.Flush();
                fileStream.Close();
            }

            MessageBox.Show("Level Saved to: " + Path.Combine(LVLDIR, LVLNAME) + ".json", "Level Saved", MessageBoxButton.OK, MessageBoxImage.Information);
        }

        //Handles Opening the File by Menu 
        private void HandleOpen(object sender, RoutedEventArgs e)
        {
            //Checks if there is a Level Open, if so Ask if they want to Save Current Level, else Open Dialog Window
            if (levelOpen)
            {
                MessageBoxResult result = MessageBox.Show("Save Level before Creating new Level?", "Save Level", MessageBoxButton.YesNoCancel, MessageBoxImage.Question);

                if (result == MessageBoxResult.Yes)
                {
                    HandleSaveByCode();
                    HandleLevelCloseByCode();
                }
                else if (result == MessageBoxResult.No)
                {
                    HandleLevelCloseByCode();
                }
            }

            OpenFileDialog openDialog = new OpenFileDialog
            {
                InitialDirectory = USRDIR,
                Filter = "JSON Files (*.json)|*.json"
            };

            if(openDialog.ShowDialog() == true)
            {
                FileStream fileStream = new FileStream(openDialog.FileName, FileMode.Open);

                //Sets all Level Directory Paths
                LVLDIR = Path.GetDirectoryName(openDialog.FileName);
                SPRITEDIR = LVLDIR + @"\Sprites";
                LVLNAME = Path.GetFileName(openDialog.FileName.Replace(".json", null));

                //Sets the Title to Level and Level Path
                Title = "Tile Grid Editor - " + LVLNAME + " - " + LVLDIR;

                //Begins reading JSON Data through Deserialising Each Object
                StreamReader streamReader = new StreamReader(fileStream);
                string jsonData = streamReader.ReadLine();
                GridData[] AllGridData = JsonConvert.DeserializeObject<GridData[]>(jsonData);

                //Runs though each Instance of Grid Data
                bool gridCreated = false;
                foreach(GridData gridData in AllGridData)
                {
                    if(gridData != null)
                    {
                        //Checks if the Grid has been made before continuing. Else continue filling the data from JSON
                        if (gridCreated == false)
                        {
                            XYImage = new string[gridData.numOfX, gridData.numOfY];
                            tileGrid.CreateGrid(gridData.numOfX, gridData.numOfY);

                            if(gridData.SpriteFilePath != null)
                            {
                                tileGrid.images[gridData.XPos, gridData.YPos].Source = new BitmapImage(new Uri(gridData.SpriteFilePath));
                            }
                            XYImage[gridData.XPos, gridData.YPos] = gridData.SpriteFilePath;
                            gridCreated = true;
                        }
                        else
                        {
                            if (gridData.SpriteFilePath != null)
                            {
                                tileGrid.images[gridData.XPos, gridData.YPos].Source = new BitmapImage(new Uri(gridData.SpriteFilePath));
                            }
                            XYImage[gridData.XPos, gridData.YPos] = gridData.SpriteFilePath;
                        }
                    }
                }

                //Reads next Line for the Sprite Data and Begins Deserialising it
                jsonData = streamReader.ReadLine();
                SpriteData[] AllSpriteData = JsonConvert.DeserializeObject<SpriteData[]>(jsonData);

                //Runs through each instances of Sprite Data 
                foreach (SpriteData spriteData in AllSpriteData)
                {
                    spriteMenu.spriteX = 0;
                    spriteMenu.spriteY = 0;
                    spriteMenu.customX = 0;
                    spriteMenu.customY = 0;

                    if (spriteData != null)
                    {
                        //Runs through the Data and Creates the Tabs and adds the Images to the Sprite Menu Grid
                        tileMapNames.Add(spriteData.tileMapName);
                        tileMapPaths.Add(spriteData.tileMapPath);
                        spriteMenu.AddTabItem(spriteData.tileMapName);
                        if(spriteData.tileMapName == "custom_sprite")
                        {
                            for (int y = 0; y <= 31; y++)
                            {
                                for (int x = 0; x <= 31; x++)
                                {
                                    string fileName = x + "_" + y + ".png";
                                    if (File.Exists(Path.Combine(spriteData.tileMapPath, fileName)))
                                    {
                                        spriteMenu.AddSprite(Path.Combine(spriteData.tileMapPath, fileName));

                                    }
                                }
                            }
                        }
                        else
                        {
                            for (int y = 0; y <= 31; y++)
                            {
                                for (int x = 0; x <= 31; x++)
                                {
                                    string fileName = y + "_" + x + ".png";
                                    if (File.Exists(Path.Combine(spriteData.tileMapPath, fileName)))
                                    {
                                        spriteMenu.AddSprite(new Image() { Source = new BitmapImage(new Uri(Path.Combine(spriteData.tileMapPath, fileName))) });

                                    }
                                }
                            }
                        }
                    }
                }

                //Closes the Stream Reader
                streamReader.Close();

                //Enables all the Level Features
                if (!levelOpen)
                {
                    levelOpen = true;
                    EnableLevelFeatures();
                }
            }
        }

        //Handles Closing the Current Level by Event
        private void HandleLevelClose(object sender, RoutedEventArgs e)
        {
            //Ask User if they want to Save Level before Creating a New Level. If Yes, Save, Else, Carry on
            MessageBoxResult result = MessageBox.Show("Save Level?", "Save Level", MessageBoxButton.YesNoCancel, MessageBoxImage.Question);

            if (result == MessageBoxResult.Yes)
            {
                HandleSaveByCode();
                tileGrid.GridReset();
                spriteMenu.ResetSpriteMenu();

                DisableLevelFeatures();
                levelOpen = false;

                Title = "Tile Grid Editor";
            }
            else if (result == MessageBoxResult.No)
            {
                tileGrid.GridReset();
                spriteMenu.ResetSpriteMenu();

                DisableLevelFeatures();
                levelOpen = false;

                Title = "Tile Grid Editor";
            }
        }

        //Handles Closing the Current Level by Code
        private void HandleLevelCloseByCode()
        {
            //Ask User if they want to Save Level before Creating a New Level. If Yes, Save, Else, Carry on
            MessageBoxResult result = MessageBox.Show("Save Level?", "Save Level", MessageBoxButton.YesNoCancel, MessageBoxImage.Question);

            if (result == MessageBoxResult.Yes)
            {
                HandleSaveByCode();
                tileGrid.GridReset();
                spriteMenu.ResetSpriteMenu();

                DisableLevelFeatures();
                levelOpen = false;

                Title = "Tile Grid Editor";
            }
            else if (result == MessageBoxResult.No)
            {
                tileGrid.GridReset();
                spriteMenu.ResetSpriteMenu();

                DisableLevelFeatures();
                levelOpen = false;

                Title = "Tile Grid Editor";
            }
        }

        //Handles Closing the Window
        private void HandleApplicationClose(object sender, RoutedEventArgs e)
        {
            //Checks if a Level is Open, if so Ask Use if they want to Save, else Continue Close
            if (levelOpen)
            {
                var result = MessageBox.Show("Save Level before Closing?", "Save before Exit", MessageBoxButton.YesNo, MessageBoxImage.Question);

                if (result == MessageBoxResult.No)
                {
                    Application.Current.Shutdown();
                }
                else if (result == MessageBoxResult.Yes)
                {
                    HandleSaveByCode();
                    Application.Current.Shutdown();
                }
            }
            else
            {
                Application.Current.Shutdown();
            }
        }

        //Handles Garbage Collection on Close
        private void HandleApplicationClosing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            GC.Collect();
        }

        //Handles the Tools Items
        private void HandleToolItems(object sender, RoutedEventArgs e)
        {
            //Checks if the Object Sender is one of the Tools
            if(sender == toolPen)
            {
                selectedTool = Tool.Pen;
                toolPen.IsEnabled = false;

                toolEraser.IsEnabled = true;
                toolEraser.IsChecked = false;
            }
            else if(sender == toolEraser)
            {
                selectedTool = Tool.Eraser;
                toolEraser.IsEnabled = false;

                toolPen.IsEnabled = true;
                toolPen.IsChecked = false;
            }
            else if (sender == toolLines)
            {
                if(toolLines.IsChecked != true)
                {
                    DynamicGrid.ShowGridLines = false;
                }
                else
                {
                    DynamicGrid.ShowGridLines = true;
                }
            }
        }

        //Handles Importing New Sprite
        private void HandleImportSprite(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openDialog = new OpenFileDialog
            {
                Filter = "Portable Network Graphic (*.png)|*.png|JPEG Image (*.jpg)|*.jpg"
            };

            if (openDialog.ShowDialog() == true)
            {
                //Checks if the Image Pixel Size is 32 x 32 px. Else show Error, else Carry On
                var image = new BitmapImage(new Uri(openDialog.FileName));
                if(image.PixelWidth < 32 && image.PixelHeight < 32)
                {
                    MessageBox.Show("Sprite is less than 32 x 32 px. Please use 32 x 32 px sprites.", "Sprite too small", MessageBoxButton.OK, MessageBoxImage.Warning);
                }
                else if(image.PixelWidth > 32 && image.PixelHeight > 32)
                {
                    MessageBox.Show("Sprite is more than 32 x 32 px. Please use 32 x 32 px sprites.", "Sprite too large", MessageBoxButton.OK, MessageBoxImage.Warning);
                }
                else
                {
                    //Creates a new name for the image, corresponding to its Sprite Menu Grid Pos. Copies that to Custom Sprites Dir in Level Dir
                    string fileName = spriteMenu.customX + "_" + spriteMenu.customY + ".png";
                    if (!File.Exists(Path.Combine(CUSTOMSPRITEDIR, fileName)))
                    {
                        File.Copy(openDialog.FileName, Path.Combine(CUSTOMSPRITEDIR, fileName));
                    }
                    spriteMenu.AddSprite(Path.Combine(CUSTOMSPRITEDIR, fileName));
                }
            }
        }

        //Handles Importing New TileMaps
        private void HandleImportTileMap(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openDialog = new OpenFileDialog
            {
                Filter = "Portable Network Graphic (*.png)|*.png|JPEG Image (*.jpg)|*.jpg"
            };

            if (openDialog.ShowDialog() == true)
            {
                string fileName;
                string folderName = Path.GetFileName(openDialog.FileName.Replace(".png", null));
                string folderPath = "";
                bool dirCheck = false;

                //Extra Extension Check to Create new Folders for the Tile Maps, removing there extensions
                if (Path.GetExtension(openDialog.FileName) == ".png")
                {
                    folderPath = Path.Combine(SPRITEDIR, folderName);
                    if(!Directory.Exists(folderPath))
                    {
                        Directory.CreateDirectory(folderPath);
                        dirCheck = true;
                    }
                }
                else if(Path.GetExtension(openDialog.FileName) == ".jpg")
                {
                    folderPath = Path.Combine(SPRITEDIR, Path.GetFileName(openDialog.FileName.Replace(".jpg", null)));
                    if (!Directory.Exists(folderPath))
                    {
                        Directory.CreateDirectory(folderPath);
                        dirCheck = true;
                    }
                }

                //Creates new Name for TileMap. Copys it to its new Folder and Begins Deconstructing it into 32 x32 px onto Sprite Menu Grid.
                fileName = "main" + Path.GetExtension(openDialog.FileName);
                if (dirCheck)
                {
                    File.Copy(openDialog.FileName, Path.Combine(folderPath, fileName));

                    var imageSource = new BitmapImage(new Uri(Path.Combine(folderPath, fileName)));

                    //Checks if the Tile Map Exceeds 1024 x 1024 px.
                    if (imageSource.PixelWidth <= 1024 && imageSource.PixelHeight <= 1024)
                    {
                        spriteMenu.AddTileMap(folderPath, folderName, fileName);
                        spriteMenu.Visibility = Visibility.Visible;
                        tileMapPaths.Add(folderPath);
                        tileMapNames.Add(folderName);
                    }
                    else
                    {
                        MessageBox.Show("Tile Map Image Exceeds 1024 x 1024 pixels. Please use a reduced size.", "Tile Map Too Large", MessageBoxButton.OK, MessageBoxImage.Warning);
                    }
                }
                else
                {
                    MessageBox.Show("Tile Map already exist in this Project", "Tile Map Exists", MessageBoxButton.OK, MessageBoxImage.Warning);
                }
            } 
        }

        //Handles Export of Level as an Image
        private void HandleExport(object sender, RoutedEventArgs e)
        {
            DynamicGrid.ShowGridLines = false;
            RenderTargetBitmap bitmap = new RenderTargetBitmap((int)DynamicGrid.ActualWidth, (int)DynamicGrid.ActualHeight, 96, 96, PixelFormats.Pbgra32);
            DynamicGrid.Measure(new Size((int)DynamicGrid.ActualWidth, (int)DynamicGrid.ActualHeight));
            DynamicGrid.Arrange(new Rect(new Size((int)DynamicGrid.ActualWidth, (int)DynamicGrid.ActualHeight)));
            bitmap.Render(DynamicGrid);

            FileStream stream = new FileStream(Path.Combine(LVLDIR, (LVLNAME + ".jpg")), FileMode.Create);

            JpegBitmapEncoder encoder = new JpegBitmapEncoder
            {
                QualityLevel = 100
            };
            encoder.Frames.Add(BitmapFrame.Create(bitmap));
            encoder.Save(stream);

            stream.Close();
            DynamicGrid.Measure(new Size((int)DynamicGrid.ActualWidth + 4, (int)DynamicGrid.ActualHeight + 4));
            DynamicGrid.Arrange(new Rect(new Size((int)DynamicGrid.ActualWidth + 4, (int)DynamicGrid.ActualHeight + 4)));
            DynamicGrid.ShowGridLines = true;
        }

        //On Mouse Down Event
        public void OnMouseDown(object sender, MouseButtonEventArgs e)
        {
            penIsDown = true;
        }

        //On Mouse Up Event
        public void OnMouseUp(object sender, MouseButtonEventArgs e)
        {
            penIsDown = false;
        }

        //On Mouse Move Event
        public void OnMouseMove(object sender, MouseEventArgs e)
        {
            //Gets X and Y Pos from Level Map Grid
            int x = (int)e.GetPosition(DynamicGrid).X / 32;
            xPos.Text = "X: " + x;
            int y = (int)e.GetPosition(DynamicGrid).Y / 32;
            yPos.Text = "Y: " + y;
            
            if (penIsDown)
            {
                if (!(x > DynamicGrid.ColumnDefinitions.Count - 1) && !(y > DynamicGrid.RowDefinitions.Count - 1))
                {
                    //Uses the Tool with X and Y and current Sprite Tile
                    tileGrid.UseTool(x, y, tileGrid.penImageSource);
                    if (tileGrid.penImageSource != null)
                    {
                        XYImage[x, y] = tileGrid.penImageSource.ToString();
                    }
                }
            }
        }

        //On Selected Item Event
        private void OnSelectedItem(ImageSource source)
        {
            //Resets the Pen Image 
            tileGrid.ImageReset(source);

            //Shows what Tile is being Used
            spriteMenu.selectedImage.Source = source;
        }

        //Enables Level Features
        public void EnableLevelFeatures()
        {
            xPos.Visibility = Visibility.Visible;
            yPos.Visibility = Visibility.Visible;
            levelGridText.Visibility = Visibility.Visible;
            spriteMenu.Visibility = Visibility.Visible;

            saveLevel.IsEnabled = true;
            closeLevel.IsEnabled = true;
            importSprite.IsEnabled = true;
            importTileMap.IsEnabled = true;
            toolMenu.IsEnabled = true;
            exportImage.IsEnabled = true;
        }

        //Disables Level Features
        public void DisableLevelFeatures()
        {
            xPos.Visibility = Visibility.Hidden;
            yPos.Visibility = Visibility.Hidden;
            levelGridText.Visibility = Visibility.Hidden;
            spriteMenu.Visibility = Visibility.Hidden;

            saveLevel.IsEnabled = false;
            closeLevel.IsEnabled = false;
            importSprite.IsEnabled = false;
            importTileMap.IsEnabled = false;
            toolMenu.IsEnabled = false;
            exportImage.IsEnabled = false;
        }
    }
}