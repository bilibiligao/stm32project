# ==============================================================================
# STM32N647 LED Blinky - Makefile (ARM GCC)
# ==============================================================================

# Toolchain
TOOLS_DIR = e:/STM32/cubeide/STM32CubeIDE_2.1.1/STM32CubeIDE/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.14.3.rel1.win32_1.0.100.202602081740/tools
CC       = $(TOOLS_DIR)/bin/arm-none-eabi-gcc
AS       = $(TOOLS_DIR)/bin/arm-none-eabi-gcc
LD       = $(TOOLS_DIR)/bin/arm-none-eabi-gcc
OBJCOPY  = $(TOOLS_DIR)/bin/arm-none-eabi-objcopy
OBJDUMP  = $(TOOLS_DIR)/bin/arm-none-eabi-objdump
SIZE     = $(TOOLS_DIR)/bin/arm-none-eabi-size
GDB      = $(TOOLS_DIR)/bin/arm-none-eabi-gdb

# Debug/flash tools
CUBEIDE_HOME = e:/STM32/cubeide/STM32CubeIDE_2.1.1/STM32CubeIDE/plugins
GDB_SERVER = $(CUBEIDE_HOME)/com.st.stm32cube.ide.mcu.externaltools.stlink-gdb-server.win32_2.2.400.202601091506/tools/bin/ST-LINK_gdbserver
PROG_CLI   = $(CUBEIDE_HOME)/com.st.stm32cube.ide.mcu.externaltools.cubeprogrammer.win32_2.2.400.202601091506/tools/bin/STM32_Programmer_CLI

# Project name
TARGET = appli
BUILD_DIR = build

# ----------------------------------------------------------------------------
# Source files
# ----------------------------------------------------------------------------
# HAL Library sources
HAL_SRC = \
    Drivers/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal.c \
    Drivers/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_cortex.c \
    Drivers/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_gpio.c \
    Drivers/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_rcc.c \
    Drivers/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_rcc_ex.c \
    Drivers/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_pwr.c \
    Drivers/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_pwr_ex.c \
    Drivers/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_rif.c \
    Drivers/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_exti.c \
    Drivers/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_dma.c \
    Drivers/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_dma_ex.c

# Application sources
APP_SRC = \
    Appli/Core/Src/main.c \
    Appli/Core/Src/stm32n6xx_hal_msp.c \
    Appli/Core/Src/stm32n6xx_it.c \
    Appli/Core/Src/system_stm32n6xx_s.c \
    Appli/Core/Src/secure_nsc.c \
    Drivers/BSP/LED/led.c

# Startup (assembly)
STARTUP_SRC = STM32CubeIDE/Appli/Application/User/Startup/startup_stm32n647x0hxq.s

# Linker script (default: LRUN for RAM)
LDSCRIPT     = STM32CubeIDE/Appli/STM32N647X0HXQ_LRUN.ld
# ROM linker script (for NOR Flash via XSPI2)
LDSCRIPT_ROM = STM32CubeIDE/Appli/STM32N647X0HXQ_ROMxspi2.ld
# External loader for NOR Flash programming
STLDR        = e:/STM32/STM32N647/Software_Package/External_Loader/MX25UM25645G_ATK-CNN647B/Binary/MX25UM25645G_ATK-CNN647B_ExtMemLoader.stldr

# All C sources
C_SRCS = $(HAL_SRC) $(APP_SRC)
ASM_SRCS = $(STARTUP_SRC)

# Object files
C_OBJS = $(addprefix $(BUILD_DIR)/, $(C_SRCS:.c=.o))
ASM_OBJS = $(addprefix $(BUILD_DIR)/, $(ASM_SRCS:.s=.o))
OBJS = $(C_OBJS) $(ASM_OBJS)

# ----------------------------------------------------------------------------
# Include paths
# ----------------------------------------------------------------------------
INC_DIRS = \
    -IDrivers/CMSIS/Core/Include \
    -IDrivers/CMSIS/Device/ST/STM32N6xx/Include \
    -IDrivers/STM32N6xx_HAL_Driver/Inc \
    -IDrivers/BSP/LED \
    -IAppli/Core/Inc \
    -ISecure_nsclib

# ----------------------------------------------------------------------------
# Compiler & Linker flags
# ----------------------------------------------------------------------------
CPUFLAGS   = -mcpu=cortex-m55 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16
ASFLAGS    = $(CPUFLAGS) -x assembler-with-cpp
CFLAGS     = $(CPUFLAGS) -mcmse -DSTM32N647xx
CFLAGS    += -Wall -Wextra -g3 -O0 -ffunction-sections -fdata-sections
CFLAGS    += $(INC_DIRS)
LDFLAGS    = $(CPUFLAGS) -T$(LDSCRIPT) -Wl,--gc-sections -Wl,-Map=$(BUILD_DIR)/$(TARGET).map
LDFLAGS   += --specs=nosys.specs --specs=nano.specs -Wl,--cref

# ----------------------------------------------------------------------------
# Build rules
# ----------------------------------------------------------------------------
.PHONY: all clean hex info flash debug debug-server rom flash-rom

all: $(BUILD_DIR)/$(TARGET).elf hex info

