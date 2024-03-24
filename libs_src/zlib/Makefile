CC = gcc

SOURCES = adler32.c crc32.c deflate.c infback.c inffast.c \
inflate.c inftrees.c trees.c zutil.c compress.c uncompr.c

OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -fno-stack-protector -fno-exceptions -pie -fPIE -c -O2 -fPIC

STATICLIB = libzip.a
DYNAMICLIB = libzip.so

BUILDDIR = myBuild

build_dir:
	mkdir -pv $(BUILDDIR)

static: build_dir $(SOURCES) $(STATICLIB)

$(STATICLIB): $(OBJECTS)
	ar cr $@ $(BUILDDIR)/*.o

shared: build_dir $(SOURCES) $(DYNAMICLIB)

$(DYNAMICLIB): $(OBJECTS)
	$(CC) -shared $(BUILDDIR)/*.o -o $@

%.o : %.c
	$(CC) $(CFLAGS) -DPIC $< -o $@
	mv -f $@ $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR)