# STM32N647 调试脚本 - GDB 命令文件
# 用法: make debug
# 前提: BOOT = Development boot (B1 → 3V3), FSBL 已烧录

# 连接到 ST-LINK GDB Server
target extended-remote localhost:61234

# 复位并停止 CPU
monitor reset
monitor halt

# 加载 ELF (GDB 自动解析入口地址)
load

# 设置断点在 main
break main

# 运行到 main
continue

# 提示
echo === 已连接到 STM32N647 ===\n
echo === break 在 main, 输入 c 继续运行, ctrl+c 暂停 ===\n
