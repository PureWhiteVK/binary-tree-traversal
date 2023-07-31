add_library(traversal INTERFACE)
add_library(traversal::traversal ALIAS traversal)
target_include_directories(
  traversal INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
)
