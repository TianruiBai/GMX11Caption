# Makefile for GMX11Caption

CC = g++
CFLAGS = -O2 -fPIC -Wall
LDFLAGS = -shared
LIBS = -lX11
TARGET = libgmx11caption.so

.PHONY: all lib test clean install help

all: lib test

lib: GMX11caption.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) GMX11caption.cpp $(LIBS)

test: lib test/test.cpp
	$(CC) -O2 -o test/gmx11_test test/test.cpp -L. -lgmx11caption -Wl,-rpath,.

clean:
	rm -f $(TARGET) test/gmx11_test

install: lib
	install -m 0755 $(TARGET) /usr/local/lib/
	@echo "Run ldconfig as root if needed: sudo ldconfig"

help:
	@echo "Targets:"
	@echo "  all   - build library and test"
	@echo "  lib   - build shared library $(TARGET)"
	@echo "  test  - build test program (links to local .)"
	@echo "  install - install library to /usr/local/lib (requires sudo)"
	@echo "  clean - remove build products"
