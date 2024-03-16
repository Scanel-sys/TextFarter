COMPILER = gcc

all : clean static shared

static:
	cd zlib-1.3.1
	configure* --static
	cd ..
	make -C zlib-1.3.1 static
	
shared:
	cd zlib-1.3.1
	configure* --shared
	cd ..
	make -C zlib-1.3.1 shared

clean:
	make -C zlib-1.3.1 clean