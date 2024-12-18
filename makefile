CC = /usr/bin/gcc-13
CFLAGS = -fdiagnostics-color=always -g
LDFLAGS = -lm

SRCS_MAIN = main.c terminal/colors.c
SRCS_CUBE = cube.c terminal/colors.c

OUT_MAIN = main
OUT_CUBE = cube

all: $(OUT_MAIN) $(OUT_CUBE)

$(OUT_MAIN): $(SRCS_MAIN)
	$(CC) $(CFLAGS) $(SRCS_MAIN) -o $(OUT_MAIN) $(LDFLAGS)

$(OUT_CUBE): $(SRCS_CUBE)
	$(CC) $(CFLAGS) $(SRCS_CUBE) -o $(OUT_CUBE) $(LDFLAGS)

clean:
	rm -f $(OUT_MAIN) $(OUT_CUBE)

run: $(OUT_MAIN) $(OUT_CUBE)
	./$(OUT_MAIN)
	./$(OUT_CUBE)
