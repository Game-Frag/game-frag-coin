CMAKE_MINIMUM_REQUIRED(VERSION 3.14.0 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "RELEASE")
ENDIF()

project(BLS)

set(BUILD_BLS_TESTS "1" CACHE STRING "")
set(BUILD_BLS_BENCHMARKS "1" CACHE STRING "")

message(STATUS "Build tests: ${BUILD_BLS_TESTS}")
message(STATUS "Build benchmarks: ${BUILD_BLS_BENCHMARKS}")

# Add path for custom modules
set(CMAKE_MODULE_PATH
	${CMAKE_MODULE_PATH}
	${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules
)

find_package(sodium)
if (SODIUM_FOUND)
  message(STATUS "Found libsodium")
  message(STATUS "Sodium include dir = ${sodium_INCLUDE_DIR}")
  set(BLSALLOC_SODIUM "1" CACHE STRING "")
  include_directories(${sodium_INCLUDE_DIR})
endif()

find_package(gmp)
if (GMP_FOUND)
  message(STATUS "Found libgmp")
  include_directories(${GMP_INCLUDE_DIR})
  set(ARITH "gmp" CACHE STRING "")
else()
  set(ARITH "easy" CACHE STRING "")
endif()

if(EMSCRIPTEN)
  # emscripten needs arch set to be none since it can't compile assembly
  set(ARCH "" CACHE STRING "")
  # emscripten is a 32 bit compiler
  set(WSIZE "32" CACHE STRING "Relic - Processor word size")
else()
  set(WSIZE "64" CACHE STRING "Relic - Processor word size")
endif()

set(TIMER "CYCLE" CACHE STRING "")
set(CHECK "off" CACHE STRING "")
set(VERBS "off" CACHE STRING "")
set(ALLOC "AUTO" CACHE STRING "")
set(SHLIB "OFF" CACHE STRING "")
set(MULTI "PTHREAD" CACHE STRING "")
set(DOCUM "off" CACHE STRING "")

set(FP_PRIME "381" CACHE STRING "Relic - Prime modulus size")

IF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(SEED "UDEV" CACHE STRING "")
  set(FP_QNRES "off" CACHE STRING "")
ELSEIF (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(SEED "WCGR" CACHE STRING "")
  set(FP_QNRES "on" CACHE STRING "")
ELSE()
  set(SEED "UDEV" CACHE STRING "")
  set(FP_QNRES "on" CACHE STRING "")
ENDIF()
set(STBIN "OFF" CACHE STRING "")

set(FP_METHD "INTEG;INTEG;INTEG;MONTY;LOWER;SLIDE" CACHE STRING "")
set(CFLAGS "-O3 -funroll-loops -fomit-frame-pointer" CACHE STRING "")
set(FP_PMERS "off" CACHE STRING "")
set(FPX_METHD "INTEG;INTEG;LAZYR" CACHE STRING "")
set(EP_PLAIN "off" CACHE STRING "")
set(EP_SUPER "off" CACHE STRING "")
# Disable relic tests and benchmarks
set(TESTS "0" CACHE STRING "Relic - Number of times each test is ran")
set(BENCH "0" CACHE STRING "Relic - Number of times each benchmark is ran")
set(QUIET "on" CACHE STRING "Relic - Build with printing disabled")

set(PP_EXT "LAZYR" CACHE STRING "")
set(PP_METHD "LAZYR;OATEP" CACHE STRING "")

add_subdirectory(src)

if (EMSCRIPTEN)
  add_subdirectory(js-bindings)
else()
  # emscripten can't build python bindings, it produces only javascript
  # add_subdirectory(contrib/pybind11)
  if (BUILD_BLS_PYTHON_BINDINGS)
    add_subdirectory(python-bindings)
  endif()
endif()
