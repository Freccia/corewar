cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(SET CMP0054 OLD)
cmake_policy(SET CMP0045 OLD)

project(corewar C)
add_subdirectory(libft)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}
  -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS_DEBUG}
  -fno-omit-frame-pointer -fsanitize=address")

file(GLOB_RECURSE corewar_HDRS ${corewar_HDRS} include/corewar/*.h)
file(GLOB_RECURSE corewar_HDRS ${corewar_HDRS} include/*.h)
file(GLOB_RECURSE vm_SRCS ${vm_SRCS} src/vm/*.c)

add_executable(asm ${corewar_HDRS}
  src/op.c
  src/asm/asm_main.c
  src/asm/init_data.c
  src/asm/error.c
  src/asm/encoder/asm_encoder.c
  src/asm/encoder/write_cor.c
  src/asm/lexer/asm_lexer.c
  src/asm/lexer/read_header.c
  src/asm/lexer/read_instruction.c
  src/asm/parser/asm_parser.c
  src/asm/parser/parse_args.c)
set_property(TARGET asm PROPERTY C_STANDARD 90)
target_include_directories(asm PUBLIC include)
target_link_libraries(asm PUBLIC debug ft)

target_compile_definitions(asm
  PRIVATE $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:NDEBUG>)
if (MSVC)
  target_compile_options(asm
    PRIVATE /MT$<$<CONFIG:Debug>:d> /Oy /W3
    PRIVATE /D_CRT_SECURE_NO_WARNINGS /Dinline=__inline
    PRIVATE /O$<$<CONFIG:Debug>:d>$<$<CONFIG:Release>:x>)
else ()
  target_compile_options(asm
    PRIVATE -Wall -Werror -Wextra
    PRIVATE -O$<$<CONFIG:Debug>:0 -g3>$<$<CONFIG:Release>:3>)
endif ()

add_executable(corewar ${corewar_HDRS}
  src/op.c
  src/utils.c
  ${vm_SRCS}
  src/vm/gui/internal.h
  src/vm/gui/exit.c
  src/vm/gui/init.c
  src/vm/gui/keys.c
  src/vm/gui/ui.c)
set_property(TARGET corewar PROPERTY C_STANDARD 90)
target_include_directories(corewar PUBLIC include)
target_link_libraries(corewar PUBLIC debug ft ncurses)

target_compile_definitions(corewar
  PRIVATE $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:NDEBUG>)
if (MSVC)
  target_compile_options(corewar
    PRIVATE /MT$<$<CONFIG:Debug>:d> /Oy /W3
    PRIVATE /D_CRT_SECURE_NO_WARNINGS /Dinline=__inline
    PRIVATE /O$<$<CONFIG:Debug>:d>$<$<CONFIG:Release>:x>)
else ()
  target_compile_options(corewar
    PRIVATE -Wall -Werror -Wextra
    PRIVATE -O$<$<CONFIG:Debug>:0 -g3>$<$<CONFIG:Release>:3>)
endif ()
