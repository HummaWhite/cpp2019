#include <windows.h>

int main()
{
	system
		(
		 "g++ -c "
		 "entity.cpp "
		 "main.cpp "
		 "player.cpp "
		 "bumpbox.cpp "
		 "item.cpp "
		 "moblin.cpp "
		 "arrow.cpp "
		 "bullet.cpp "
		 "-std=c++11 -g"
		);
	system
		(
		 "g++ "
		 "acllib.o "
		 "entity.o "
		 "main.o "
		 "player.o "
		 "bumpbox.o "
		 "item.o "
		 "moblin.o "
		 "arrow.o "
		 "bullet.o "
		 "-lgdi32 -lole32 -loleaut32 -luuid -lwinmm -lmsimg32 "
		 "-o test02.exe -g"
		);
	system("test02.exe");
}
