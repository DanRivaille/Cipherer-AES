#Compilador a usar
CC = g++

#Opciones de compilacion
CFLAGS = -w

#Rutas de directorios
DIR_OBJS = bin
DIR_SOURCE = source

#Nombre de los ejecutables y ficheros objetos usados
EXE_NAME = main
OBJS_FILES = $(DIR_SOURCE)/main.cpp  $(DIR_OBJS)/Tables.o $(DIR_OBJS)/Cipher.o

$(EXE_NAME): $(OBJS_FILES)
	$(CC) $^ $(CFLAGS) -o $(EXE_NAME)

$(DIR_OBJS)/Cipher.o: $(DIR_SOURCE)/Cipher.cpp  $(DIR_SOURCE)/Cipher.h $(DIR_SOURCE)/definitions.h
	$(CC) $(CFLAGS) -c $(DIR_SOURCE)/Cipher.cpp -o $(DIR_OBJS)/Cipher.o

$(DIR_OBJS)/Tables.o:  $(DIR_SOURCE)/Tables.cpp  $(DIR_SOURCE)/Tables.h
	$(CC) $(CFLAGS) -c $(DIR_SOURCE)/Tables.cpp -o $(DIR_OBJS)/Tables.o

clean:
	$(RM) $(EXE_NAME) $(DIR_OBJS)/*.o core

