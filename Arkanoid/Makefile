# Constantes
name = Arkanoid
src = $(wildcard src/*.c)
obj = $(src:.c=.o)
dest = build/

# Flags GCC
LDFLAGS = -lSDL2 -Wall 

$(name): $(obj)
	$(CC) -o $(dest)$@ $^ $(LDFLAGS); make clean

.PHONY: clean
clean:
	rm -f $(obj) build/Arkanoid

.PHONY: run
run: 
	cd build; ./Arkanoid