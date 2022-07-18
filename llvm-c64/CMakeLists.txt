cmake_minimum_required(VERSION 3.18)
set(LLVM_MOS_PLATFORM c64)
find_package(llvm-mos-sdk REQUIRED)
project(myproject VERSION 0.1.0)

find_package(mega65libc REQUIRED)
find_program(BSA NAMES bsa HINTS ~/bin ~/opt/bin)
find_program(CA65 NAMES cl65)
find_program(CC65 NAMES cc65)
find_program(CL65 NAMES cl65 REQUIRED)
find_program(VICE NAMES x64sc HINTS /opt/homebrew/opt/vice/bin/)

add_compile_options(-mcpu=mos6502 -Os -Wall -Wextra -Wshadow -Wno-language-extension-token)

#
# For targets that require mega65libc, add:
#    target_link_libraries(mytarget mega65libc::mega65libc)
#

# plasma
add_executable(plasma plasma.c)
set_target_properties(plasma PROPERTIES OUTPUT_NAME plasma_llvm.prg)
add_custom_target(plasma_cc65 ALL COMMAND ${CL65} -t c64 -O -o plasma_cc65.prg plasma.c)

# raster-interrupt1
add_executable(raster-interrupt1 raster-interrupt1.cpp)
set_target_properties(raster-interrupt1 PROPERTIES OUTPUT_NAME raster-interrupt1.prg)

# raster-interrupt2
add_executable(raster-interrupt2 raster-interrupt2.cpp)
set_target_properties(raster-interrupt2 PROPERTIES OUTPUT_NAME raster-interrupt2.prg)

