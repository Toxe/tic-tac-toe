add_library(lib_tic_tac_toe
        game/board.cpp
        game/board.hpp
        game/execute_command.cpp
        game/execute_command.hpp
        game/game_state.cpp
        game/game_state.hpp
        game/player.cpp
        game/player.hpp
        input/read_command.cpp
        input/read_command.hpp
        output/generate_output.cpp
        output/generate_output.hpp
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
if (BUILD_TESTING)
    add_executable(tic_tac_toe_tests
            game/board.test.cpp
            game/game_state.test.cpp
            game/player.test.cpp
            output/generate_output.test.cpp
            )

    set_target_properties(tic_tac_toe_tests PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(tic_tac_toe_tests PUBLIC cxx_std_20)
    target_compile_options(tic_tac_toe_tests PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
    target_link_options(tic_tac_toe_tests PRIVATE ${SANITIZER_LINK_OPTIONS})
    target_link_libraries(tic_tac_toe_tests PRIVATE ${SANITIZER_LINK_LIBRARIES} lib_tic_tac_toe Catch2::Catch2WithMain)

    add_test(NAME tic_tac_toe_tests COMMAND tic_tac_toe_tests)
endif ()
