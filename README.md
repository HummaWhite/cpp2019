

### cpp2019课的实验

![](https://github.com/HummaWhite/cpp2019/blob/master/md-pics/Movies%20%26%20TV%202020_2_11%2023_11_37.png)

![](https://github.com/HummaWhite/cpp2019/blob/master/md-pics/test02%202019_11_25%2014_06_43.png)

cpp课的大实验要求用C++的方法（类封装、继承、多态）+ACLlib写一个精灵游戏，恰好像素风格素材很适合这种功能简单的图形库，于是就仿了一个劣质的塞尔达出来。图音素材取自A Link to The Past与Link's Awakening。游戏中有几类不同的精灵，会根据玩家的行为作出不同的互动。特意还原了塞尔达传说最强生物：鸡神。

#### 运行方法

编译compile.cpp并运行

或执行以下命令：

```
gcc -c acllib.c -std=c11
g++ -c entity.cpp main.cpp player.cpp bumpbox.cpp item.cpp moblin.cpp arrow.cpp bullet.cpp slime.cpp sword.cpp cucco.cpp bari.cpp animation.cpp sound.cpp -std=c++11
g++ acllib.o main.o entity.o player.o bumpbox.o item.o moblin.o arrow.o bullet.o slime.o sword.o cucco.o bari.o animation.o sound.o -lgdi32 -lole32 -loleaut32 -luuid -lwinmm -lmsimg32 -o test.exe
```

#### 操作

方向键：										移动

空格： 											使用剑

E:          											发射一圈火球

Q:    												自爆

B:    												开启/关闭 Debug 显示（DEBUG_SHOWBOX）

P： 												开启/关闭 Debug 暂停（DEBUG_FREEZE） 

Z： 												获得红药水 

C： 												使用物品 

Shift： 										切换物品

#### Debug/后台

>**Debug显示：**精灵的显示碰撞箱以及关系（连线）
>
>**Debug暂停：**暂停除玩家精灵外其他精灵的活动

![](https://github.com/HummaWhite/cpp2019/blob/master/md-pics/Movies%20%26%20TV%202020_2_11%2023_05_02.png)

![](https://github.com/HummaWhite/cpp2019/blob/master/md-pics/test02%202019_10_24%2018_34_17.png)

![](https://github.com/HummaWhite/cpp2019/blob/master/md-pics/Movies%20%26%20TV%202020_2_11%2023_05_50.png)
