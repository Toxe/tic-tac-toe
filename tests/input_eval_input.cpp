#include <utility>
#include <vector>

#include "catch2/catch_test_macros.hpp"

#include "../src/app/app_controller.hpp"
#include "../src/board/board.hpp"
#include "../src/command/command_factory.hpp"
#include "../src/game/game_state.hpp"
#include "../src/input/eval_input.hpp"
#include "../src/output/console_writer.hpp"

namespace tic_tac_toe {

TEST_CASE("input/eval_input")
{
    Board board;
    GameState game_state;
    AppController controller;
    ConsoleWriter console_writer{false};
    CommandFactory command_factory{board, game_state, controller, console_writer};

    SECTION("eval_input()")
    {
        SECTION("empty input returns an invalid command (nullopt)")
        {
            CHECK(eval_input(board, command_factory, "") == std::nullopt);
        }

        SECTION("simple keyword commands")
        {
            CHECK(eval_input(board, command_factory, "?") != std::nullopt);
            CHECK(eval_input(board, command_factory, "h") != std::nullopt);
            CHECK(eval_input(board, command_factory, "q") != std::nullopt);
            CHECK(eval_input(board, command_factory, "r") != std::nullopt);
            CHECK(eval_input(board, command_factory, "u") != std::nullopt);
            CHECK(eval_input(board, command_factory, "exit") != std::nullopt);
            CHECK(eval_input(board, command_factory, "help") != std::nullopt);
            CHECK(eval_input(board, command_factory, "quit") != std::nullopt);
            CHECK(eval_input(board, command_factory, "redo") != std::nullopt);
            CHECK(eval_input(board, command_factory, "undo") != std::nullopt);
        }

        SECTION("player move commands")
        {
            SECTION("input must be one alphabetic character (\"abcABC\") and one digit (\"123\")")
            {
                CHECK(eval_input(board, command_factory, "12") == std::nullopt);
                CHECK(eval_input(board, command_factory, "32") == std::nullopt);
                CHECK(eval_input(board, command_factory, "19") == std::nullopt);
                CHECK(eval_input(board, command_factory, "91") == std::nullopt);
                CHECK(eval_input(board, command_factory, "99") == std::nullopt);
                CHECK(eval_input(board, command_factory, "01") == std::nullopt);
                CHECK(eval_input(board, command_factory, "00") == std::nullopt);
                CHECK(eval_input(board, command_factory, "44") == std::nullopt);
                CHECK(eval_input(board, command_factory, "ab") == std::nullopt);
                CHECK(eval_input(board, command_factory, "AB") == std::nullopt);
                CHECK(eval_input(board, command_factory, "XY") == std::nullopt);
                CHECK(eval_input(board, command_factory, "yz") == std::nullopt);
                CHECK(eval_input(board, command_factory, "a") == std::nullopt);
                CHECK(eval_input(board, command_factory, "A") == std::nullopt);
                CHECK(eval_input(board, command_factory, "1") == std::nullopt);
                CHECK(eval_input(board, command_factory, "1?") == std::nullopt);
                CHECK(eval_input(board, command_factory, "?1") == std::nullopt);
                CHECK(eval_input(board, command_factory, "??") == std::nullopt);
                CHECK(eval_input(board, command_factory, "???") == std::nullopt);
                CHECK(eval_input(board, command_factory, " ") == std::nullopt);
                CHECK(eval_input(board, command_factory, "  ") == std::nullopt);
                CHECK(eval_input(board, command_factory, "\n") == std::nullopt);
                CHECK(eval_input(board, command_factory, "\n\n") == std::nullopt);
            }

            SECTION("square on the board must be empty")
            {
                board.change_owner_of_square(Square{1, 0}, human_player_id);

                CHECK(eval_input(board, command_factory, "1a") != std::nullopt);
                CHECK(eval_input(board, command_factory, "1b") == std::nullopt);
            }

            SECTION("command belongs to the human player")
            {
                auto command = eval_input(board, command_factory, "1a");
                controller.execute(std::move(*command));

                CHECK(board.player_of_square({0, 0}) == human_player_id);
            }

            SECTION("the input characters can be turned around")
            {
                const std::vector<std::pair<const char*, Square>> checks{
                    {"1b", Square{1, 0}},
                    {"b1", Square{1, 0}},
                    {"2a", Square{0, 1}},
                    {"a2", Square{0, 1}},
                    {"2C", Square{2, 1}},
                    {"C2", Square{2, 1}},
                };

                for (const auto& check : checks) {
                    Board empty_board;
                    CommandFactory new_command_factory{empty_board, game_state, controller, console_writer};

                    auto command = eval_input(empty_board, new_command_factory, check.first);
                    controller.execute(std::move(*command));

                    CHECK(empty_board.player_of_square(check.second) == human_player_id);
                }
            }
        }
    }

    SECTION("is_valid_alphabetic_input_character()")
    {
        SECTION("character must be one of \"abcABC\"")
        {
            CHECK(is_valid_alphabetic_input_character('1') == false);
            CHECK(is_valid_alphabetic_input_character('2') == false);
            CHECK(is_valid_alphabetic_input_character('3') == false);
            CHECK(is_valid_alphabetic_input_character('a') == true);
            CHECK(is_valid_alphabetic_input_character('b') == true);
            CHECK(is_valid_alphabetic_input_character('c') == true);
            CHECK(is_valid_alphabetic_input_character('A') == true);
            CHECK(is_valid_alphabetic_input_character('B') == true);
            CHECK(is_valid_alphabetic_input_character('C') == true);
        }
    }

    SECTION("is_valid_numeric_input_character()")
    {
        SECTION("character must be one of \"123\"")
        {
            CHECK(is_valid_numeric_input_character('1') == true);
            CHECK(is_valid_numeric_input_character('2') == true);
            CHECK(is_valid_numeric_input_character('3') == true);
            CHECK(is_valid_numeric_input_character('a') == false);
            CHECK(is_valid_numeric_input_character('b') == false);
            CHECK(is_valid_numeric_input_character('c') == false);
            CHECK(is_valid_numeric_input_character('A') == false);
            CHECK(is_valid_numeric_input_character('B') == false);
            CHECK(is_valid_numeric_input_character('C') == false);
        }
    }

    SECTION("is_valid_input_character()")
    {
        SECTION("character must be one of \"abcABC123\"")
        {
            CHECK(is_valid_input_character('1'));
            CHECK(is_valid_input_character('2'));
            CHECK(is_valid_input_character('3'));
            CHECK(is_valid_input_character('a'));
            CHECK(is_valid_input_character('b'));
            CHECK(is_valid_input_character('c'));
            CHECK(is_valid_input_character('A'));
            CHECK(is_valid_input_character('B'));
            CHECK(is_valid_input_character('C'));
            CHECK(is_valid_input_character('0') == false);
            CHECK(is_valid_input_character('4') == false);
            CHECK(is_valid_input_character('d') == false);
            CHECK(is_valid_input_character('D') == false);
            CHECK(is_valid_input_character(0) == false);
            CHECK(is_valid_input_character(1) == false);
            CHECK(is_valid_input_character(2) == false);
            CHECK(is_valid_input_character(3) == false);
            CHECK(is_valid_input_character(4) == false);
            CHECK(is_valid_input_character(' ') == false);
            CHECK(is_valid_input_character('\n') == false);
        }
    }

    SECTION("convert_input_character_to_square_coord()")
    {
        SECTION("returns the integer board coordinate of the digit")
        {
            CHECK(convert_input_character_to_square_coord('1') == 0);
            CHECK(convert_input_character_to_square_coord('2') == 1);
            CHECK(convert_input_character_to_square_coord('3') == 2);
            CHECK(convert_input_character_to_square_coord('a') == 0);
            CHECK(convert_input_character_to_square_coord('b') == 1);
            CHECK(convert_input_character_to_square_coord('c') == 2);
            CHECK(convert_input_character_to_square_coord('A') == 0);
            CHECK(convert_input_character_to_square_coord('B') == 1);
            CHECK(convert_input_character_to_square_coord('C') == 2);
        }
    }
}

}  // namespace tic_tac_toe
