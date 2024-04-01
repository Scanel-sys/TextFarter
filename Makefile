CC = gcc

TARGET = TextFarter

BUILDDIR = build
SRC_DIR=src
LIBS_SRC_DIR=libs_src
LOADER_DIR=elfloader

build_dir:
	mkdir -pv $(BUILDDIR)/bin/
	mkdir -pv $(BUILDDIR)/obj/

make_static_dirs:
	mkdir -pv $(BUILDDIR)/deps/static/

make_shared_dirs:
	mkdir -pv $(BUILDDIR)/deps/shared/


cp_static_lib_builds:
	cp -r $(LIBS_SRC_DIR)/build/obj/* build/obj/
	cp  $(LIBS_SRC_DIR)/build/*.a build/deps/static/

cp_shared_lib_builds:
	cp -r $(LIBS_SRC_DIR)/build/obj/* build/obj/
	cp  $(LIBS_SRC_DIR)/build/*.so build/deps/shared/

cp_project_files:
	cp -f $(SRC_DIR)/bin/$(TARGET)-* $(BUILDDIR)/bin/
	cp -r $(SRC_DIR)/res $(BUILDDIR)

all : clean static shared blob

static :
	$(MAKE) build_dir
	$(MAKE) make_static_dirs
	$(MAKE) -C $(LIBS_SRC_DIR) static
	$(MAKE) cp_static_lib_builds 
	$(MAKE) -C $(SRC_DIR) static
	$(MAKE) cp_project_files
	
shared : 
	$(MAKE) build_dir
	$(MAKE) make_shared_dirs
	$(MAKE) -C $(LIBS_SRC_DIR) shared 
	$(MAKE) cp_shared_lib_builds
	$(MAKE) -C $(SRC_DIR) shared
	$(MAKE) cp_project_files

blob :
	$(MAKE) build_dir
	$(MAKE) make_static_dirs
	$(MAKE) -C $(LIBS_SRC_DIR) static 
	$(MAKE) cp_static_lib_builds 
	$(MAKE) -C $(SRC_DIR) blob
	gcc $(LOADER_DIR)/elf_loader.c $(LOADER_DIR)/main.c $(LOADER_DIR)/wheelc/list.c -lm -ldl -o $(BUILDDIR)/bin/$(TARGET)-loader
	$(MAKE) cp_project_files


clean :
	$(MAKE) -C $(LIBS_SRC_DIR) clean
	$(MAKE) -C $(SRC_DIR) clean
	$(MAKE) -C $(LOADER_DIR) clean
	rm -rf build
