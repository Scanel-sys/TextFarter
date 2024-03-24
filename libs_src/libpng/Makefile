CC = gcc

SOURCES = png.c pngerror.c pngget.c pngmem.c pngpread.c pngread.c pngrio.c \
pngrtran.c pngrutil.c pngset.c pngtrans.c pngwio.c pngwrite.c pngwtran.c pngwutil.c

ZLIBSOURCES = ../zlib/adler32.c ../zlib/crc32.c ../zlib/deflate.c ../zlib/infback.c \
../zlib/inffast.c ../zlib/inflate.c ../zlib/inftrees.c ../zlib/trees.c ../zlib/zutil.c \
../zlib/compress.c ../zlib/uncompr.c

OBJECTS = $(SOURCES:.c=.o)
ZLIBOBJECTS = $(ZLIBSOURCES:.c=.o)

CFLAGS = -fno-stack-protector -fno-exceptions -pie -fPIE -c -O2 -fPIC

BUILDDIR = myBuild

STATICLIB = $(BUILDDIR)/libpng.a
DYNAMICLIB = $(BUILDDIR)/libpng.so


build_dir:
	mkdir -pv $(BUILDDIR)/obj

static: cp_libconf build_dir $(SOURCES) $(STATICLIB)

$(STATICLIB): $(OBJECTS)
	ar cr $@ $(BUILDDIR)/obj/*.o

shared: cp_libconf build_dir $(SOURCES) $(DYNAMICLIB)

$(DYNAMICLIB): $(OBJECTS) $(ZLIBOBJECTS)
	$(CC) -shared $(BUILDDIR)/obj/*.o -o $@

%.o : %.c
	$(CC) $(CFLAGS) -I../zlib $< -o $@
	mv -f $@ $(BUILDDIR)/obj

cp_libconf:
	cp scripts/pnglibconf.h.prebuilt pnglibconf.h 

clean:
	rm -rf $(BUILDDIR)
	rm pnglibconf.h