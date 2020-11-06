TARGET = matrix
OBJ = main.o matrix.o
LFLAGS = -pthread -lpthread
CFLAGS = -D_REENTERANT

all: $(OBJ)
	gcc -o $(TARGET) $(LFLAGS) $(OBJ)

.c.o:
	gcc -c $(CFLAGS) $<

clean:
	rm -r *.o $(TARGET)