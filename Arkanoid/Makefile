# Constantes
name = Arkanoid
src = $(wildcard src/*.c)
obj = $(src:.c=.o)
dest = build/

# Flags GCC
LDFLAGS = -lSDL2 -Wall 

$(name): $(obj)
	$(CC) -o $(dest)$@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) $(dest)$(name)