SOURCES = main.cpp text_farter.cpp
COMPILER = gcc
TARGET = TextFarter

static:
	@#$(COMPILER) $(SOURCES) -D BUILD_STATIC -static -L../depndencies/include -lmy -o app-static
	$(COMPILER) $(SOURCES) -D BUILD_STATIC -o $(TARGET)-static

shared:
	$(COMPILER) $(SOURCES) -D BUILD_DYNAMIC -ldl -o $(TARGET)-shared

clean:
	rm -f *.o
	rm -f $(TARGET)*

