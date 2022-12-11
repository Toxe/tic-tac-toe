#include "catch2/catch_test_macros.hpp"

#include "eval_input.hpp"

namespace tic_tac_toe {

TEST_CASE("input/eval_input")
{
    SECTION("eval_input()")
    {
        SECTION("empty input returns an invalid command (nullopt)")
        {
            const Board board{};

            CHECK(eval_input(board, "") == std::nullopt);
        }

        SECTION("input must be one alphabetic character (\"abcABC\") and one digit (\"123\")")
        {
            const Board board{};

            CHECK(eval_input(board, "12") == std::nullopt);
            CHECK(eval_input(board, "32") == std::nullopt);
            CHECK(eval_input(board, "19") == std::nullopt);
            CHECK(eval_input(board, "91") == std::nullopt);
            CHECK(eval_input(board, "99") == std::nullopt);
            CHECK(eval_input(board, "01") == std::nullopt);
            CHECK(eval_input(board, "00") == std::nullopt);
            CHECK(eval_input(board, "44") == std::nullopt);
            CHECK(eval_input(board, "ab") == std::nullopt);
            CHECK(eval_input(board, "AB") == std::nullopt);
            CHECK(eval_input(board, "XY") == std::nullopt);
            CHECK(eval_input(board, "yz") == std::nullopt);
            CHECK(eval_input(board, "a") == std::nullopt);
            CHECK(eval_input(board, "A") == std::nullopt);
            CHECK(eval_input(board, "1") == std::nullopt);
            CHECK(eval_input(board, "?") == std::nullopt);
            CHECK(eval_input(board, "1?") == std::nullopt);
            CHECK(eval_input(board, "?1") == std::nullopt);
            CHECK(eval_input(board, "??") == std::nullopt);
            CHECK(eval_input(board, "???") == std::nullopt);
            CHECK(eval_input(board, " ") == std::nullopt);
            CHECK(eval_input(board, "  ") == std::nullopt);
            CHECK(eval_input(board, "\n") == std::nullopt);
            CHECK(eval_input(board, "\n\n") == std::nullopt);
        }

        SECTION("square on the board must be empty")
        {
            Board board{};

            board.change_owner_of_square(Square{0, 1}, 1);

            CHECK(eval_input(board, "a1") != std::nullopt);
            CHECK(eval_input(board, "a2") == std::nullopt);
        }

        SECTION("command belongs to the human player")
        {
            const Board board{};
            const auto command = eval_input(board, "1a");

            CHECK(command->player == human_player_id);
        }

        SECTION("the input characters can be turned around")
        {
            const Board board{};

            CHECK(eval_input(board, "a2")->square == Square{0, 1});
            CHECK(eval_input(board, "2a")->square == Square{0, 1});
            CHECK(eval_input(board, "b1")->square == Square{1, 0});
            CHECK(eval_input(board, "1b")->square == Square{1, 0});
            CHECK(eval_input(board, "B3")->square == Square{1, 2});
            CHECK(eval_input(board, "3B")->square == Square{1, 2});
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
