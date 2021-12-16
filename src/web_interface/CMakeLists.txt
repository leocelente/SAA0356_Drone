cmake_minimum_required( VERSION 3.10.3 )

project(            breguet_web_server
                    VERSION 0.1 
                    LANGUAGES C 
                    DESCRIPTION "Web Interface component"
                    HOMEPAGE_URL "https://github.com/leocelente/SAA0356_Drone"
)
find_package(Threads REQUIRED)

add_executable(web_interface)
target_sources(web_interface PRIVATE 
                                ${CMAKE_CURRENT_LIST_DIR}/main.c
                                ${CMAKE_CURRENT_LIST_DIR}/server/server.c )
target_link_libraries(web_interface Threads::Threads)

target_include_directories(web_interface PRIVATE ${CMAKE_CURRENT_LIST_DIR}/server/)
target_link_libraries(web_interface ipc)
target_include_directories(web_interface PRIVATE ${IPC_INCLUDE_DIRECTORIES})
