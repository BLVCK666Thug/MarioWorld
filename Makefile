marioworld:main.o fonctions.o
	gcc main.o fonctions.o -o marioworld -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g
main.o:main.c
	gcc -c main.c -g
fonctions.o:fonctions.c
	gcc -c fonctions.c -g

clean:
	rm main.o fonctions.o marioworld

