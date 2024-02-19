set(PROJECT_NAME qtwinmigrate)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets Gui REQUIRED)

add_definitions(-DQT_QTWINMIGRATE_EXPORT)

set(SOURCE_LIST
  "qtwinmigrate/qwinwidget.cpp"
  "qtwinmigrate/qmfcapp.cpp"
  "qtwinmigrate/qwinhost.cpp"
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_LIST})

target_include_directories(${PROJECT_NAME}
  PUBLIC .
  PRIVATE ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
  ${Qt5Gui_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS}
)

if(MSVC)
  target_link_options(${PROJECT_NAME} PRIVATE /DEBUG)
  target_compile_options(${PROJECT_NAME} PRIVATE /Zi)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE 
  ${Qt5Widgets_LIBRARIES} ${Qt5Gui_LIBRARIES}
)

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
)
