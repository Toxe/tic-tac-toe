if(BUILD_TESTING)
    add_executable(tests
        ai_receive_ai_command.cpp
        app_app_controller.cpp
        app_commands.cpp
        board_board.cpp
        board_square.cpp
        command_command.cpp
        game_commands.cpp
        game_game_state.cpp
        game_player.cpp
        game_win_conditions.cpp
        grid_coords.cpp
        grid_grid.cpp
        grid_gridcell.cpp
        input_eval_input.cpp
        minimax_minimax.cpp
        minimax_stats.cpp
        output_player_symbol.cpp
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
