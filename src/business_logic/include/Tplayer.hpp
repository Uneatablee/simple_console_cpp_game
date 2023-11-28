#pragma once
#include "Ientity.hpp"
#include "Ilevel.hpp"
#include "Idrawable.hpp"
#include <memory>

struct Tposition;
class Tscreen;

class Tplayer : virtual public Ientity, virtual public Idrawable
{
private:

    Tposition m_current_position;
    std::shared_ptr<Ilevel> m_current_level = nullptr;
    std::string m_name;
    std::shared_ptr<Idrawable> m_drawer = nullptr;

public:

    Tplayer(std::string init_name, const std::shared_ptr<Idrawable>& m_drawer);
    ~Tplayer() override = default;
    bool assign_level(std::shared_ptr<Ilevel> p_current_level) override;
    bool move(Movement) override;
    std::string get_name() override;
    std::shared_ptr<Ilevel> get_current_level() override;
    Tposition get_current_position() override;
    bool draw(const std::shared_ptr<Tscreen>& screen, Tposition position) override;
    bool change_current_position(Tposition position) override;
};