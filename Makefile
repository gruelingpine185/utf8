# library
lib_dir = $(bin_dir)
lib_name := utf8
lib_ext =
lib_full = $(lib_dir)/lib$(lib_name).$(lib_ext)

# paths
inc_dir := inc/$(lib_name)
src_dir := src
bin_dir := bin

# sources
c_headers := $(wildcard $(inc_dir)/*.h)
c_sources := $(wildcard $(src_dir)/*.c)
c_objects := $(patsubst $(src_dir)/%.c, $(bin_dir)/%.o, $(c_sources))

# compiler
c_std := -std=c11
c_opt := -O2
c_wrn := -Wall -Wextra -pedantic
c_inc := -I$(inc_dir)
CC ?= clang
CFLAGS := $(c_std) $(c_opt) $(c_wrn)

os := $(shell uname -s)
ifeq ($(os), Darwin)
	lib_ext = dylib
endif # Darwin
ifeq ($(os), Linux)
	lib_ext = so
endif # Linux


.PHONY: all clean
all:
	@$(MAKE) $(lib_full)
clean:
	-rm -rf $(wildcard $(bin_dir) *.$(lib_full) *.o)

$(lib_full): $(c_objects)
	$(CC) $(CFLAGS) -shared $^ -o $@

$(bin_dir)/%.o: $(src_dir)/%.c $(wildcard $(inc_dir)/%.h) $(bin_dir)
	$(CC) $(CFLAGS) $(c_inc) -fpic -c $< -o $@

$(bin_dir):
	-mkdir $@
