#include <catch2/catch_test_macros.hpp>
#include "Tscreen.hpp"
#include "Tlevel.hpp"
#include "Tplayer.hpp"
#include "fakeit.hpp"
#include <memory>

TEST_CASE("Screen_IsCreated_IsAbleToOutput")
{
    //Arrange
    std::shared_ptr<Tscreen> main_screen = std::make_shared<Tscreen>();

    //Act

    bool expected_result = true;
    bool result = main_screen -> main_screen_output();

    //Assert

    REQUIRE(result == expected_result);
}

TEST_CASE("WhenGetChar_IsCalled_ReturnsProperString")
{
    //Arrange
    std::shared_ptr<Tscreen> main_screen = std::make_shared<Tscreen>();

    //Act

    std::string expected_result = ".";
    std::string result = main_screen -> get_char(Tposition(20,35));

    //Assert

    REQUIRE(result == expected_result);
}

TEST_CASE("WhenScreenReplace_IsCalled_ReplaceCharacter")
{
    //Arrange
    std::shared_ptr<Tscreen> main_screen = std::make_shared<Tscreen>();

    //Act
    bool expected_result = true;
    bool result = main_screen -> screen_replace("Text", Tposition(10,4));

    //Assert
    REQUIRE(result == expected_result);
}

using namespace fakeit;
Mock<Ilevel> level_mock;


TEST_CASE("WhenPlayer_IsCreated_ItsPossibleToAssignHimLevel")
{

    //Arrange

    When(Method(level_mock,get_starting_position)).Return(Tposition(0,0));
    Ilevel* level_mock_temp = &level_mock.get();

    std::shared_ptr<Ientity> main_player = std::make_shared<Tplayer>();
    main_player -> assign_level(std::shared_ptr<Ilevel>(level_mock_temp));

    //Act

    auto result = main_player -> get_current_level();
    auto expected_result = nullptr;

    //Assert

    REQUIRE(result != expected_result);
}

TEST_CASE("WhenAssignLevel_IsCalled_CurrentPositionBecomesStartingPositionFromLevel")
{
    //Arrange


}


