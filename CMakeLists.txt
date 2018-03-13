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

add_executable(asm include/op.h include/asm.h
  src/asm/parser.c)
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
  src/vm/vm.c
  src/nc/exit.c
  src/nc/init.c
  src/nc/notify.c
  src/nc/update.c)
set_property(TARGET corewar PROPERTY C_STANDARD 90)
target_include_directories(corewar PUBLIC include)
target_link_libraries(corewar PUBLIC debug ft)

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
