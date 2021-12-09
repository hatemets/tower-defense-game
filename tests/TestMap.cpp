#define CATCH_CONFIG_MAIN

#include "../include/auxiliary/constants.hpp"
#include <catch2/catch.hpp>
#include <fstream>
#include <array>


constexpr std::array<char, 5> symbols = {'.', '#', 'S', 'O', 'B'};

TEST_CASE("General gameplay")
{
    SECTION("Constants are valid")
    {
        REQUIRE(WindowWidth > WindowHeight);
        REQUIRE(TileCols > TileRows);
        REQUIRE(TotalLevels > 0);
    }


    SECTION("Map files are valid")
    {
        std::ifstream ifs("./include/maps/map1.txt");
        std::string output;
        int rowCounter = 0;

        while (!ifs.eof())
        {
            std::getline(ifs, output);

            // End of text
            if (output.length() == 0)
            {
                break;
            }

            for (auto ch : output)
            {
                // The symbols array must include the character
                REQUIRE(std::count(symbols.begin(), symbols.end(), ch));
            }


            // Test for the correct amount of columns
            REQUIRE(output.length() == TileCols);

            rowCounter++;
        }


        REQUIRE(rowCounter == TileRows);
    }
}

