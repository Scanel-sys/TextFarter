CC = gcc
LIBS = -lfreetype -lpng -lzip -lm
DEPS_DIR=../build/deps
LIBS_DIR=../libs_src
CFLAGS = -I$(LIBS_DIR)/zlib/ -I$(LIBS_DIR)/libpng/ -I$(LIBS_DIR)/freetype/include/ -I$(LIBS_DIR)/freetype/include/freetype
LDFLAGS = -L$(DEPS_DIR)/static/
CFLAGS_BLOB = -fno-stack-protector -nostdlib -pie -fPIE -lm -fPIC -shared -e main -D BUILD_BLOB

SRC=text_farter.c
TARGET = TextFarter

INCLUDES= -I $(LIBS_DIR)/freetype/include -I $(LIBS_DIR)/libpng
BLOB_LIBS= $(DEPS_DIR)/static/libpng.a $(DEPS_DIR)/static/libzip.a $(DEPS_DIR)/static/libfreetype.a

mk_build:
	mkdir -pv bin

static :
	$(MAKE) mk_build
	$(CC) $(CFLAGS) $(LDFLAGS) -D BUILD_STATIC $(SRC) -o bin/$(TARGET)-static $(LIBS)

shared :
	$(MAKE) mk_build
	$(CC) $(SRC) $(CFLAGS) -D BUILD_DYNAMIC -ldl -o bin/$(TARGET)-shared 

blob :
	$(MAKE) mk_build
	$(CC) $(SRC) $(INCLUDES) $(BLOB_LIBS) $(CFLAGS_BLOB) -o bin/$(TARGET)-blob
	


clean:
	rm -rf bin