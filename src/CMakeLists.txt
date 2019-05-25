project(system_monitor)

# find ncurses library
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# automatically find all sources and headers file
file(GLOB PROJECT_SOURCE *.cc *.hpp)

# create the executable with all files listed on `src` folder
add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCE})
target_link_libraries(${CMAKE_PROJECT_NAME} ${CURSES_LIBRARIES})

# define `bin` folder as output path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)
