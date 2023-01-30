add_library(lib_tic_tac_toe
    ai/receive_ai_command.cpp
    ai/receive_ai_command.hpp
    app/app_controller.cpp
    app/app_controller.hpp
    app/commands.cpp
    app/commands.hpp
    board/board.cpp
    board/board.hpp
    board/square.cpp
    board/square.hpp
    command/command.hpp
    command/command_factory.cpp
    command/command_factory.hpp
    game/commands.cpp
    game/commands.hpp
    game/game_state.cpp
    game/game_state.hpp
    game/player.cpp
    game/player.hpp
    game/win_conditions.cpp
    game/win_conditions.hpp
    input/eval_input.cpp
    input/eval_input.hpp
    input/receive_player_command.cpp
    input/receive_player_command.hpp
    output/console_writer.cpp
    output/console_writer.hpp
    output/show_board.cpp
    output/show_board.hpp
    output/show_game_over.cpp
    output/show_game_over.hpp
)

set_target_properties(lib_tic_tac_toe PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(lib_tic_tac_toe PUBLIC cxx_std_20)
target_compile_options(lib_tic_tac_toe PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
target_link_options(lib_tic_tac_toe PRIVATE ${SANITIZER_LINK_OPTIONS})
target_link_libraries(lib_tic_tac_toe PRIVATE ${SANITIZER_LINK_LIBRARIES} fmt::fmt scn::scn)
target_include_directories(lib_tic_tac_toe INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# main executable
add_executable(tic_tac_toe main.cpp)

set_target_properties(tic_tac_toe PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(tic_tac_toe PUBLIC cxx_std_20)
target_compile_options(tic_tac_toe PRIVATE ${SANITIZER_COMPILE_OPTIONS} ${DEFAULT_COMPILER_OPTIONS} ${DEFAULT_COMPILER_WARNINGS})
target_link_options(tic_tac_toe PRIVATE ${SANITIZER_LINK_OPTIONS})
target_link_libraries(tic_tac_toe PRIVATE ${SANITIZER_LINK_LIBRARIES} lib_tic_tac_toe)
