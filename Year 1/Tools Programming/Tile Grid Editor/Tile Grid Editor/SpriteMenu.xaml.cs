using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace TileGridEditor
{
    /// <summary>
    /// Interaction logic for SpriteMenu.xaml
    /// </summary>
    public partial class SpriteMenu : UserControl
    {
        //Variables
        public MainWindow mainWindow;

        public delegate void SelectedItemDelegate(ImageSource source);
        public event SelectedItemDelegate SelectedItem;

        public int SpriteWidth { get; private set; } = 32;
        public int SpriteHeight { get; private set; } = 32;

        public Border[,,] images { get; private set; } = new Border[16, 32, 32];

        List<Grid> tileGridMaps = new List<Grid>();
        List<TabItem> tabItems = new List<TabItem>();

        public int spriteX = 0;
        public int spriteY = 0;
        public int customX = 0;
        public int customY = 0;

        private int currentTab = 0;
        private int customTabIndex = 0;

        protected int BorderWidth = 2;
        protected SolidColorBrush selectedBrush = new SolidColorBrush(Colors.Black);
        protected SolidColorBrush unselectedBrush = new SolidColorBrush(Colors.White);

        protected Border selectedSprite = null;

        //Window Initaliser
        public SpriteMenu()
        {
            InitializeComponent();
            if (System.ComponentModel.DesignerProperties.GetIsInDesignMode(this)) return;
        }

        //1st Add Sprite with Overload String for Custom Sprites
        public void AddSprite(string localFilePath)
        {
            Image image = new Image() { Source = new BitmapImage(new Uri(localFilePath)) };

            Border border = images[customTabIndex, customX, customY];
            border.Height = 32;
            border.Width = 32;
            border.BorderBrush = unselectedBrush;
            border.Child = image;

            if (customX == 31)
            {
                customX = 0;
                customY++;
            }
            else
            {
                customX++;
            }
        }

        //2nd Add Sprite with Overload Image for Tile Map Sprites
        public void AddSprite(Image image)
        {
            Border border = images[currentTab, spriteX, spriteY];
            border.Height = 32;
            border.Width = 32;
            border.BorderBrush = unselectedBrush;
            border.Child = image;
            
            if(spriteX == 31)
            {
                spriteX = 0;
                spriteY++;
            }
            else
            {
                spriteX++;
            }
        }

        //Adds Tile Map to Tab Controller and Breaks up into 32 x 32 px sprites
        public void AddTileMap(string localFolderPath, string localFolderName, string localFileName)
        {
            string localFilePath = Path.Combine(localFolderPath, localFileName);
            var imageSource = new BitmapImage(new Uri(localFilePath));

            spriteX = 0;
            spriteY = 0;

            //Creates a New Tab
            AddTabItem(localFolderName);

            for (int y = 0; y < imageSource.PixelHeight; y += 32)
            {
                for (int x = 0; x < imageSource.PixelWidth; x += 32)
                {
                    //Crops Down Image down to 32 x 32 px on a X and Y Pos
                    CroppedBitmap croppedBitmap = new CroppedBitmap(imageSource, new Int32Rect(x, y, 32, 32));

                    string newImagePath = localFolderPath + "\\" + (y / 32).ToString() + "_" + (x / 32).ToString() + ".png";

                    PngBitmapEncoder pngBitmapEncoder = new PngBitmapEncoder();
                    pngBitmapEncoder.Frames.Add(BitmapFrame.Create(croppedBitmap));

                    //Saves this to its new Folder Location
                    FileStream fileStream = new FileStream(newImagePath, FileMode.Create);
                    pngBitmapEncoder.Save(fileStream);
                    fileStream.Close();

                    Image image = new Image() { Source = new BitmapImage(new Uri(newImagePath)) };

                    //Adds Sprite to Grid
                    AddSprite(image);
                }
            }
        }

        //On Mouse Down Event
        private void OnMouseDown(object sender, MouseButtonEventArgs e)
        {
            //Gets X and Y Pos
            int x = (int)e.GetPosition((sender as Grid)).X / 32;
            int y = (int)e.GetPosition((sender as Grid)).Y / 32;

            //Gets that from Array based on Current Tab, X and Y
            Border border = images[currentTab, x, y];
            selectedSprite = border;

            if (selectedSprite != null)
            {
                ImageSource source = (border.Child as Image).Source;

                //Sends it to On Selected Item Event
                SelectedItem?.Invoke(source);
            }
        }

        //Add a new Tab to Controller
        public void AddTabItem(string tileMapName)
        {
            currentTab = tabController.Items.Count;

            //Creates a New Tab Item
            TabItem tabItem = new TabItem
            {
                Header = "Tile Map: " + tileMapName,
                Name = string.Format("tileMap{0}", currentTab)
            };

            //Creates a New Scroll Viewer
            ScrollViewer scrollViewer = new ScrollViewer
            {
                VerticalScrollBarVisibility = ScrollBarVisibility.Visible,
                HorizontalScrollBarVisibility = ScrollBarVisibility.Visible
            };

            //Creates a New Grid with 32 Rows and 32 Columns
            Grid grid = new Grid()
            {
                Background = new SolidColorBrush(Colors.LightGray),
                Name = string.Format("tileGrid{0}", currentTab),
                ShowGridLines = true
            };

            for (int x = 0; x < 32; x++)
            {
                grid.ColumnDefinitions.Add(new ColumnDefinition());
            }

            for(int y = 0; y < 32; y++)
            {
                grid.RowDefinitions.Add(new RowDefinition());
            }

            //Sets a new Array for this Grid to Use
            for(int x = 0; x < 32; x++)
            {
                for(int y = 0; y < 32; y++)
                {
                    Border border = new Border
                    {
                        Width = 32,
                        Height = 32
                    };
                    Grid.SetColumn(border, x);
                    Grid.SetRow(border, y);

                    grid.Children.Add(border);

                    images[currentTab, x, y] = border;
                }
            }
            //Adds this to an Array
            tileGridMaps.Add(grid);

            //Sets the Grid to the Scroll Bar's Content
            scrollViewer.Content = grid;

            //Sets the Scroll Bar to the Tab Item's Conent
            tabItem.Content = scrollViewer;

            //Adds Tab Items to Array
            tabItems.Add(tabItem);

            //Inserts Tab To Tab Controller
            tabController.Items.Insert(currentTab, tabItem);

            //Sets Mouse Down Event for Grid to Funtion
            grid.MouseDown += OnMouseDown;
            tabController.SelectedIndex = currentTab;
        }

        //Resets the Sprite Menu
        public void ResetSpriteMenu()
        {
            tileGridMaps.Clear();
            tabItems.Clear();
            tabController.Items.Clear();
            images = null;
            images = new Border[16, 32, 32];
            currentTab = 0;
        }

        //Updates Current Tab based on selected Tab
        private void OnSelectionChange(object sender, SelectionChangedEventArgs e)
        {
            currentTab = tabController.SelectedIndex;
        }
    }
}