#### If building for linux ####
# Just issue 'make' command in top level directory
CC=gcc
#### If building for windows ####
# Cross-compilation requires you to have either ming32 or mingw-w64
# I am using mingw-w64 which can build 32 bit or 64 bit for windows
# Run 'make win32' to build for windows
WCC=i686-w64-mingw32-gcc
OBJ=obj/win32/
WINDRES=i686-w64-mingw32-windres

default: hangman.o dictionary.o stkfgr.o getchlike.o
	 $(CC) obj/hangman.o obj/dictionary.o obj/stkfgr.o obj/getchlike.o \
			-o hangman

hangman.o:	src/hangman.c
		$(CC) -c src/hangman.c -o obj/hangman.o

dictionary.o:	src/dictionary.c
		$(CC) -c src/dictionary.c -o obj/dictionary.o

stkfgr.o:	src/stkfgr.c
		$(CC) -c src/stkfgr.c -o obj/stkfgr.o

getchlike.o:	src/getchlike.c
		$(CC) -c src/getchlike.c -o obj/getchlike.o

win32: 	win32_hangman.o win32_dictionary.o win32_stkfgr.o win32_icon.res
	$(WCC) $(OBJ)hangman.o $(OBJ)dictionary.o $(OBJ)stkfgr.o \
	       			$(OBJ)icon.res -o hangman.exe

win32_hangman.o: src/hangman.c
		 $(WCC) -c src/hangman.c -o $(OBJ)hangman.o

win32_dictionary.o:	 src/dictionary.c
		 $(WCC) -c src/dictionary.c -o $(OBJ)dictionary.o

win32_stkfgr.o:	 src/stkfgr.c
		 $(WCC) -c src/stkfgr.c -o $(OBJ)stkfgr.o

win32_icon.res:  src/icon.rc
		 $(WINDRES) src/icon.rc -O coff -o $(OBJ)icon.res

clean:	
		rm obj/*.o hangman
		rm obj/win32/*.o obj/win32/icon.res hangman.exe
