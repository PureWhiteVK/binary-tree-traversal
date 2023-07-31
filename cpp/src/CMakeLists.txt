add_subdirectory(traversal)

add_executable(traversal_demo main.cpp)
set_property(TARGET traversal_demo PROPERTY CXX_STANDARD 17)
target_link_libraries(traversal_demo PRIVATE traversal::traversal)