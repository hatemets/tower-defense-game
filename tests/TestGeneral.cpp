#define CATCH_CONFIG_MAIN

#include "../include/auxiliary/constants.hpp"
#include <catch2/catch.hpp>
#include <fstream>
#include <array>


constexpr std::array<char, 5> symbols = {'.', '#', 'S', 'O', 'B'};


void testFile(const std::string& filename)
{
    std::ifstream ifs(filename);
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


TEST_CASE("General gameplay")
{
    SECTION("Constants are valid")
    {
        REQUIRE(WindowWidth > WindowHeight);
        REQUIRE(TileCols > TileRows);
        REQUIRE(TotalLevels > 0);
        
        REQUIRE(WindowWidth / TileCols == WindowHeight / TileRows);
    }

    SECTION("Map files are valid")
    {
        testFile("./include/maps/map1.txt");
        testFile("./include/maps/map2.txt");
        testFile("./include/maps/map3.txt");
        testFile("./include/maps/map4.txt");
        testFile("./include/maps/map5.txt");
        testFile("./include/maps/map6.txt");
    }

    SECTION("Cache file is valid")
    {
        std::ifstream ifs("./include/auxiliary/cache.txt");
        std::string output;

        while (!ifs.eof())
        {
            std::getline(ifs, output);
        }

        int level = std::stoi(output);

        REQUIRE(level > 0);
        REQUIRE(level <= TotalLevels);
    }
}

