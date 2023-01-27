#include <utility>
#include <vector>

#include "catch2/catch_test_macros.hpp"

#include "../src/app/app_controller.hpp"
#include "../src/input/eval_input.hpp"

namespace tic_tac_toe {

TEST_CASE("input/eval_input")
{
    Board board{};
    GameState game_state{};
    AppController controller{};

    SECTION("eval_input()")
    {
        SECTION("empty input returns an invalid command (nullopt)")
        {
            CHECK(eval_input(game_state, board, controller, "") == std::nullopt);
        }

        SECTION("simple keyword commands")
        {
            CHECK(eval_input(game_state, board, controller, "?") != std::nullopt);
            CHECK(eval_input(game_state, board, controller, "h") != std::nullopt);
            CHECK(eval_input(game_state, board, controller, "q") != std::nullopt);
            CHECK(eval_input(game_state, board, controller, "r") != std::nullopt);
            CHECK(eval_input(game_state, board, controller, "u") != std::nullopt);
            CHECK(eval_input(game_state, board, controller, "exit") != std::nullopt);
            CHECK(eval_input(game_state, board, controller, "help") != std::nullopt);
            CHECK(eval_input(game_state, board, controller, "quit") != std::nullopt);
            CHECK(eval_input(game_state, board, controller, "redo") != std::nullopt);
            CHECK(eval_input(game_state, board, controller, "undo") != std::nullopt);
        }

        SECTION("player move commands")
        {
            SECTION("input must be one alphabetic character (\"abcABC\") and one digit (\"123\")")
            {
                CHECK(eval_input(game_state, board, controller, "12") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, "32") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, "19") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, "91") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, "99") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, "01") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, "00") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, "44") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, "ab") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, "AB") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, "XY") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, "yz") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, "a") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, "A") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, "1") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, "1?") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, "?1") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, "??") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, "???") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, " ") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, "  ") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, "\n") == std::nullopt);
                CHECK(eval_input(game_state, board, controller, "\n\n") == std::nullopt);
            }

            SECTION("square on the board must be empty")
            {
                board.change_owner_of_square(Square{0, 1}, human_player_id);

                CHECK(eval_input(game_state, board, controller, "1a") != std::nullopt);
                CHECK(eval_input(game_state, board, controller, "1b") == std::nullopt);
            }

            SECTION("command belongs to the human player")
            {
                auto command = eval_input(game_state, board, controller, "1a");
                controller.execute(std::move(*command));

                CHECK(board.player_of_square({0, 0}) == human_player_id);
            }

            SECTION("the input characters can be turned around")
            {
                const std::vector<std::pair<const char*, Square>> checks{
                    {"1b", Square{0, 1}},
                    {"b1", Square{0, 1}},
                    {"2a", Square{1, 0}},
                    {"a2", Square{1, 0}},
                    {"2C", Square{1, 2}},
                    {"C2", Square{1, 2}},
                };

                for (const auto& check : checks) {
                    Board empty_board{};
                    auto command = eval_input(game_state, empty_board, controller, check.first);
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
