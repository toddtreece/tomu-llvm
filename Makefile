PREFIX    ?=
PRJ       := llvm-tomu
LDSCRIPT  := tomu.ld
OPT_LEVEL := z
ARCH      := cortex-m0plus
C_STD     := c11
DBG_LEVEL := 3
Q         :=@

OUT := out
CSRC:= $(wildcard src/*.c)
OBJ := $(addprefix $(OUT)/, $(CSRC:.c=.o))

CC = $(PREFIX)clang
LD = $(PREFIX)ld.lld
SIZE = $(PREFIX)llvm-size
COPY = $(PREFIX)llvm-objcopy
DUMP = $(PREFIX)llvm-objdump

TARGET:=$(OUT)/$(PRJ).elf
TARGET_LST:=$(OUT)/$(PRJ).lst
TARGET_BIN:=$(OUT)/$(PRJ).bin
TARGET_MAP:=$(OUT)/$(PRJ).map
TARGET_DFU:=$(OUT)/$(PRJ).dfu

ARCH_FLAGS := --target=armv6-none-eabi
ARCH_FLAGS += -mthumb
ARCH_FLAGS += -march=armv6m
ARCH_FLAGS += -mcpu=cortex-m0plus
ARCH_FLAGS += -mfloat-abi=soft
ARCH_FLAGS += -mfpu=none

CFLAGS := $(ARCH_FLAGS)
CFLAGS += -I./includes
CFLAGS += -ffreestanding
CFLAGS += -O$(OPT_LEVEL)
CFLAGS += -std=$(C_STD)
CFLAGS += -Wall
CFLAGS += -g$(DBG_LEVEL)

LDFLAGS := --Bstatic
LDFLAGS += --build-id
LDFLAGS += --gc-sections
LDFLAGS += --Map $(TARGET_MAP)
LDFLAGS += --script $(LDSCRIPT)

all: $(TARGET_BIN) $(TARGET_LST) $(TARGET_DFU) size

$(OUT)/%.o: %.c
	@echo CC $^
	@mkdir -p $(dir $@)
	$(Q)$(CC) -o $@ $(CFLAGS) -c $<

$(TARGET): $(OBJ)
	@echo LD $@
	$(Q)$(LD) -o $@ $(LDFLAGS) $(OBJ)

$(TARGET_LST): $(TARGET)
	@echo LIST on $@
	$(Q)$(DUMP) -s -S $< > $@

$(TARGET_BIN): $(TARGET)
	@echo COPY to $@
	$(Q)$(COPY) -O binary $< $@

$(TARGET_DFU): $(TARGET)
	@echo DFU to $@
	$(Q)$(COPY) $(TARGET) $@
	$(Q)dfu-suffix -v 1209 -p 70b1 -a $@

size: $(TARGET)
	$(Q)$(SIZE) $<

clean:
	@echo CLEAN
	@rm -fR $(OUT)

rebuild: clean all

flash: rebuild
	@echo DOWNLOAD
	$(Q)dfu-util --download $(TARGET_DFU)

.PHONY: all clean list size rebuild flash
