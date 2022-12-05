add_library(lib_tic_tac_toe
        game/execute_command.cpp
        game/execute_command.hpp
        game/game_state.cpp
        game/game_state.hpp
        input/read_command.cpp
        input/read_command.hpp
        output/show_output.cpp
        output/show_output.hpp
        )

set_target_properties(lib_tic_tac_toe PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(lib_tic_tac_toe PUBLIC cxx_std_20)
target_compile_options(lib_tic_tac_toe PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
target_link_options(lib_tic_tac_toe PRIVATE ${SANITIZER_LINK_OPTIONS})
target_link_libraries(lib_tic_tac_toe PRIVATE ${SANITIZER_LINK_LIBRARIES} fmt::fmt scn::scn)
target_include_directories(lib_tic_tac_toe INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Tests
#if (BUILD_TESTING)
#    add_executable(lib_tic_tac_toe_tests
#            )
#
#    set_target_properties(lib_tic_tac_toe_tests PROPERTIES CXX_EXTENSIONS OFF)
#    target_compile_features(lib_tic_tac_toe_tests PUBLIC cxx_std_20)
#    target_compile_options(lib_tic_tac_toe_tests PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
#    target_link_options(lib_tic_tac_toe_tests PRIVATE ${SANITIZER_LINK_OPTIONS})
#    target_link_libraries(lib_tic_tac_toe_tests PRIVATE ${SANITIZER_LINK_LIBRARIES} lib_tic_tac_toe Catch2::Catch2WithMain)
#
#    add_test(NAME lib_tic_tac_toe_tests COMMAND lib_tic_tac_toe_tests)
#endif ()
