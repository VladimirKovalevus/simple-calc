cmake_minimum_required(VERSION 3.5)

project(simple-calc VERSION 0.1 LANGUAGES CXX )

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS  Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS  Widgets PrintSupport)

set(PROJECT_SOURCES
        main.cpp
        controller/mainwindow.cpp
        controller/mainwindow.h
        mainwindow.ui
        service/qcustomplot.cpp
        service/qcustomplot.h
        controller/controlnode.h
        controller/controlnode.cpp
        service/polishnotation.h
        service/polishnotation.cpp
        controller/evalstringprocessor.h
        controller/evalstringprocessor.cpp
        service/utils.cpp
        service/utils.hpp
)
add_library(qcustomplot
  service/qcustomplot.h
  service/qcustomplot.cpp
  )

target_include_directories(qcustomplot PUBLIC
    service
  )
set_target_properties(qcustomplot PROPERTIES
  AUTOMOC ON
  )

set(Qt${QT_VERSION_MAJOR}Libs Core Widgets PrintSupport)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS ${Qt${QT_VERSION_MAJOR}Libs} REQUIRED)
foreach(i IN LISTS Qt${QT_VERSION_MAJOR}Libs)
    target_link_libraries(qcustomplot PRIVATE
      Qt${QT_VERSION_MAJOR}::${i}
)
endforeach()
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(simple-calc
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET simple-calc APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(simple-calc SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(simple-calc
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport qcustomplot)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.simple-calc)
endif()
set_target_properties(simple-calc PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS simple-calc
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(simple-calc)
endif()
