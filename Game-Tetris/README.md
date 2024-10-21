# MS-DOS-Tetris 基本描述
控制台程序——俄罗斯方块(Tetris).

# 实现思路
## 界面显示
  通过用for循环printf函数显示.
## 数据储存
  玩家可以控制的方块，即移动方块，用循环链表储存，在函数Initialise中有具体定义;
  那么，移动方块用4\*4的int型二维数组进行储存，每一个元素值为2的元素代表一个像素点;
  比如:
 |Ⅰ   |2 0 0 0   2 2 2 2 |
 |形   |2 0 0 0   0 0 0 0 |
 |方   |2 0 0 0   0 0 0 0 |
 |块   |2 0 0 0   0 0 0 0 |
## 方块移动
   这里有两个基本int型数据:Immortalx,Immortaly.分别表示移动方块在游戏界面的坐标位置.
   通过kbhit函数和getch函数 + switch语句进行键盘敲击判断，W:变换移动方块形状(链表的下一个元素).AD:左右移动(Immortalx加减).S：快速移动(跳过Sleep函数).当然这里的操作需要一定的判断——判断是否碰撞等……