#include "../Utils/header.hpp"

Mock<Ilevel> level_mock;

TEST_CASE("Player_can_move")
{
    //Arrange

    When(Method(level_mock,get_starting_position)).Return(Tposition(20,20));
    When(Method(level_mock,is_next_pixel_wall)).Return(false);
    Ilevel* level_mock_instance = &level_mock.get();

    std::string name("main_player");
    std::shared_ptr<Ientity> main_player = std::make_shared<Tplayer>(name);
    main_player -> assign_level(std::shared_ptr<Ilevel>(level_mock_instance));

    //Act

    SECTION("WhenMoveUP_IsCalled_YpositionIsHigher")
    {
        main_player -> move(Ientity::Movement::Up);
        Tposition expected_result(20,19);
        Tposition result = main_player -> get_current_position();

        //Assert

        REQUIRE(result.m_position_x == expected_result.m_position_x);
        REQUIRE(result.m_position_y == expected_result.m_position_y);

    }

    SECTION("WhenMoveDOWN_IsCalled_YpositionIsLower")
    {
        main_player -> move(Ientity::Movement::Down);
        Tposition expected_result(20,21);
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