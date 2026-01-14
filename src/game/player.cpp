#include "player.hpp"
#include "../core/input.hpp"
#include "../core/joystick.hpp"

Player::Player()
{
}

Player::Player(const Vector2 &pos, Texture *tex) : GameObject(pos, tex)
{

    boundingBox.w = 15;
    boundingBox.h = 43;
    boundingBox.x = 34;
    boundingBox.y = 26;

    std::vector<Frame> walkAnimFrames;

    for(int i = 0; i < 10; i++)
    {
        Frame f;
        f.x = 84 * i;
        f.y = 84;
        f.w = 84;
        f.h = 84;
        walkAnimFrames.push_back(f);
    }

    Animation walkAnimation(walkAnimFrames,5);
    animationController.addAnimation("walk", walkAnimation);
    animationController.setCurrentAnimation("walk");

    std::vector<Frame> idleAnimFrames;
    for(int i = 0; i < 4; i++)
    {
        Frame f;
        f.x = 84 * i;
        f.y = 0;
        f.w = 84;
        f.h = 84;
        idleAnimFrames.push_back(f);
    }
    Animation idleAnimation(idleAnimFrames,10);
    animationController.addAnimation("idle", idleAnimation);
    animationController.setCurrentAnimation("idle");

    speed = 2;

}

Player::~Player()
{
}

void Player::update()
{
    
    velocity.x = 0;
    //velocity.y = 0;
    if(!isOnGround()){
         velocity.y += 0.5; // gravity
    }
   
    velocity.y = std::min(velocity.y, 5.0f); // terminal velocity
    if(Input::getInstance().isKeyPressed(Key::UP) || Joystick::getInstance().isButtonDown(JoystickButton::DPAD_UP))
    {
        velocity.y -= 7.0f;
    } 
    if(Input::getInstance().isKeyDown(Key::DOWN) || Joystick::getInstance().isButtonDown(JoystickButton::DPAD_DOWN))
    {
       velocity.y += speed;
    }

    if(Input::getInstance().isKeyDown(Key::LEFT) || Joystick::getInstance().isButtonDown(JoystickButton::DPAD_LEFT))
    {
        velocity.x -= speed;
    }
    if(Input::getInstance().isKeyDown(Key::RIGHT) || Joystick::getInstance().isButtonDown(JoystickButton::DPAD_RIGHT))
    {
        velocity.x += speed;
    }

    

    if(velocity.x < 0)
        flipState = 1;
    else if(velocity.x > 0)
        flipState = 0;
        
}

void Player::render(Graphics &graphics)
{
    if(velocity.x != 0.0f || velocity.y != 0.0f)
    {
        animationController.setCurrentAnimation("walk");
    }
    else
    {
        animationController.setCurrentAnimation("idle");
    }
    animationController.update();
    Frame frame = animationController.getCurrentFrame();
    graphics.drawTextureRegion(texture, frame.x, frame.y, frame.w, frame.h, static_cast<int>(position.x), static_cast<int>(position.y),flipState);
    
    graphics.drawRectangle(position.x + boundingBox.x, position.y + boundingBox.y, boundingBox.w, boundingBox.h,Color{0.5f,0.0f,0.0f,0.2f});
    //graphics.drawRectangle(boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h);
}

Enemy::Enemy()
{
}

Enemy::Enemy(const Vector2 &pos, Texture *tex)
{

    boundingBox.w = 25;
    boundingBox.h = 20;
    boundingBox.x = 0;
    boundingBox.y = 0;
    position = pos;
    texture = tex;
    std::vector<Frame> idleAnimFrames;
    for(int i = 0; i < 5; i++)
    {
        Frame f;
        f.x = 5+(26*i);
        f.y = 310;
        f.w = 26;
        f.h = 20;
        idleAnimFrames.push_back(f);
    }
    Animation idleAnimation(idleAnimFrames,10);
    animationController.addAnimation("idle", idleAnimation);
    animationController.setCurrentAnimation("idle");
    speed =1.0f;
    velocity.y = 1;
    velocity.x = 1;
}

Enemy::~Enemy()
{
}

void Enemy::update()
{
    velocity.y += 1;

    velocity.x = velocity.x * speed;

    //position += velocity;
}


void Enemy::render(Graphics &graphics)
{
    animationController.update();
    Frame frame = animationController.getCurrentFrame();
    graphics.drawTextureRegion(texture, frame.x, frame.y, frame.w, frame.h, static_cast<int>(position.x), static_cast<int>(position.y),flipState);
}

void Enemy::onTileCollision(int i)
{
    velocity.x *= -1;
}
