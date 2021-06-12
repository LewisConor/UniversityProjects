using System;
using System.IO;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media.Imaging;
using System.Threading.Tasks;

namespace TileGridEditor
{
    /// <summary>
    /// Interaction logic for NewMap.xaml
    /// </summary>
    public partial class NewMap : Window
    {
        MainWindow main = (MainWindow)Application.Current.MainWindow;

        //Window Initalizer
        public NewMap()
        {
            InitializeComponent();
            if (System.ComponentModel.DesignerProperties.GetIsInDesignMode(this)) return;
        }

        //Handles Level Creation
        private void CreateLevel(object sender, RoutedEventArgs e)
        {
            //Letter Validation Check
            Regex regex = null;

            regex = new Regex("^([a-zA-Z0-9])*$");

            string levelNameString = new TextRange(levelName.Document.ContentStart, levelName.Document.ContentEnd).Text;
            levelNameString = levelNameString.Replace("\r\n", string.Empty);

            if (String.IsNullOrEmpty(levelNameString))
            {
                MessageBox.Show("Level Name cannot be empty.", "No Level Name", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }

            //Checks if there are Special Characters. If there are, User Must Remove them. Else Continue
            if (!regex.IsMatch(levelNameString))
            {
                MessageBox.Show("Please remove Special Characters from Level Name", "Special Character Detected", MessageBoxButton.OK, MessageBoxImage.Warning);
            }
            else
            {
                int newColumnCount = (int)levelWidth.Value;
                int newRowCount = (int)levelHeight.Value;

                string levelPath = main.USRDIR + @"\" + levelNameString;
                string spritePath = levelPath + @"\Sprites";

                string customSpritePath = spritePath + @"\custom_sprites";

                //If the Level already exists, Warn the User to use another name
                if (!Directory.Exists(levelPath))
                {
                    //Creates Level Directories
                    Directory.CreateDirectory(levelPath);
                    Directory.CreateDirectory(spritePath);
                    Directory.CreateDirectory(customSpritePath);

                    //Enables Level Features
                    if (main.levelOpen != true)
                    {
                        main.EnableLevelFeatures();
                        main.levelOpen = true;
                    }

                    //Sets Level Directories in Main
                    main.LVLDIR = levelPath;
                    main.SPRITEDIR = spritePath;
                    main.CUSTOMSPRITEDIR = customSpritePath;
                    main.LVLNAME = levelNameString;

                    //Creates the Level Map Grid
                    main.tileGrid.CreateGrid(newColumnCount, newRowCount);

                    //Creates Custom Sprites Tab in Sprite Menu
                    main.spriteMenu.AddTabItem("custom_sprites");
                    main.tileMapNames.Add("custom_sprites");
                    main.tileMapPaths.Add(customSpritePath);

                    //If the User wants to include Default Sprites then Flow into
                    if (includeSprites.IsChecked == true)
                    {
                        AddDefaultSprites();
                    }

                    //Sets the Title to Level Name and Path
                    main.Title = "Tile Grid Editor - " + levelNameString + " - " + levelPath;

                    //Creates an Array for Sprite Paths
                    main.XYImage = new string[newColumnCount, newRowCount];

                    //Closes Window
                    Close();

                    //Saves the Level
                    main.HandleSaveByCode();
                }
                else
                {
                    MessageBox.Show("Level already Exists, please use a different Name.", "Level Name Exists", MessageBoxButton.OK, MessageBoxImage.Warning);
                }
            }
        }

        //Handles Closing Window
        public void CloseWindow(object sender, RoutedEventArgs e)
        {
            Close();
        }

        //Handles Slider Value Changes
        private void ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            //Checks Object Sender to determine which Variable to Set
            if(sender == levelWidth)
            {
                levelWidthValue.Text = ((int)levelWidth.Value).ToString();
            }
            else if (sender == levelHeight)
            {
                levelHeightValue.Text = ((int)levelHeight.Value).ToString();
            }
        }

        void AddDefaultSprites()
        {
            //Function Variables
            BitmapImage image;
            PngBitmapEncoder pngBitmapEncoder;
            FileStream fileStream;
            string fileName;
            string folderName = "";
            string folderPath = "";

            //Adds Single Tiles to Level Dir
            for (int i = 0; i < 12; i++)
            {
                fileName = main.spriteMenu.customX + "_" + main.spriteMenu.customY + ".png";

                string spriteFile = "pack://application:,,,/Images/singleTiles/" + i + ".png";
                image = new BitmapImage(new Uri(spriteFile));

                pngBitmapEncoder = new PngBitmapEncoder();
                pngBitmapEncoder.Frames.Add(BitmapFrame.Create(image));

                fileStream = new FileStream(Path.Combine(main.CUSTOMSPRITEDIR, fileName), FileMode.Create);
                pngBitmapEncoder.Save(fileStream);
                fileStream.Close();

                main.spriteMenu.AddSprite(Path.Combine(main.CUSTOMSPRITEDIR, fileName));
            }

            //Adds Terrain Atlas Tile Map To Level Dir
            folderName = "terrain_atlas";
            folderPath = Path.Combine(main.SPRITEDIR, folderName);
            Directory.CreateDirectory(folderPath);

            fileName = main + ".png";

            image = new BitmapImage(new Uri("pack://application:,,,/Images/terrain_atlas.png"));

            pngBitmapEncoder = new PngBitmapEncoder();
            pngBitmapEncoder.Frames.Add(BitmapFrame.Create(image));

            fileStream = new FileStream(Path.Combine(folderPath, fileName), FileMode.Create);
            pngBitmapEncoder.Save(fileStream);
            fileStream.Close();

            main.spriteMenu.AddTileMap(folderPath, folderName, fileName);

            main.tileMapPaths.Add(folderPath);
            main.tileMapNames.Add(folderName);

            //Adds Base Out Atlas Tile Map to Level Dir
            folderName = "base_out_atlas";
            folderPath = Path.Combine(main.SPRITEDIR, folderName);
            Directory.CreateDirectory(folderPath);

            fileName = main + ".png";

            image = new BitmapImage(new Uri("pack://application:,,,/Images/base_out_atlas.png"));

            pngBitmapEncoder = new PngBitmapEncoder();
            pngBitmapEncoder.Frames.Add(BitmapFrame.Create(image));

            fileStream = new FileStream(Path.Combine(folderPath, fileName), FileMode.Create);
            pngBitmapEncoder.Save(fileStream);
            fileStream.Close();

            main.spriteMenu.AddTileMap(folderPath, folderName, fileName);

            main.tileMapPaths.Add(folderPath);
            main.tileMapNames.Add(folderName);
        }
    }
}