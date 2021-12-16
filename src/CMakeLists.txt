cmake_minimum_required( VERSION 3.10.3 )

project(            breguet 
                    VERSION 0.1 
                    LANGUAGES C 
                    DESCRIPTION "Control Four PWM Motors with Web Interface"
                    HOMEPAGE_URL "https://github.com/leocelente/SAA0356_Drone"
        )

# CMAKE_TOOLCHAIN_FILE = 
set(EXPORT_COMPILE_COMMANDS true)
# dependency order
# web_interface -> pwm_ctrl-> ipc
#   |-> ipc

# IPC - Inter-Process Comunication
include(./ipc/CMakeLists.txt)
# PWM_CTRL - Pulse-Width-Modulation Controller
include(./pwm_ctrl/CMakeLists.txt)
# Web Server Interface
include(./web_interface/CMakeLists.txt)

