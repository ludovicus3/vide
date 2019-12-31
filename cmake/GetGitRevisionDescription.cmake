if(__get_git_revision_description)
  return()
endif()
set(__get_git_revision_description YES)

get_filename_component(_gitdescmoddir ${CMAKE_CURRENT_LIST_FILE} PATH)

function(get_git_head_revision _revision)
  if(NOT GIT_FOUND)
    find_package(Git QUIET)
  endif()
  if(NOT GIT_FOUND)
    set(${_revision} "GIT-NOTFOUND" PARENT_SCOPE)
    return()
  endif()

  execute_process(
    COMMAND             "${GIT_EXECUTABLE}" rev-list --count --first-parent HEAD
    WORKING_DIRECTORY   "${CMAKE_CURRENT_SOURCE_DIR}"
    RESULT_VARIABLE     result
    OUTPUT_VARIABLE     output
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
  if(NOT result EQUAL 0)
    set(${_revision} "HEAD-REVISION-NOTFOUND" PARENT_SCOPE)
    return()
  endif()

  set(${_revision} "${output}" PARENT_SCOPE)
endfunction()

