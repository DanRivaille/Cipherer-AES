#Compilador a usar
CC = g++

#Opciones de compilacion
CFLAGS = -w

#Rutas de directorios
DIR_OBJS = bin
DIR_SOURCE = source

#Nombre de los ejecutables y ficheros objetos usados
EXE_NAME = main
OBJS_FILES = $(DIR_SOURCE)/main.cpp $(DIR_OBJS)/Key.o

$(EXE_NAME): $(OBJS_FILES)
	$(CC) $^ $(CFLAGS) -o $(EXE_NAME)

#$(DIR_OBJS)/s-box.o: $(DIR_SOURCE)/s-box.c  $(DIR_SOURCE)/s-box.h $(DIR_SOURCE)/definitions.h
#	$(CC) $(CFLAGS) -c $(DIR_SOURCE)/s-box.c -o $(DIR_OBJS)/s-box.o

#$(DIR_OBJS)/rcon.o:  $(DIR_SOURCE)/rcon.c $(DIR_SOURCE)/rcon.h $(DIR_SOURCE)/definitions.h
#	$(CC) $(CFLAGS) -c $(DIR_SOURCE)/rcon.c -o $(DIR_OBJS)/rcon.o

$(DIR_OBJS)/Key.o:  $(DIR_SOURCE)/Key.cpp  $(DIR_SOURCE)/Key.h $(DIR_SOURCE)/definitions.h
	$(CC) $(CFLAGS) -c $(DIR_SOURCE)/Key.cpp -o $(DIR_OBJS)/Key.o

clean:
	$(RM) $(EXE_NAME) $(DIR_OBJS)/*.o core

