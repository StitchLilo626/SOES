cmake_minimum_required (VERSION 3.13)
project (soes_host_tests C)

enable_testing ()
include (CheckIPOSupported)
check_ipo_supported (RESULT HAVE_LTO OUTPUT LTO_ERROR LANGUAGES C)
if (NOT HAVE_LTO)
  message (FATAL_ERROR "Host regression tests require LTO: ${LTO_ERROR}")
endif ()

get_filename_component (SOES_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../.." ABSOLUTE)

foreach (TEST_NAME cc_layout cc_layout_lto)
  add_executable (${TEST_NAME}
    cc_layout.c
    cc_osal_first.c
    cc_soes_first.c
    ${SOES_ROOT}/soes/ecat_slv.c
    )
  target_include_directories (${TEST_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SOES_ROOT}/soes
    ${SOES_ROOT}/soes/include/sys/gcc
    ${SOES_ROOT}/applications/linux_lan9252demo
    )
  target_compile_options (${TEST_NAME} PRIVATE
    -Wall -Wextra -Werror -Wno-unused-parameter
    -ffunction-sections -fdata-sections
    )
  target_link_options (${TEST_NAME} PRIVATE -Wl,--gc-sections)
  set_target_properties (${TEST_NAME} PROPERTIES C_STANDARD 11 C_STANDARD_REQUIRED YES)
  if (TEST_NAME STREQUAL cc_layout_lto)
    set_target_properties (${TEST_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
    if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
      target_link_options (${TEST_NAME} PRIVATE -Werror=lto-type-mismatch)
    endif ()
  endif ()
  add_test (NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach ()