$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	@echo "Linking $@"
	@mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(BUILD_DIR)/%.o: %.s
	@echo "AS  $<"
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.c
	@echo "CC  $<"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

hex: $(BUILD_DIR)/$(TARGET).hex

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O ihex $< $@
	@echo "Generated $@"

info: $(BUILD_DIR)/$(TARGET).elf
	$(SIZE) $<

clean:
	rm -rf $(BUILD_DIR)

# ----------------------------------------------------------------------------
# Flash & Debug targets
# ----------------------------------------------------------------------------

# 烧录 hex 到开发板 (不改跳线帽: Development boot 模式 + 烧录到 0x34000000)
flash: $(BUILD_DIR)/$(TARGET).hex
	@echo "Flashing $(TARGET).hex ..."
	$(PROG_CLI) -c port=SWD -w $< -v

# 直接加载 LRUN ELF 到 RAM 并运行 (不改跳线帽, 利用 FSBL 预初始化)
# Reset_Handler 地址从 ELF 中提取, SP 从链接脚本确定 (_estack)
run: $(BUILD_DIR)/$(TARGET).elf
	@echo "=== 加载并运行 $(TARGET) ==="
	@echo "  BOOT = Development boot (B1→3V3), FSBL 必须已烧录"
	@# 从 ELF 提取 Reset_Handler 地址
	@RST_ADDR=$$($(OBJDUMP) -t $< | grep "Reset_Handler$$" | awk '{print "0x"$$1}'); \
	SP=$$($(OBJDUMP) -t $< | grep " _estack$$" | awk '{print "0x"$$1}'); \
	echo "  SP = $$SP, Reset_Handler = $$RST_ADDR"; \
	$(PROG_CLI) -c port=SWD -halt \
	  -w $(BUILD_DIR)/$(TARGET).hex \
	  -coreReg MSP=$$SP PC=$$RST_ADDR \
	  -run; \
	echo "=== 运行中, LED 应交替闪烁 ==="

# 启动 ST-LINK GDB Server (后台运行, 端口 61234)
debug-server:
	@echo "Starting ST-LINK GDB Server on port 61234 ..."
	@echo "Leave this running, then in another terminal: make debug"
	$(GDB_SERVER) -p 61234 -d -v

# GDB 调试: 连接 GDB Server + 加载 ELF + break main
# 前提: BOOT = Development boot (B1 → 3V3), debug-server 已启动
debug: $(BUILD_DIR)/$(TARGET).elf
	$(GDB) -x debug.gdb $<

# 一键调试: 先启动 GDB Server, 再自动连接 GDB
debug-all: $(BUILD_DIR)/$(TARGET).elf
	@echo "=== 一键调试模式 ==="
	@echo "确保: BOOT = Development boot (B1 → 3V3), FSBL 已烧录"
	@echo ""
	@echo "请在另一个终端运行: make debug-server"
	@echo "然后手动: make debug"
	@echo ""
	@echo "或者两步走:"
	@echo "  终端1: make debug-server"
	@echo "  终端2: make debug"

# ----------------------------------------------------------------------------
# ROM build (for NOR Flash, loaded by FSBL)
# ----------------------------------------------------------------------------
ROM_BUILD_DIR = build_rom
ROM_ELF = $(ROM_BUILD_DIR)/$(TARGET).elf
ROM_HEX = $(ROM_BUILD_DIR)/$(TARGET).hex

# ROM object files (same source, different build dir)
ROM_C_OBJS = $(addprefix $(ROM_BUILD_DIR)/, $(C_SRCS:.c=.o))
ROM_ASM_OBJS = $(addprefix $(ROM_BUILD_DIR)/, $(ASM_SRCS:.s=.o))
ROM_OBJS = $(ROM_C_OBJS) $(ROM_ASM_OBJS)

rom: $(ROM_HEX) rom-info

$(ROM_HEX): $(ROM_ELF)
	$(OBJCOPY) -O ihex $< $@
	@echo "Generated ROM $@"

$(ROM_ELF): $(ROM_OBJS)
	@echo "Linking ROM $@"
	@mkdir -p $(dir $@)
	$(LD) $(CPUFLAGS) -T$(LDSCRIPT_ROM) -Wl,--gc-sections -Wl,-Map=$(ROM_BUILD_DIR)/$(TARGET).map --specs=nosys.specs --specs=nano.specs -Wl,--cref -o $@ $(ROM_OBJS)

$(ROM_BUILD_DIR)/%.o: %.s
	@echo "AS  $<"
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

$(ROM_BUILD_DIR)/%.o: %.c
	@echo "CC  $<"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

rom-info: $(ROM_ELF)
	$(SIZE) $<

rom-clean:
	rm -rf $(ROM_BUILD_DIR)

# 烧录 ROM 版本到 NOR Flash (通过 External Loader, 不覆盖 FSBL)
flash-rom: $(ROM_HEX)
	@echo "Flashing $(ROM_HEX) to NOR Flash via External Loader..."
	$(PROG_CLI) -c port=SWD -el "$(STLDR)" -w $< -v

# Dependency helpers
$(BUILD_DIR)/%.d: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MM -MF $@ $<

ifneq ($(MAKECMDGOALS),clean)
-include $(addprefix $(BUILD_DIR)/, $(C_SRCS:.c=.d))
endif
