cmake_minimum_required( VERSION 3.10.3 )

project(            breguet_pwm_ctrl
                    VERSION 0.1 
                    LANGUAGES C 
                    DESCRIPTION "PWM Controller component"
                    HOMEPAGE_URL "https://github.com/leocelente/SAA0356_Drone"
)
if(NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    message(FATAL_ERROR "This is a Linux specific driver!")
endif()

add_executable(pwm_ctrl)
target_sources(pwm_ctrl PRIVATE 
                                ${CMAKE_CURRENT_LIST_DIR}/main.c
                                ${CMAKE_CURRENT_LIST_DIR}/pwm_driver_api/driver.c )
target_include_directories(pwm_ctrl PRIVATE ${CMAKE_CURRENT_LIST_DIR}/pwm_driver_api/)
target_link_libraries(pwm_ctrl ipc)
target_include_directories(pwm_ctrl PRIVATE ${IPC_INCLUDE_DIRECTORIES})

