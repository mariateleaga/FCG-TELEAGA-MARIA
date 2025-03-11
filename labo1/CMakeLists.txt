cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)


add_executable(main_event_callback_cout src/main_event_callback_cout.cpp)
target_link_libraries(main_event_callback_cout PRIVATE SFML::Graphics)

add_executable(main_event_callback_text src/main_event_callback_text.cpp)
target_link_libraries(main_event_callback_text PRIVATE SFML::Graphics)

add_executable(main_event_classic_cout src/main_event_classic_cout.cpp)
target_link_libraries(main_event_classic_cout PRIVATE SFML::Graphics)

add_executable(main_event_classic_text src/main_event_classic_text.cpp)
target_link_libraries (main_event_classic_text PRIVATE SFML::Graphics)

add_executable(main_text_echo src/main_text_echo.cpp)
target_link_libraries(main_text_echo PRIVATE SFML::Graphics)

# add_executable(my_editor  src/my_editor.cpp)
# target_link_libraries(my_editor PRIVATE SFML::Graphics)