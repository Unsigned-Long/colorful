set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(OpenCV)

include_directories(include)

add_executable(${CMAKE_PROJECT_NAME}_terminal main_ct.cpp)

add_executable(${CMAKE_PROJECT_NAME}_mapping main_cm.cpp)

target_include_directories(${CMAKE_PROJECT_NAME}_mapping PRIVATE ${OpenCV_INCLUDE_DIRS})

target_link_libraries(${CMAKE_PROJECT_NAME}_mapping PRIVATE ${OpenCV_LIBS})

