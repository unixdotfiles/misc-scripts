CFLAGS+=-Weverything -Wno-sign-conversion -g -I/usr/local/include -I/opt/local/include 
LDFLAGS+=-lcrypto
PROGS=	telnetenable

all:	$(PROGS)
telnetenable: telnetenable.o blowfish.0
clean:
	rm -f $(PROGS)
