CC = gcc
SDL = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lm 
TARGET = simple-slot-machine
SRCDIR = src/
OBJDIR = build/obj/
OBJECTS = build/obj/main.o build/obj/sprites.o build/obj/rates.o

$(TARGET): $(OBJECTS)
	$(CC) $(CCFLAGS) $^ -o $(TARGET) ${SDL}
	
$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(OBJDIR)
	$(CC) -c $^ -o $@
