#include <catch2/catch_test_macros.hpp>
#include "Tlevel.hpp"
#include "Tplayer.hpp"
#include "fakeit.hpp"
#include "Idrawable.hpp"
#include <memory>

// TEST_CASE("Screen_IsCreated_IsAbleToOutput")
// {
//     //Arrange
//     std::shared_ptr<Tscreen> main_screen = std::make_shared<Tscreen>();

//     //Act

//     bool expected_result = true;
//     bool result = main_screen -> main_screen_output();

//     //Assert

//     REQUIRE(result == expected_result);
// }

// TEST_CASE("WhenGetChar_IsCalled_ReturnsProperString")
// {
//     //Arrange
//     std::shared_ptr<Tscreen> main_screen = std::make_shared<Tscreen>();

//     //Act

//     std::string expected_result = ".";
//     std::string result = main_screen -> get_char(Tposition(20,15));

//     //Assert

//     REQUIRE(result == expected_result);
// }

// TEST_CASE("WhenScreenReplace_IsCalled_ReplaceCharacter")
// {
//     //Arrange
//     std::shared_ptr<Tscreen> main_screen = std::make_shared<Tscreen>();

//     //Act
//     bool expected_result = true;
//     bool result = main_screen -> screen_replace("Text", Tposition(10,4));

//     //Assert
//     REQUIRE(result == expected_result);
// }

using namespace fakeit;
Mock<Ilevel> level_mock;
Mock<Idrawable> drawable_mock;


TEST_CASE("WhenPlayer_IsCreated_ItsPossibleToAssignHimLevel")
{

    //Arrange

    When(Method(level_mock,get_starting_position)).Return(Tposition(0,0));
    Ilevel* level_mock_temp = &level_mock.get();

    When(Method(drawable_mock,draw)).Return(true);
    Idrawable* drawable_mock_temp = &drawable_mock.get();

    std::string name("main_player");
    std::shared_ptr<Ientity> main_player = std::make_shared<Tplayer>(name, std::shared_ptr<Idrawable>(drawable_mock_temp));
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
    When(Method(level_mock,get_starting_position)).Return(Tposition(5,5));
    Ilevel* level_mock_instance = &level_mock.get();

    When(Method(drawable_mock,draw)).Return(true);
    Idrawable* drawable_mock_temp = &drawable_mock.get();

    std::string name("main_player");
    std::shared_ptr<Ientity> main_player = std::make_shared<Tplayer>(name, std::shared_ptr<Idrawable>(drawable_mock_temp));
    main_player -> assign_level(std::shared_ptr<Ilevel>(level_mock_instance));

    //Act

    Tposition expected_result(5,5);
    Tposition result = main_player -> get_current_position();

    //Assert

    REQUIRE(result.m_position_x == expected_result.m_position_x);
    REQUIRE(result.m_position_y == expected_result.m_position_y);
}

TEST_CASE("Player_can_move")
{
    //Arrange

    When(Method(level_mock,get_starting_position)).Return(Tposition(20,20));
    Ilevel* level_mock_instance = &level_mock.get();

    When(Method(drawable_mock,draw)).Return(true);
    Idrawable* drawable_mock_temp = &drawable_mock.get();

    std::string name("main_player");
    std::shared_ptr<Ientity> main_player = std::make_shared<Tplayer>(name, std::shared_ptr<Idrawable>(drawable_mock_temp));
    main_player -> assign_level(std::shared_ptr<Ilevel>(level_mock_instance));

    //Act

    SECTION("WhenMoveUP_IsCalled_YpositionIsHigher")
    {
        main_player -> move(Ientity::Movement::Up);
        Tposition expected_result(20,21);
        Tposition result = main_player -> get_current_position();

        //Assert

        REQUIRE(result.m_position_x == expected_result.m_position_x);
        REQUIRE(result.m_position_y == expected_result.m_position_y);

    }

    SECTION("WhenMoveDOWN_IsCalled_YpositionIsLower")
    {
        main_player -> move(Ientity::Movement::Down);
        Tposition expected_result(20,19);
        Tposition result = main_player -> get_current_position();

        //Assert

        REQUIRE(result.m_position_x == expected_result.m_position_x);
        REQUIRE(result.m_position_y == expected_result.m_position_y);
    }

    SECTION("WhenMoveLEFT_IsCalled_XpositionIsLower")
    {
        main_player -> move(Ientity::Movement::Left);
        Tposition expected_result(19,20);
        Tposition result = main_player -> get_current_position();

        //Assert

        REQUIRE(result.m_position_x == expected_result.m_position_x);
        REQUIRE(result.m_position_y == expected_result.m_position_y);
    }

    SECTION("WhenMoveRIGHT_IsCalled_XpositionIsHigher")
    {
        main_player -> move(Ientity::Movement::Right);
        Tposition expected_result(21,20);
        Tposition result = main_player -> get_current_position();

        //Assert

        REQUIRE(result.m_position_x == expected_result.m_position_x);
        REQUIRE(result.m_position_y == expected_result.m_position_y);
    }
}


