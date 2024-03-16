TOP_DIR        := /mnt/c/Users/scanel/Desktop/src/study/3_course/2 sem/ТРСПО/1/text_farter/libs_src/freetype-2.13.2
OBJ_DIR        := /mnt/c/Users/scanel/Desktop/src/study/3_course/2 sem/ТРСПО/1/text_farter/libs_src/freetype-2.13.2
OBJ_BUILD      := $(OBJ_DIR)
DOC_DIR        := $(OBJ_DIR)/docs
FT_LIBTOOL_DIR := $(OBJ_DIR)
ifndef FT2DEMOS
  include $(TOP_DIR)/Makefile
else
  TOP_DIR_2 := $(TOP_DIR)/../ft2demos
  PROJECT   := freetype
  CONFIG_MK := $(OBJ_DIR)/config.mk
  include $(TOP_DIR_2)/Makefile
endif
