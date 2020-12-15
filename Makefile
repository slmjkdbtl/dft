# wengwengweng

CC := clang
CFLAGS += -Iext
PREFIX := /usr/local

.PHONY: all
all: dimg dsnd

dimg: d_img.c
	$(CC) $(CFLAGS) d_img.c -o dimg

dsnd: d_snd.c
	$(CC) $(CFLAGS) d_snd.c -o dsnd

.PHONY: install
install: dimg dsnd
	install dimg $(PREFIX)/bin
	install dsnd $(PREFIX)/bin

.PHONY: clean
clean: dimg dsnd
	rm dimg
	rm dsnd
	rm *.dimg
	rm *.dsnd

