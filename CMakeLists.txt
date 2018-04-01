cmake_minimum_required(VERSION 3.4.3)

# If we are not building as a part of LLVM, build ppf as an
# standalone project, using LLVM as an external library:
if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
  project(ppf)
  ## FIXME unimplemented, look at Clang for an example
  message(FATAL_ERROR "We don't know how to build standalone yet")
else()
  set(BACKEND_PACKAGE_STRING "${PACKAGE_STRING}")
endif()

set(PPF_RESOURCE_DIR "" CACHE STRING
  "Relative directory from the ppf binary to its resource files.")

set(C_INCLUDE_DIRS "" CACHE STRING
  "Colon separated list of directories ppf will search for headers.")

set(GCC_INSTALL_PREFIX "" CACHE PATH "Directory where gcc is installed." )
set(DEFAULT_SYSROOT "" CACHE PATH
  "Default <path> to all compiler invocations for --sysroot=<path>." )

set(PPF_VENDOR "" CACHE STRING
  "Vendor-specific text for showing with version information.")

if( PPF_VENDOR )
  add_definitions( -DPPF_VENDOR="${PPF_VENDOR} " )
endif()

set(PPF_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PPF_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR AND NOT MSVC_IDE )
  message(FATAL_ERROR "In-source builds are not allowed. CMake would overwrite "
"the makefiles distributed with LLVM. Please create a directory and run cmake "
"from there, passing the path to this source directory as the last argument. "
"This process created the file `CMakeCache.txt' and the directory "
"`CMakeFiles'. Please delete them.")
endif()

if( NOT CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR )
  file(GLOB_RECURSE
    tablegenned_files_on_include_dir
    "${PPF_SOURCE_DIR}/include/ppf/*.inc")
  if( tablegenned_files_on_include_dir )
    message(FATAL_ERROR "Apparently there is a previous in-source build, "
"probably as the result of running `configure' and `make' on "
"${PPF_SOURCE_DIR}. This may cause problems. The suspicious files are:\n"
"${tablegenned_files_on_include_dir}\nPlease clean the source directory.")
  endif()
endif()

# Compute the ppf version from the LLVM version.
string(REGEX MATCH "[0-9]+\\.[0-9]+(\\.[0-9]+)?" PPF_VERSION
  ${PACKAGE_VERSION})
message(STATUS "ppf version: ${PPF_VERSION}")

string(REGEX REPLACE "([0-9]+)\\.[0-9]+(\\.[0-9]+)?" "\\1" PPF_VERSION_MAJOR
  ${PPF_VERSION})
string(REGEX REPLACE "[0-9]+\\.([0-9]+)(\\.[0-9]+)?" "\\1" PPF_VERSION_MINOR
  ${PPF_VERSION})
if (${PPF_VERSION} MATCHES "[0-9]+\\.[0-9]+\\.[0-9]+")
  set(PPF_HAS_VERSION_PATCHLEVEL 1)
  string(REGEX REPLACE "[0-9]+\\.[0-9]+\\.([0-9]+)" "\\1" PPF_VERSION_PATCHLEVEL
    ${PPF_VERSION})
else()
  set(PPF_HAS_VERSION_PATCHLEVEL 0)
endif()

# Configure the Version.inc file.
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/ppf/Basic/Version.inc.in
  ${CMAKE_CURRENT_BINARY_DIR}/include/ppf/Basic/Version.inc)

