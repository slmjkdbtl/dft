# wengwengweng

CC := clang
CFLAGS += -Iext
PREFIX := /usr/local
TARGETS := dimg dsnd dfnt

.PHONY: all
all: dimg dsnd dfnt

%: %.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: install
install: dimg dsnd dfnt
	install dimg $(PREFIX)/bin
	install dsnd $(PREFIX)/bin
	install dfnt $(PREFIX)/bin

.PHONY: clean
clean:
	rm -f dimg
	rm -f dsnd
	rm -f dfnt
	rm -f *.dimg
	rm -f *.dsnd
	rm -f *.dfnt

