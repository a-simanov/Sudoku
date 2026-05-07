cmake_minimum_required(VERSION 3.16)

project(Sudoku LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(SOURCES
    main.cpp
    field.cpp
    sudoku.cpp
)

set(FORMS
    sudoku.ui
)

set(HEADERS
    sudoku.h
    field.h
)

add_executable(Sudoku
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
)

target_link_libraries(Sudoku PRIVATE 
    Qt6::Core 
    Qt6::Gui 
    Qt6::Widgets
)

if(QNX)
    set(INSTALL_EXAMPLEDIR /tmp/${PROJECT_NAME}/bin)
elseif(UNIX AND NOT ANDROID)
    set(INSTALL_EXAMPLEDIR /opt/${PROJECT_NAME}/bin)
endif()

if(INSTALL_EXAMPLEDIR)
    install(TARGETS Sudoku DESTINATION ${INSTALL_EXAMPLEDIR})
endif()
