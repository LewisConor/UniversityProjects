   M S B A M L   `   `   `  ����  TileGridEditor    TileGridEditor.NewMap   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	     � Title$  Create New Level��5   	   $	��250��6"   $	��250��6/    � 
ResizeMode$ NoResize=�6;    � WindowStartupLocation$ CenterScreen=�6Q   
�������.��5      �  � ColumnDefinitions 5	   
   �� 5
      �� 5       � RowDefinitions 5   
   �� 5      �� 5      �� 5      �� 5      �� 5      .+�5   
   �� $��0��6   $��
Level Name��6!   $��18(�63   $��Center=�6A    �� TextAlignment$ Center=�6\   �� 5   
   -   5         ��Name$ 	levelName��5      $��2��6)   $��0��69   $��18(�6F   $��Center=�6T   
�������$��2q�6�   �� 5   
   $��1��6   $��Level Width��6!   $��18(�64   $��Center=�6B   $ Center=�6]   �� 5   
   -   5         ��Name$ levelWidthValue��5      $��1��6-   $��1��6:   $��2��6J   $��15(�6S   $	��Top=�6a   $��Center=�6y   �� 5   
   -   5         ��Name$ 
levelWidth��5      	 � Value$	 2Q�6%   
 � Minimum$
 2Q�6/    � Maximum$ 20Q�6;    �� TickFrequency$ 1Q�6H    �� TickPlacement$ BottomRight=�6Z    �� IsSnapToTickEnabled . $��1��6�   $��1��6�   $��Bottom=�6�   6�   �� 5   
   $��2��6   $��Level Height��6!   $��18(�65   $��Center=�6C   $ Center=�6^   �� 5   
   -   5        $ levelHeightValue��5      $��2��6.   $��1��6;   $��2��6K   $��15(�6T   $	��Top=�6b   $��Center=�6z   �� 5   
   -   5        $ levelHeight��5      $	 2Q�6&   $
 2Q�60   $ 20Q�6<   $ 1Q�6I   $ BottomRight=�6[    . $��2��6�   $��1��6�   $��Bottom=�6�   6�   �� 5   
   $��Include Default Sprites��6   $��18(�63   $
��Wrap=�6A   $ Center=�6U   $��3��6l   $��0��6y   $��Center=�6�   �� 5    
   -   5         ��Name$ includeSprites��5       $��3��6+   $��1��68   $��Center=�6H   $��Center=�6c   �� 5"   
   -   5        $��Create Level��5"      $��4��6(   $��2��65   $��30��6E   $	��100��6Q   $��Center=�6]   $��Center=�6x   6�   �� 5#   
   -   5        $��Cancel��5#      $��4��6"   $��0��6/   $��30��6?   $	��100��6K   $��Center=�6W   $��Center=�6r   6�   5$      5%      