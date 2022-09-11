

CC	:= gcc
OBJCOPY	:= objcopy
ODIR	:= build
SDIR	:= source
IDIRS	:= -I$/include -Iinclude
LDIRS	:= -L$
MAPFILE := $(shell basename "$(CURDIR)").map
CFLAGS	:= $(IDIRS) -Os -std=c11 -ffunction-sections -fdata-sections -fno-builtin -nostartfiles -nostdlib -Wall -Wextra -masm=intel -march=btver2 -mtune=btver2 -m64 -mabi=sysv -mcmodel=small -fpie -fPIC
LFLAGS	:= $(LDIRS) -Xlinker -T linker.x -Xlinker -Map="$(MAPFILE)" -Wl,--build-id=none -Wl,--gc-sections
CFILES	:= $(wildcard $(SDIR)/*.c)
SFILES	:= $(wildcard $(SDIR)/*.s)
OBJS	:= $(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(CFILES)) $(patsubst $(SDIR)/%.s, $(ODIR)/%.o, $(SFILES))


TARGET = $(shell basename "$(CURDIR)").bin

$(TARGET): $(ODIR) $(OBJS)
	$(CC) crt0.s $(ODIR)/*.o -o temp.t $(CFLAGS) $(LFLAGS) $(LIBS)
	$(OBJCOPY) -O binary temp.t "$(TARGET)"
	rm -f temp.t

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.s
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR):
	@mkdir $@

.PHONY: clean

clean:
	rm -rf "$(TARGET)" "$(MAPFILE)" $(ODIR)
