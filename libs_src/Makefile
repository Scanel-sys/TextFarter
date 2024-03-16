COMPILER = gcc

all : clean static shared

static:
	cd zlib-1.3.1 && \
	./configure --prefix=../../dependencies/ --static
	make -C zlib-1.3.1 static
	
shared:
	cd zlib-1.3.1 && \
	./configure --prefix=../../dependencies/ --shared
	make -C zlib-1.3.1 shared
	make -C zlib-1.3.1 install

clean:
	make -C zlib-1.3.1 clean
	make -C freetype-2.13.2 clean
	make -C lpng1643 clean
	cd ../dependencies && rm -rf include \
					   && rm -rf lib \
					   && rm -rf share