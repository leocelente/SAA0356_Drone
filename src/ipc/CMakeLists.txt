cmake_minimum_required( VERSION 3.10.3 )

project(            breguet_ipc
                    VERSION 0.1 
                    LANGUAGES C 
                    DESCRIPTION "Inter-Process-Communication component"
                    HOMEPAGE_URL "https://github.com/leocelente/SAA0356_Drone"
)

add_library(ipc)
target_sources(ipc PRIVATE ${CMAKE_CURRENT_LIST_DIR}/ipc.c)
target_include_directories(ipc PUBLIC ${CMAKE_CURRENT_LIST_DIR})


