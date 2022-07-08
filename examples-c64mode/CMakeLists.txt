cmake_minimum_required(VERSION 3.18)
set(LLVM_MOS_PLATFORM c64)
find_package(llvm-mos-sdk REQUIRED)
project(myproject VERSION 0.1.0 LANGUAGES C ASM)
include(cmake/CPM.cmake)

find_package(mega65libc REQUIRED)

add_compile_options(-mcpu=mos6502 -Os)# -Wall -Wextra -Wshadow -Wno-language-extension-token)

add_executable(plasma plasma.c)
target_link_libraries(plasma mega65libc::mega65libc)
set_target_properties(plasma PROPERTIES OUTPUT_NAME plasma.prg)


