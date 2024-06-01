cmake_minimum_required(VERSION 3.5)

project(ai-qt-app VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Add boost lib source>>
set(BOOST_INCLUDE_LIBRARIES asio beast json)
set(BOOST_ENABLE_CMAKE ON)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE) # Print downloading progress
# Download and extract boost lib from GitHub


# # Set the path to the Boost lib (just in case)
# set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/build/_deps/boost-src")

# Dowload and extract sqlite3
FetchContent_Declare(
    sqlite3
    URL https://www.sqlite.org/2024/sqlite-amalgamation-3450300.zip
)
# FOR DB

include(FetchContent)
FetchContent_Declare(sqlite3 URL https://www.sqlite.org/2024/sqlite-amalgamation-3450300.zip)
FetchContent_MakeAvailable(sqlite3)

# Set the path to the SQLite amalgamation directory
set(SQLITE "${CMAKE_SOURCE_DIR}/cmake-build-debug/_deps/sqlite3-src")

# Include the SQLite amalgamation directly into the project
add_library(sqlite3 STATIC ${SQLITE}/sqlite3.c)

# Add include directories for SQLite
target_include_directories(sqlite3 PUBLIC ${SQLITE})


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Core Network)

set(TS_FILES ai-qt-app_en_GB.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        sendconfirmwindow.cpp
        sendconfirmwindow.h
        sendconfirmwindow.ui
        resetwarningwindow.cpp
        resetwarningwindow.h
        resetwarningwindow.ui
        newloginwindow.cpp
        newloginwindow.h
        requestsToBackEnd.cpp
        requestsToBackend.h
        database.h
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ai-qt-app
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        sendconfirmwindow.h sendconfirmwindow.cpp sendconfirmwindow.ui
        resetwarningwindow.h resetwarningwindow.cpp resetwarningwindow.ui
        newloginwindow.h newloginwindow.cpp newloginwindow.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ai-qt-app APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(ai-qt-app SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ai-qt-app
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()
target_link_libraries(ai-qt-app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::Core
        sqlite3) #тууууут что-то

# target_link_libraries(ai-qt-app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets )

# Find the Boost libraries
#find_package(Boost REQUIRED COMPONENTS system program_options)
#
#include_directories(${Boost_INCLUDE_DIRS})
#link_directories(${Boost_LIBRARY_DIRS})
#target_link_libraries(ai-qt-app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${Boost_LIBRARIES})
# Если библиотека найдена, то
#target_include_directories (SYSTEM ${Boost_INCLUDE_DIR}) # подключаем заголовочные файлы
#
#target_link_libraries(ai-qt-app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ai-qt-app ${Boost_LIBRARIES})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ai-qt-app)
endif()
set_target_properties(ai-qt-app PROPERTIES
  ${BUNDLE_ID_OPTION}
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
  MACOSX_BUNDLE TRUE
  WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ai-qt-app
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Укажите компоненты Boost, которые вам нужны
#find_package(Boost 1.79 REQUIRED COMPONENTS filesystem system)

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(ai-qt-app)
endif()