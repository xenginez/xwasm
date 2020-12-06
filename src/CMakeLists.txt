# CMakeList.txt: xwasm 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 将源代码添加到此项目的可执行文件。
add_library (xwasm SHARED "types.h" "endian.cpp" "executor.cpp" "loader.cpp" "module.cpp" "runtime.cpp" "sandbox.cpp" "section_t.cpp" "stream.cpp" "value.cpp")

target_compile_definitions(xwasm PRIVATE -DXWASM_EXPORT)

set(	INSTALL_HEAD_FILES
		${CMAKE_SOURCE_DIR}/src/endian.h 
		${CMAKE_SOURCE_DIR}/src/module.h 
		${CMAKE_SOURCE_DIR}/src/sandbox.h 
		${CMAKE_SOURCE_DIR}/src/section_t.h 
		${CMAKE_SOURCE_DIR}/src/stream.h 
		${CMAKE_SOURCE_DIR}/src/types.h 
		${CMAKE_SOURCE_DIR}/src/value.h 
		${CMAKE_SOURCE_DIR}/src/xwasm.h
)

install(TARGETS xwasm
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
)
install(
		FILES ${INSTALL_HEAD_FILES} DESTINATION include/xwasm
)
