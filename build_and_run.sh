#!/bin/bash
# ==============================================================================
# STM32N647 LED Blinky - 一键编译 & 运行
# ==============================================================================
set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

# 工具路径
MAKE="e:/STM32/cubeide/STM32CubeIDE_2.1.1/STM32CubeIDE/plugins/com.st.stm32cube.ide.mcu.externaltools.make.win32_2.2.100.202601091506/tools/bin/make.exe"
GCC_BIN="e:/STM32/cubeide/STM32CubeIDE_2.1.1/STM32CubeIDE/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.14.3.rel1.win32_1.0.100.202602081740/tools/bin"
PROG_CLI="e:/STM32/cubeide/STM32CubeIDE_2.1.1/STM32CubeIDE/plugins/com.st.stm32cube.ide.mcu.externaltools.cubeprogrammer.win32_2.2.400.202601091506/tools/bin/STM32_Programmer_CLI.exe"

export PATH="$GCC_BIN:$PATH"

# Step 1: 清理 & 编译
echo "============================================"
echo "  Step 1/3: 编译 LRUN 版本..."
echo "============================================"
"$MAKE" clean
"$MAKE"

# Step 2: 从 ELF 提取 SP 和 Reset_Handler
echo ""
echo "============================================"
echo "  Step 2/3: 提取向量表地址..."
echo "============================================"
ELF="build/appli.elf"
HEX="build/appli.hex"

SP=$("$GCC_BIN/arm-none-eabi-objdump" -t "$ELF" | grep " _estack$" | awk '{print "0x"$1}')
RST=$("$GCC_BIN/arm-none-eabi-objdump" -t "$ELF" | grep "Reset_Handler$" | awk '{print "0x"$1}')

echo "  SP (top of stack)    = $SP"
echo "  PC (Reset_Handler)   = $RST"

# Step 3: 烧录 & 运行
echo ""
echo "============================================"
echo "  Step 3/3: SWD 烧录 & 运行..."
echo "============================================"
"$PROG_CLI" -c port=SWD \
  -halt \
  -w "$HEX" \
  -coreReg "MSP=$SP" "PC=$RST" \
  -run

echo ""
echo "============================================"
echo "  完成. LED0/LED1 应交替闪烁 (500ms)."
echo "============================================"
