if(BUILD_TESTING)
    add_executable(tests
        ai_receive_ai_command.cpp
        game_board.cpp
        game_command.cpp
        game_execute_command.cpp
        game_game_state.cpp
        game_player.cpp
        game_square.cpp
        game_win_conditions.cpp
        input_eval_input.cpp
        output_show_board.cpp
        output_show_game_over.cpp
    )

    set_target_properties(tests PROPERTIES CXX_EXTENSIONS OFF)
    target_compile_features(tests PUBLIC cxx_std_20)
    target_compile_options(tests PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
    target_link_options(tests PRIVATE ${SANITIZER_LINK_OPTIONS})
    target_link_libraries(tests PRIVATE ${SANITIZER_LINK_LIBRARIES} lib_tic_tac_toe Catch2::Catch2WithMain)

    add_test(NAME tests COMMAND tests)
endif()
