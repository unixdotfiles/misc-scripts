.SUFFIXES: .so .dylib
.c.so:
	$(CC) $(CLFAGS) $(LDFLAGS) -shared $< -o $@
.c.dylib:
	$(CC) $(CLFAGS) $(LDFLAGS) -dynamiclib $< -o $@
all:	leak.so leak.dylib
clean:
	rm -vf *.so *.dylib

