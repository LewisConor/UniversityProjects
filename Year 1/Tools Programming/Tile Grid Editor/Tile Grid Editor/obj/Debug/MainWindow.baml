   M S B A M L   `   `   `  ����I  ETileGridEditor, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null/clr-namespace:TileGridEditorTileGridEditor  5   	       TileGridEditor.MainWindow   5   	   W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   .localclr-namespace:TileGridEditor     5   	   -   5          � Title$  Tile Grid Editor��5	   	   $	��600��6"   $	��800��6/    � WindowStartupLocation$ CenterScreen=�6;    � WindowState$ 	Maximized=�6`   
������� �� TextAlignment$ Center=�6�   .��5
      ]� .+�5   
   o�  o� 
IsMainMenu . $	��Top=�6"   .@�5      m� $
��File��6   .@�5      m� -   5        $��	New Level��5      6.   m� 5      -   5         m�Name$ 	saveLevel��5      $��
Save Level��6.   {�.  6T   m� 5      -   5        $��
Open Level��5      6/   m� 5      -   5        $ 
closeLevel��5      $��Close Level��6/   {�.  6V   �� 5      m� 5      -   5        $ importSprite��5      $��Import Sprite��61   {�.  6Z   m� 5      -   5        $ importTileMap��5      $��Import Tile Map��62   {�.  6]   �� 5      m� 5      -   5        $ exportImage��5      $��Export Level as Image��60   {�.  6a   �� 5      m� 5      -	   5        $��Close Tile Grid Editor��5      6;   5      m� 5      -
   5        $ toolMenu��5      $��Tools��6)   {�.  .@�5      m� -   5        $ toolPen��5   ^   $	��Pen��6    m� IsCheckable .  m� 	IsChecked . {�.  6o   m� 5      -   5        $ 
toolEraser��5   >   $��Eraser��6    . {�. 6c   �� 5      m� 5      -   5        $ 	toolLines��5   ]   $��Show/Hide Grid Lines��6    .  . {�. 6�   5      5      � 5    
   $	��Top=�6    � ShowGridLines . 	 � ColumnDefinitions	 5!      �� 5"      �� 5#      .+�5&         TileGridEditor.SpriteMenu  -   5        
  Name$
 
spriteMenu��5&      $
��Left=�63   $��Center=�6I   $	��500��6d   $	��500��6p   $y�Hidden=�6}   $��0��6�   $��1��6�   � 5(      $��1��6    � RowDefinitions 5)      �� 5*      $��1* �6$   �� 5+      $	��10* �6$   �� 5,      $��1* �6$   .+�5.      �� -   5         ��Name$ levelGridText��5.      $y�Hidden=�63   $��Level Grid Map��6G   $��30(�6]   $��0��6k   $��Bottom=�6x   �� 5/      -   5         ��Name$ 
gridBorder��5/   -   $y�Hidden=�6   
���   �$��2q�6U   $��1��6i   $��Center=�6v   $��Center=�6�   ._�50      � -   5         �Name$ DynamicGrid��50      
�������$y�Hidden=�6G    . 6[   51      � 52      $��2��6   $	��Top=�6$   $��Center=�6<   	 53      �� 54      $
��Auto �6+   �� 55      $��10 �6+   �� 56      $
��Auto �6+   �� 57       59      �� 5:      $��32 �6(   �� 5;      .+�5=      �� -   5        $
 xPos��5=       $��0��6.   $	��X: ��6>   $y�Hidden=�6I   $��Bottom=�6]   $
��Left=�6x   
�������$��30(�6�   �� 5>      -   5        $
 yPos��5>       $��2��6.   $	��Y: ��6>   $y�Hidden=�6I   $��Bottom=�6]   $��Right=�6x   
�������$��30(�6�   5?      5@      5A      5B      5D      