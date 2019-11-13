# cpp2019
cpp2019课的实验

> 运行方法：编译compile.cpp并运行
>
> 或执行以下命令：

```
gcc -c acllib.c -std=c11
g++ -c entity.cpp main.cpp player.cpp bumpbox.cpp item.cpp moblin.cpp arrow.cpp bullet.cpp slime.cpp sword.cpp cucco.cpp bari.cpp animation.cpp -std=c++11
g++ acllib.o main.o entity.o player.o bumpbox.o item.o moblin.o arrow.o bullet.o slime.o sword.o cucco.o bari.o animation.o -lgdi32 -lole32 -loleaut32 -luuid -lwinmm -lmsimg32 -o test.exe
```