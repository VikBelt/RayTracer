CC = g++
CFLAGS = -I.
DEPS = helper.h rays.h shapes.h
OBJ = rays.o shapes.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

rays: rays.cpp shapes.cpp main.cpp
	  $(CC) -o $@ $^ $(CFLAGS)
