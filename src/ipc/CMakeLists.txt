cmake_minimum_required( VERSION 3.10.3 )

add_library(ipc)
target_sources(ipc PRIVATE ${CMAKE_CURRENT_LIST_DIR}/ipc.c)
target_include_directories(ipc PUBLIC ${CMAKE_CURRENT_LIST_DIR})
