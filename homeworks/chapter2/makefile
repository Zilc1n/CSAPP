# 定义编译器，可以根据你的需要选择 gcc (for C) 或 g++ (for C++)
# Define the compiler, choose gcc (for C) or g++ (for C++) as needed
CC = clang++
# CC = g++

# 定义编译选项，例如 -Wall (显示所有警告), -g (生成调试信息)
# Define compilation flags, e.g., -Wall (show all warnings), -g (generate debug info)
CFLAGS = -Wall -g

# 定义链接选项，如果你的程序需要链接额外的库，可以在这里添加
# Define linker flags, add extra libraries here if your program needs them
LDFLAGS =

# .PHONY 声明 clean 是一个伪目标，避免与实际文件冲突
# .PHONY declares clean as a phony target, to avoid conflicts with actual files
.PHONY: clean all

# all 目标，用于默认编译所有可执行文件 (如果需要的话，可以扩展)
# The 'all' target, for compiling all executables by default (can be extended if needed)
all:

# 通用编译规则：将 .c 或 .cpp 文件编译成同名的可执行文件
# Generic compilation rule: compiles .c or .cpp files into executables with the same name
%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

%: %.cpp
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# clean 目标：删除所有生成的可执行文件和可能的 .o 文件
# clean target: removes all generated executables and potential .o files
clean:
	@echo "清理编译生成的文件..." # Print a message
	@rm -f *.o *~ a.out
	@find . -maxdepth 1 -type f -executable -print0 | xargs -0 rm -- # 删除当前目录下所有可执行文件
	@echo "清理完成。" # Print a completion message
