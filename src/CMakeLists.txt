# CMakeList.txt: xwasm 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 将源代码添加到此项目的可执行文件。
#add_library (xwasm SHARED "opcode.h" "endian.cpp" "executor.cpp" "loader.cpp" "module.cpp" "sandbox.cpp" "section_t.cpp" "value.cpp" "stream.cpp" "runtime.cpp")
#target_compile_definitions(xwasm PRIVATE -DXWASM_EXPORT)

add_executable (xwasm "test.cpp" "opcode.h" "endian.cpp" "executor.cpp" "loader.cpp" "module.cpp" "sandbox.cpp" "section_t.cpp" "value.cpp" "stream.cpp" "runtime.cpp")


# TODO: 如有需要，请添加测试并安装目标。
