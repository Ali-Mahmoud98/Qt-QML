cmake_minimum_required(VERSION 3.22.1)

project(Qt-core-example2 LANGUAGES CXX)

set(HEADER_FILES
    inc/Contact.h
    inc/MainWindow.h
    inc/ContactDialog.h
)

set(SOURCES
    src/Contact.cpp
    src/MainWindow.cpp
    src/ContactDialog.cpp
    main.cpp
)

set(CMAKE_AUTOMOC ON)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} /home/ali-mahmoud/Qt/6.7.3/gcc_64/lib/cmake/)

find_package(Qt6 COMPONENTS Widgets Core REQUIRED)

qt6_wrap_cpp(HEADER_MOC ${HEADER_FILES})

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADER_FILES}
    ${HEADER_MOC}
)

set(QT_LIBS
    Qt6::Core
    Qt6::Widgets
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${QT_LIBS})

# Include directories (optional, depends on your project's needs)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

# Enable C++17 without compiler-specific extensions
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS OFF
)
