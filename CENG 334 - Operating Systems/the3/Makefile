CC = gcc

CFLAGS = -g -DTIMESTAMP=0x12345678



TARGET = je2fs

SOURCES = je2fs.c



all: $(TARGET)



$(TARGET): $(SOURCES)

	$(CC) $(SOURCES) $(CFLAGS) -o $(TARGET)



clean:

	rm -f $(TARGET)

