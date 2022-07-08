cmake_minimum_required(VERSION 3.18)
set(LLVM_MOS_PLATFORM mega65)
find_package(llvm-mos-sdk REQUIRED)
project(myproject VERSION 0.1.0 LANGUAGES C ASM)

find_package(mega65libc REQUIRED)
find_program(BSA NAMES bsa HINTS ~/bin ~/opt/bin)
find_program(CA65 NAMES cl65)
find_program(CC65 NAMES cc65)
find_program(CL65 NAMES cl65)


add_compile_options(-mcpu=mos6502 -Os -Wall -Wextra -Wshadow -Wno-language-extension-token)

add_executable(random-sid random-sid.c)
set_target_properties(random-sid PROPERTIES OUTPUT_NAME random-sid.prg)

