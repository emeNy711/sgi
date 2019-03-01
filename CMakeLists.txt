project(xmlconverter)
cmake_minimum_required(VERSION 2.8)

enable_language(CXX)

#if (NOT DEFINED SPO_BUILD_PATH)
#	SET(SPO_BUILD_PATH ${PROJECT_BINARY_DIR})
#endif()

#SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SPO_BUILD_PATH}/bin) 
#SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SPO_BUILD_PATH}/lib)
#SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SPO_BUILD_PATH}/lib)

#add_definitions(-D__WIN32__)
if(WIN32)
  add_definitions(-DWIN32)
endif()

find_package (Qt5Core)
find_package (Qt5Widgets)
find_package (Qt5Gui)
find_package (Qt5Sql)
find_package (Qt5Concurrent)
#find_package (Qt5Network)

FILE(GLOB SOURCES *.cpp)
FILE(GLOB HEADERS *.h *.hpp)
SET(CMAKE_AUTOMOC ON)

add_definitions(${Qt5Core_DEFINITIONS})
add_definitions(${Qt5Widgets_DEFINITIONS})
add_definitions(${Qt5Network_DEFINITIONS})
add_definitions(${Qt5Concurrent_DEFINITIONS})

include_directories(${Qt5Core_INCLUDES})
include_directories(${Qt5Widgets_INCLUDES})
include_directories(${Qt5Concurrent_INCLUDES})
#include_directories(${Qt5Network_INCLUDES})

set(CMAKE_CXX_FLAGS "${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${Qt5Network_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${Qt5Concurrent_EXECUTABLE_COMPILE_FLAGS}")


#if(WIN32)
#	set(MY_WIN_FLAG WIN32)
#	set(CMAKE_CXX_FLAGS "/EHa /Zc:wchar_t")
#	set(ADDITIONAL_LIBS ws2_32)
#else()
#	set(ADDITIONAL_LIBS pthread mongoclient)
#endif()

link_directories(${QT_LIBRARY_DIR})

add_executable(xmlconverter ${SOURCES} ${HEADERS})
target_link_libraries (xmlconverter ${QT_LIBRARIES})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /SAFESEH:NO")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
									 
if(WIN32)
  qt5_use_modules(xmlconverter Core Widgets Sql Concurrent)
endif()
