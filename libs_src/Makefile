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


all : clean static shared

static : build_dir zlib_static freetype_static libpng_static cp_builds

shared : build_dir zlib_shared freetype_shared libpng_shared cp_builds


freetype_static :
	$(MAKE) -C freetype static
	
libpng_static :
	$(MAKE) -C libpng static

zlib_static :
	$(MAKE) -C zlib static

freetype_shared :
	$(MAKE) -C freetype shared

libpng_shared :
	$(MAKE) -C libpng shared

zlib_shared :
	$(MAKE) -C zlib shared


clean :
	$(MAKE) -C zlib clean
	$(MAKE) -C freetype clean 
	$(MAKE) -C libpng clean
	rm -rf $(BUILDDIR)
