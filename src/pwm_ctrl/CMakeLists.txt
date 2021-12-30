cmake_minimum_required( VERSION 3.10.3 )

if(NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    message(FATAL_ERROR "This is a Linux specific driver!")
endif()

set(INIH_DIR "${CMAKE_CURRENT_LIST_DIR}/../thirdparty/inih")
add_library(inih ${INIH_DIR}/ini.c)

add_executable(pwm_ctrl)
target_sources(pwm_ctrl PRIVATE 
                                ${CMAKE_CURRENT_LIST_DIR}/main.c
                                ${CMAKE_CURRENT_LIST_DIR}/pwm_driver_api/driver.c )
target_include_directories(pwm_ctrl PRIVATE ${CMAKE_CURRENT_LIST_DIR}/pwm_driver_api/)
target_link_libraries(pwm_ctrl ipc)
target_include_directories(pwm_ctrl PRIVATE ${IPC_INCLUDE_DIRECTORIES})

target_link_libraries(pwm_ctrl inih)
target_include_directories(pwm_ctrl PRIVATE ${INIH_DIR}/)

