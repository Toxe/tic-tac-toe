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

        SECTION("input must be two digits between 1 and 3")
        {
            const Board board{};

            CHECK(eval_input(board, "19") == std::nullopt);
            CHECK(eval_input(board, "91") == std::nullopt);
            CHECK(eval_input(board, "99") == std::nullopt);
            CHECK(eval_input(board, "01") == std::nullopt);
            CHECK(eval_input(board, "00") == std::nullopt);
            CHECK(eval_input(board, "44") == std::nullopt);
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

            CHECK(eval_input(board, "11") != std::nullopt);
            CHECK(eval_input(board, "12") == std::nullopt);
        }
    }

    SECTION("is_valid_input_digit()")
    {
        SECTION("character must be two digits between '1' and '3'")
        {
            CHECK(is_valid_input_digit('1'));
            CHECK(is_valid_input_digit('2'));
            CHECK(is_valid_input_digit('3'));
            CHECK(is_valid_input_digit('0') == false);
            CHECK(is_valid_input_digit('4') == false);
            CHECK(is_valid_input_digit('\n') == false);
            CHECK(is_valid_input_digit(0) == false);
            CHECK(is_valid_input_digit(1) == false);
            CHECK(is_valid_input_digit(2) == false);
            CHECK(is_valid_input_digit(3) == false);
            CHECK(is_valid_input_digit(4) == false);
        }
    }

    SECTION("convert_input_digit_to_square_coord()")
    {
        SECTION("returns the integer board coordinate of the digit")
        {
            CHECK(convert_input_digit_to_square_coord('1') == 0);
            CHECK(convert_input_digit_to_square_coord('2') == 1);
            CHECK(convert_input_digit_to_square_coord('3') == 2);
        }
    }
}

}  // namespace tic_tac_toe
