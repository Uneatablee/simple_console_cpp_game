#include <catch2/catch_test_macros.hpp>
#include "Tscreen.hpp"
#include <memory>

TEST_CASE("ScreenIsCreated_IsAbleToOutput")
{
    //Arrange
    std::shared_ptr<Tscreen> main_screen = std::make_shared<Tscreen>();

    //Act

    bool expected_result = true;
    bool result = main_screen -> main_screen_output();

    //Assert

    REQUIRE(result == expected_result);
}

TEST_CASE("WhenGetCharIsCalled_ReturnsProperString")
{
    //Arrange
    std::shared_ptr<Tscreen> main_screen = std::make_shared<Tscreen>();

    //Act

    std::string expected_result = ".";
    std::string result = main_screen -> get_char(20,35);

    //Assert

    REQUIRE(result == expected_result);
}

TEST_CASE("WhenScreenReplaceIsCalled_ReplaceCharacter")
{
    //Arrange
    std::shared_ptr<Tscreen> main_screen = std::make_shared<Tscreen>();

    //Act
    bool expected_result = true;
    bool result = main_screen -> screen_replace("Text", 10, 4);

    //Assert
    REQUIRE(result == expected_result);
}

