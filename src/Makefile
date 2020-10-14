include ../config

all: directories program

directories: 
	mkdir -p ../$(OUTPUT)

program: program.o
	$(CC) -o ../$(OUTPUT)/app-50NuancesDeCodes $^ $(LIBS)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

config:
	rm config
	"OS= `uname`" >> config

clean:
	rm -rf *.o


