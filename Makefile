BINARY=app
CODEDIRS=src
LIBS=libs/

CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.c))
MACOS_INCLUDE=-framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL

OBJECTS=$(patsubst %.c,%.o,$(CFILES))

CFLAGS=-Wall -g
CC=clang

all: $(BINARY)
	./$(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -I$(LIBS) -L$(LIBS) $(MACOS_INCLUDE) libs/libraylib.a -o $@ $^

# $(BINARY): $(CFILES)
# 	$(CC) $(CFLAGS) $(MACOS_INCLUDE) $(LIBS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBS) -L$(LIBS) $(MACOS_INCLUDE) libs/libraylib.a -c -o $@ $^

clean:
	rm -rf $(BINARY) $(OBJECTS)
