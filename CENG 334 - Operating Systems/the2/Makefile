CC = gcc
CFLAGS = -lpthread
TARGET = hw2
SOURCES = hw2.c hw2_output.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)
