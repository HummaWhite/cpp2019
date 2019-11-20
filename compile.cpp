#include <windows.h>

int main()
{
	system("gcc -c acllib.c -std=c11 -g");
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
		 "slime.cpp "
		 "sword.cpp "
		 "cucco.cpp "
		 "bari.cpp "
		 "animation.cpp "
		 "sound.cpp "
		 "-std=c++11 -g"
		);
	system
		(
		 "g++ "
		 "acllib.o "
		 "main.o "
		 "entity.o "
		 "player.o "
		 "bumpbox.o "
		 "item.o "
		 "moblin.o "
		 "arrow.o "
		 "bullet.o "
		 "slime.o "
		 "sword.o "
		 "cucco.o "
		 "bari.o "
		 "animation.o "
		 "sound.o "
		 "-lgdi32 -lole32 -loleaut32 -luuid -lwinmm -lmsimg32 "
		 "-o test02.exe -g"
		);
	system("test02.exe");
}
