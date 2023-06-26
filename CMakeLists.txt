cmake_minimum_required(VERSION 3.26)

project(sysvk)

add_library(sysvk SHARED sysvk.c)
target_link_libraries(sysvk hardware)
target_include_directories(sysvk SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(TARGETS sysvk 
  LIBRARY DESTINATION lib)
install(FILES sysvk_icd.json
  DESTINATION share/vulkan/icd.d/)


