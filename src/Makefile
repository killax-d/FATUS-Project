include ../config

all: directories program

directories: 
	rm -rf ../$(OUTPUT)
	mkdir -p ../$(OUTPUT)
	mkdir -p assets
	cp -r assets ../$(OUTPUT)

program: program.o
	$(CC) -o ../$(OUTPUT)/app-50NuancesDeCodes $^ $(LIBS)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

config:
	rm config
	"OS= `uname`" >> config

clean:
	rm -rf *.o
	rm -rf ../$(OUTPUT)


