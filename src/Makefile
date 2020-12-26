include ../config

all: directories program

directories: 
	rm -rf ../$(OUTPUT)
	rm -rf ../src/*.o
	mkdir -p ../$(OUTPUT)
	mkdir -p assets
	cp -r assets ../$(OUTPUT)

program: program.o item.o inventory.o collider.o player.o sprite.o map.o game.o gameitems.o button.o menu.o door.o
	$(CC) -o ../$(OUTPUT)/app-50NuancesDeCodes $^ $(LIBS)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

config:
	rm config
	"OS= `uname`" >> config

clean:
	rm -rf *.o
	rm -rf ../$(OUTPUT)


