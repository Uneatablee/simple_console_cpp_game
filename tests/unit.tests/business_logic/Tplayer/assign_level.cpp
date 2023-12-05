#include <catch2/catch_test_macros.hpp>
#include "Ilevel.hpp"
#include "Tplayer.hpp"
#include "fakeit.hpp"
#include <memory>

using namespace fakeit;

Mock<Ilevel> level_mock_1;

TEST_CASE("WhenPlayer_IsCreated_ItsPossibleToAssignHimLevel")
{

    //Arrange

    When(Method(level_mock_1,get_starting_position)).Return(Tposition(0,0));
    Ilevel* level_mock_temp = &level_mock_1.get();

    std::string name("main_player");
    std::shared_ptr<Ientity> main_player = std::make_shared<Tplayer>(name);
    main_player -> assign_level(std::shared_ptr<Ilevel>(level_mock_temp));

    //Act

    auto result = main_player -> get_current_level();
    auto not_expected_result = nullptr;

    //Assert

    REQUIRE(result != not_expected_result);
}

TEST_CASE("WhenAssignLevel_IsCalled_CurrentPositionBecomesStartingPositionFromLevel")
{
    //Arrange
    When(Method(level_mock_1,get_starting_position)).Return(Tposition(5,5));
    Ilevel* level_mock_instance = &level_mock_1.get();

    std::string name("main_player");
    std::shared_ptr<Ientity> main_player = std::make_shared<Tplayer>(name);
    main_player -> assign_level(std::shared_ptr<Ilevel>(level_mock_instance));

    //Act

    Tposition expected_result(5,5);
    Tposition result = main_player -> get_current_position();

    //Assert

    REQUIRE(result.m_position_x == expected_result.m_position_x);
    REQUIRE(result.m_position_y == expected_result.m_position_y);
}