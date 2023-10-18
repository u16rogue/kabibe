cmake_minimum_required(VERSION 3.18)

#====================================================================== 
#=== Configuration Parameters

set(KABIBE_DEP_METAPP_DIR ""
  CACHE PATH
  "Path to the metapp library if target is not available on the parent project. (Existing project target if exist will be prefered by the configuration)"
)

#====================================================================== 
#=== Configuration Setup

# [18/10/2023] We will not be managing dependencies to prevent duplicate packages and versioning 
# hell It is also important that the metapp depedency is the exact same with its parent project
# to prevent mismatch in the ABI.
if (NOT TARGET metapp)
  if (KABIBE_DEP_METAPP_DIR STREQUAL "")
    message(FATAL_ERROR "-- kabibe > Target 'metapp' is not available and 'KABIBE_DEP_METAPP_DIR' is empty. Either import metapp on the parent project or manually configure 'KABIBE_DEP_METAPP_DIR' to point to metapp.")
  endif()
  add_subdirectory(${KABIBE_DEP_METAPP_DIR} "${CMAKE_CURRENT_BINARY_DIR}/metapp")
  if (NOT TARGET metapp)
    message(FATAL_ERROR "-- kabibe > Target 'metapp' failed to import from 'KABIBE_DEP_METAPP_DIR'=(${KABIBE_DEP_METAPP_DIR})")
  endif()
endif()

#====================================================================== 
#=== Project Setup

project(kabibe
  VERSION     0.1.0
  DESCRIPTION "Shell style assembler library."
  LANGUAGES   CXX
)

add_library(${PROJECT_NAME} STATIC
  "include/kabibe/kabibe.hh"
  "src/kabibe.cc"

  "include/kabibe/arch/x86_64.hh"
  "src/x86_64.cc"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 20
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
