cmake_minimum_required(VERSION 3.18)

#====================================================================== 
#=== Configuration Parameters

#====================================================================== 
#=== Configuration Setup

#====================================================================== 
#=== Project Setup

project(kabibe
  VERSION     0.1.0
  DESCRIPTION "Shell style assembler library."
  LANGUAGES   C
)

add_library(${PROJECT_NAME} STATIC
  "include/kabibe/types.h"

  "include/kabibe/kabibe.h"
  "src/kabibe.c"

  "include/kabibe/arch/x86_64.h"
  "src/x86_64.c"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  C_STANDARD 17
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE metapp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC "include/"
)

target_compile_options(${PROJECT_NAME}
  PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall -Wextra -Wpedantic -Werror -Wsign-conversion -Wconversion>
    $<$<CXX_COMPILER_ID:MSVC>: /W4 /WX>
)
