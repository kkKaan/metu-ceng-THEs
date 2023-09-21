CC = gcc
CFLAGS =
TARGET = bgame
SOURCES = bgame.c logging.c message.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)