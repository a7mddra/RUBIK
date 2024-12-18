CC = /usr/bin/gcc-13
CFLAGS = -fdiagnostics-color=always -g
LDFLAGS = -lm

SRCS = main.c terminal/colors.c

OUT = main

all: $(OUT)

$(OUT): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)

run: $(OUT)
	./$(OUT)
