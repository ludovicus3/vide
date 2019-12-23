# This function prevents in-source builds
function(AssureOutOfSourceBuilds)
  # ensure user isn't using symlinks to pass check
  get_filename_component(srcdir "${CMAKE_SOURCE_DIR}" REALPATH)
  get_filename_component(bindir "${CMAKE_BINARY_DIR}" REALPATH)

  if("${srcdir}" STREQUAL "${bindir}")
    message(FATAL_ERROR "You must run cmake in a build directory")
  endif()
endfunction()

AssureOutOfSourceBuilds()
