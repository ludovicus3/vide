set(PROJECT_SOURCES
  thread.cc
  )

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

set(PUBLIC_HEADERS
  "${CMAKE_CURRENT_BINARY_DIR}/../clotho/version.h"
  )

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER "${PUBLIC_HEADERS}"
  )

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}_targets
  RUNTIME DESTINATION bin COMPONENT libs
  )
