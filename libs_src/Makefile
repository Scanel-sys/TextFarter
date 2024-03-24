CC = gcc

TARGET_STATIC = app_static
TARGET_DYNAMIC = app_dynamic

BUILDDIR = build


build_dir:
	mkdir -pv $(BUILDDIR)

cp_builds:
	cp -r zlib/myBuild/* $(BUILDDIR)
	cp -r freetype/myBuild/* $(BUILDDIR)
	cp -r libpng/myBuild/* $(BUILDDIR)


all : clean static dynamic

static : build_dir zlib_static freetype_static libpng_static cp_builds

shared : build_dir zlib_shared freetype_shared libpng_shared cp_builds


freetype_static :
	$(MAKE) -C freetype static
	# cp freetype/objs/.libs/libfreetype.a build/libfreetype.a
	
libpng_static :
	$(MAKE) -C libpng static
	# cp libpng/.libs/libpng16.a build/libpng16.a

freetype_shared :
	$(MAKE) -C freetype shared
	# cp freetype/objs/.libs/libfreetype.so build/libfreetype.so

libpng_shared :
	$(MAKE) -C libpng shared
	# cp libpng/.libs/libpng16.so build/libpng16.so

zlib_static :
	$(MAKE) -C zlib static

zlib_shared :
	$(MAKE) -C zlib shared


clean :
	$(MAKE) -C zlib clean
	$(MAKE) -C freetype clean 
	$(MAKE) -C libpng clean
	rm -r $(BUILDDIR)
