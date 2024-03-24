CC = gcc

SOURCES = builds/unix/ftsystem.c src/autofit/autofit.c src/base/ftbase.c src/base/ftinit.c src/base/ftbitmap.c \
src/base/ftglyph.c src/truetype/truetype.c src/type1/type1.c src/cff/cff.c src/cid/type1cid.c src/pfr/pfr.c \
src/type42/type42.c src/winfonts/winfnt.c src/gzip/ftgzip.c src/lzw/ftlzw.c src/pcf/pcf.c src/psaux/psaux.c \
src/psnames/psnames.c src/pshinter/pshinter.c src/raster/raster.c src/sfnt/sfnt.c src/bdf/bdf.c \
src/base/ftdebug.c src/smooth/smooth.c src/sdf/sdf.c src/svg/svg.c src/base/ftmm.c

OBJECTS = $(SOURCES:.c=.o)

CFLAGS = -fno-stack-protector -fno-exceptions -pie -fPIE -c -O2 -fPIC \
 "-DFT_CONFIG_CONFIG_H=<ftconfig.h>" -DFT2_BUILD_LIBRARY -DHAVE_FCNTL_H \
 "-DFT_CONFIG_MODULES_H=<ftmodule.h>" "-DFT_CONFIG_OPTIONS_H=<ftoption.h>"

INCLUDE = -I./include/freetype/config -I./builds/unix -I./include -I./src -I../zlib

STATICLIB = libfreetype.a
DYNAMICLIB = libfreetype.so

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
	$(CC) $(INCLUDE) $(CFLAGS) $< -o $@ -DPIC
	mv -f $@ $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR)