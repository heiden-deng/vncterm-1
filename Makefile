TARGET = vncterm

OBJS := main.o console.o

LIBS_so := libvnc/libvnc.so
LIBS := libvnc/libvnc.a

ifeq ($(shell uname),Linux)
LDLIBS := -lutil
endif

XEN_ARCH := x86
XEN_TARGET := xen

CFLAGS  = -I$(shell pwd)/include
# _GNU_SOURCE for asprintf.
CFLAGS += -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_GNU_SOURCE
CFLAGS += -Wall -Werror -g -O1

# Get gcc to generate the dependencies for us.
CFLAGS   += -Wp,-MD,$(@D)/.$(@F).d

SUBDIRS  = $(filter-out ./,$(dir $(OBJS) $(LIBS)))
DEPS     = .*.d

LDFLAGS := -g

all: $(TARGET)

$(TARGET): $(LIBS) $(OBJS)
	gcc -o $@ $(LDFLAGS) $(OBJS) $(LIBS) $(LDLIBS)

%.o: %.c
	gcc -o $@ $(CFLAGS) -c $<

$(LIBS_so): %.so: ALWAYS
	$(MAKE) -C $(*D)

$(LIBS): %.a: ALWAYS
	$(MAKE) -C $(*D)

.PHONY: ALWAYS

clean:
	$(foreach dir,$(SUBDIRS),make -C $(dir) clean)
	rm -f $(OBJS)
	rm -f $(DEPS)
	rm -f $(TARGET)
	rm -f TAGS

.PHONY: TAGS
TAGS:
	find . -name \*.[ch] | etags -

-include $(DEPS)

print-%:
	echo $($*)