cmake_minimum_required(VERSION 3.16)
project(QtPropertyExample VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} /home/ali-mahmoud/Qt/6.7.3/gcc_64/lib/cmake/)
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
# For Qt5, use this instead:
# find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(PROJECT_SOURCES
    src/main.cpp
    src/person.h
    src/person.cpp
    src/addressbook.h
    src/addressbook.cpp
    src/mainwindow.h
    src/mainwindow.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    # For Qt5, use these instead:
    # Qt5::Core
    # Qt5::Gui
    # Qt5::Widgets
)

# Install the executable
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
