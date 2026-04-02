cmake_minimum_required(VERSION 3.19)
project(files LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 6.9 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(EXE_EXTRAS WIN32)

set(EXE_EXTRAS ${EXE_EXTRAS} MACOSX_BUNDLE)

set(SOURCES
    ./src/main.cpp
    ./src/window.cpp
    ./src/window.hpp
    ./src/file_list.hpp
    ./src/dialog_open_file.cpp
    ./src/dialog_open_file.hpp
)

qt_add_executable(files ${EXE_EXTRAS} ${SOURCES})

target_link_libraries(files
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS files
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET files
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
