#Compilador a usar
CC = gcc

#Opciones de compilacion
CFLAGS = -w

#Rutas de directorios
DIR_OBJS = bin
DIR_SOURCE = src

#Nombre de los ejecutables y ficheros objetos usados
EXE_NAME = main
OBJS_FILES = $(DIR_SOURCE)/main.c $(DIR_OBJS)/s-box.o $(DIR_OBJS)/rcon.o

$(EXE_NAME): $(OBJS_FILES)
	$(CC) $^ $(CFLAGS) -o $(EXE_NAME)

$(DIR_OBJS)/s-box.o: $(DIR_SOURCE)/s-box.c  $(DIR_SOURCE)/s-box.h
	$(CC) $(CFLAGS) -c $(DIR_SOURCE)/s-box.c -o $(DIR_OBJS)/s-box.o

$(DIR_OBJS)/rcon.o:  $(DIR_SOURCE)/rcon.c $(DIR_SOURCE)/rcon.h
	$(CC) $(CFLAGS) -c $(DIR_SOURCE)/rcon.c -o $(DIR_OBJS)/rcon.o

clean:
	$(RM) $(EXE_NAME) $(DIR_OBJS)/*.o core

