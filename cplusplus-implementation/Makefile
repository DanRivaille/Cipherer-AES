#Compilador a usar
CC = g++

#Opciones de compilacion
CFLAGS = -w

#Rutas de directorios
DIR_OBJS = bin
DIR_SOURCE = source

#Nombre de los ejecutables y ficheros objetos usados
EXE_NAME = main
OBJS_FILES = $(DIR_SOURCE)/main.cpp $(DIR_OBJS)/Key.o $(DIR_OBJS)/Sbox.o $(DIR_OBJS)/Rcon.o $(DIR_OBJS)/Tables.o

$(EXE_NAME): $(OBJS_FILES)
	$(CC) $^ $(CFLAGS) -o $(EXE_NAME)

$(DIR_OBJS)/Sbox.o: $(DIR_SOURCE)/Sbox.cpp  $(DIR_SOURCE)/Sbox.h $(DIR_SOURCE)/definitions.h
	$(CC) $(CFLAGS) -c $(DIR_SOURCE)/Sbox.cpp -o $(DIR_OBJS)/Sbox.o

$(DIR_OBJS)/Rcon.o:  $(DIR_SOURCE)/Rcon.cpp $(DIR_SOURCE)/Rcon.h $(DIR_SOURCE)/definitions.h
	$(CC) $(CFLAGS) -c $(DIR_SOURCE)/Rcon.cpp -o $(DIR_OBJS)/Rcon.o

$(DIR_OBJS)/Key.o:  $(DIR_SOURCE)/Key.cpp  $(DIR_SOURCE)/Key.h $(DIR_SOURCE)/definitions.h
	$(CC) $(CFLAGS) -c $(DIR_SOURCE)/Key.cpp -o $(DIR_OBJS)/Key.o

$(DIR_OBJS)/Tables.o:  $(DIR_SOURCE)/Tables.cpp  $(DIR_SOURCE)/Tables.h
	$(CC) $(CFLAGS) -c $(DIR_SOURCE)/Tables.cpp -o $(DIR_OBJS)/Tables.o

clean:
	$(RM) $(EXE_NAME) $(DIR_OBJS)/*.o core

