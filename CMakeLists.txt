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

add_executable(asm
  include/op.h
  include/asm.h
  include/asm/asm_util.h
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

add_executable(corewar include/op.h include/corewar.h
  src/op.c
  src/vm/vm.c
  src/vm/vm_init.c
  src/vm/cw_add.c
  src/vm/cw_aff.c
  src/vm/cw_and.c
  src/vm/cw_fork.c
  src/vm/cw_ld.c
  src/vm/cw_ldi.c
  src/vm/cw_lfork.c
  src/vm/cw_live.c
  src/vm/cw_lld.c
  src/vm/cw_lldi.c
  src/vm/cw_or.c
  src/vm/cw_st.c
  src/vm/cw_sti.c
  src/vm/cw_sub.c
  src/vm/cw_xor.c
  src/vm/cw_zjmp.c
  src/vm/vm_tools.c
  src/nc/internal.h
  src/nc/exit.c
  src/nc/init.c
  src/nc/notify.c
  src/nc/update.c)
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
