COMPILER = gcc
ZLIB_NAME = zlib-1.3.1
FREETYPE_NAME = freetype-2.13.2
LPNG_NAME = libpng-1.6.43


all : clean static shared

static:
	cd $(ZLIB_NAME) && \
	./configure --prefix=../../dependencies/ --static
	make -C $(ZLIB_NAME) static
	make -C $(ZLIB_NAME) install
	
shared:
	cd $(ZLIB_NAME) && \
	./configure --prefix=../../dependencies/ --shared
	make -C $(ZLIB_NAME) shared
	make -C $(ZLIB_NAME) install

clean:
	make -C $(ZLIB_NAME) clean
	cd ../dependencies && rm -rf include \
					   && rm -rf lib \
					   && rm -rf share