# Add appropriate flags for GCC
if (LLVM_COMPILER_IS_GCC_COMPATIBLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-common -Woverloaded-virtual -Wcast-qual -fno-strict-aliasing -pedantic -Wno-long-long -Wall -W -Wno-unused-parameter -Wwrite-strings")
endif ()

if (APPLE)
  set(CMAKE_MODULE_LINKER_FLAGS "-Wl,-flat_namespace -Wl,-undefined -Wl,suppress")
endif ()

configure_file(
  ${PPF_SOURCE_DIR}/include/ppf/Config/config.h.cmake
  ${PPF_BINARY_DIR}/include/ppf/Config/config.h)

#include(LLVMParseArguments)

# Enable C++ 11
if(NOT MSVC)
  add_definitions(-std=c++11)
endif()

function(ppf_tablegen)
  # Syntax:
  # ppf_tablegen output-file [tablegen-arg ...] SOURCE source-file
  # [[TARGET cmake-target-name] [DEPENDS extra-dependency ...]]
  #
  # Generates a custom command for invoking tblgen as
  #
  # tblgen source-file -o=output-file tablegen-arg ...
  #
  # and, if cmake-target-name is provided, creates a custom target for
  # executing the custom command depending on output-file. It is
  # possible to list more files to depend after DEPENDS.

  cmake_parse_arguments(CTG "" "SOURCE;TARGET" "" ${ARGN})

  if( NOT CTG_SOURCE )
    message(FATAL_ERROR "SOURCE source-file required by ppf_tablegen")
  endif()

  set( LLVM_TARGET_DEFINITIONS ${CTG_SOURCE} )
  tablegen(PPF ${CTG_UNPARSED_ARGUMENTS})

  if(CTG_TARGET)
    add_public_tablegen_target(${CTG_TARGET})
    set_target_properties( ${CTG_TARGET} PROPERTIES FOLDER "ppf tablegenning")
    set_property(GLOBAL APPEND PROPERTY PPF_TABLEGEN_TARGETS ${CTG_TARGET})
  endif()
endfunction(ppf_tablegen)

macro(add_ppf_library name)
  llvm_process_sources(srcs ${ARGN})
  if(MSVC_IDE OR XCODE)
    # Add public headers
    file(RELATIVE_PATH lib_path
      ${PPF_SOURCE_DIR}/lib/
      ${CMAKE_CURRENT_SOURCE_DIR}
    )
    if(NOT lib_path MATCHES "^[.][.]")
      file( GLOB_RECURSE headers
        ${PPF_SOURCE_DIR}/include/ppf/${lib_path}/*.h
        ${PPF_SOURCE_DIR}/include/ppf/${lib_path}/*.def
      )
      set_source_files_properties(${headers} PROPERTIES HEADER_FILE_ONLY ON)

      file( GLOB_RECURSE tds
        ${PPF_SOURCE_DIR}/include/ppf/${lib_path}/*.td
      )
      source_group("TableGen descriptions" FILES ${tds})
      set_source_files_properties(${tds}} PROPERTIES HEADER_FILE_ONLY ON)

      set(srcs ${srcs} ${headers} ${tds})
    endif()
  endif(MSVC_IDE OR XCODE)
  if (MODULE)
    set(libkind MODULE)
  elseif (SHARED_LIBRARY)
    set(libkind SHARED)
  else()
    set(libkind)
  endif()
  add_library( ${name} ${libkind} ${srcs} )
  llvm_update_compile_flags(${name} ${srcs})
  if( LLVM_COMMON_DEPENDS )
    add_dependencies( ${name} ${LLVM_COMMON_DEPENDS} )
  endif( LLVM_COMMON_DEPENDS )

  llvm_config( ${name} ${LLVM_LINK_COMPONENTS} )
  target_link_libraries( ${name} ${LLVM_COMMON_LIBS} )

  install(TARGETS ${name}
    LIBRARY DESTINATION lib${LLVM_LIBDIR_SUFFIX}
    ARCHIVE DESTINATION lib${LLVM_LIBDIR_SUFFIX}
    RUNTIME DESTINATION bin)
  set_target_properties(${name} PROPERTIES FOLDER "ppf libraries")
endmacro(add_ppf_library)

macro(add_ppf_executable name)
  add_llvm_executable( ${name} ${ARGN} )
  set_target_properties(${name} PROPERTIES FOLDER "ppf executables")
endmacro(add_ppf_executable)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(BEFORE
  ${CMAKE_CURRENT_BINARY_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  )

install(DIRECTORY include/
  DESTINATION include
  FILES_MATCHING
  PATTERN "*.def"
  PATTERN "*.h"
  PATTERN "config.h" EXCLUDE
  PATTERN ".svn" EXCLUDE
  )

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/
  DESTINATION include
  FILES_MATCHING
  PATTERN "CMakeFiles" EXCLUDE
  PATTERN "*.inc"
  )

add_definitions( -D_GNU_SOURCE )

# ppf version information
set(PPF_EXECUTABLE_VERSION
     "${PPF_VERSION_MAJOR}.${PPF_VERSION_MINOR}" CACHE STRING
    "Version number that will be placed into the ppf executable, in the form XX.YY")
set(LIBPPF_LIBRARY_VERSION
     "${PPF_VERSION_MAJOR}.${PPF_VERSION_MINOR}" CACHE STRING
    "Version number that will be placed into the libppf library , in the form XX.YY")
mark_as_advanced(PPF_EXECUTABLE_VERSION LIBPPF_LIBRARY_VERSION)

add_subdirectory(utils/TableGen)

add_subdirectory(include)

# All targets below may depend on all tablegen'd files
get_property(PPF_TABLEGEN_TARGETS GLOBAL PROPERTY PPF_TABLEGEN_TARGETS)
list(APPEND LLVM_COMMON_DEPENDS ${PPF_TABLEGEN_TARGETS})

add_subdirectory(lib)
add_subdirectory(tools)

if( LLVM_INCLUDE_TESTS )
  add_subdirectory(unittests)
  list(APPEND PPF_TEST_DEPS ppfUnitTests)
    list(APPEND PPF_TEST_PARAMS
      ppf_unit_site_config=${CMAKE_CURRENT_BINARY_DIR}/test/Unit/lit.site.cfg
      )
  add_subdirectory(test)
endif()

option(PPF_INCLUDE_DOCS "Generate build targets for the ppf docs."
  ${LLVM_INCLUDE_DOCS})
if( PPF_INCLUDE_DOCS )
  add_subdirectory(docs)
endif()

# Workaround for MSVS10 to avoid the Dialog Hell
# FIXME: This could be removed with future version of CMake.
if( PPF_BUILT_STANDALONE AND MSVC_VERSION EQUAL 1600 )
  set(PPF_SLN_FILENAME "${CMAKE_CURRENT_BINARY_DIR}/ppf.sln")
  if( EXISTS "${PPF_SLN_FILENAME}" )
    file(APPEND "${PPF_SLN_FILENAME}" "\n# This should be regenerated!\n")
  endif()
endif()

set(BUG_REPORT_URL "http://FIXME" CACHE STRING
  "Default URL where bug reports are to be submitted.")

