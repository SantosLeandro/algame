#include "gameobject.hpp"


class Door : public GameObject
{   
public:
    Door();
    Door(const Vector2 &pos, Texture *tex);
    ~Door();
    void render(Graphics &graphics) override;
    std::string targert;
};