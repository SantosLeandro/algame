#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Frame
{
public:
    int x;
    int y;
    int w;
    int h;
};

class Animation
{
private:
    int m_currentFrame = 0;
    int m_frameDelay = 5;
    int m_frameCounter = 0;
    std::vector<Frame> m_frames;

public:
    Animation() = default;
    Animation(const std::vector<Frame> &frames, int frameDelay)
        : m_frames(frames), m_frameDelay(frameDelay)
    {
    }

    void update()
    {
        m_frameCounter++;
        if (m_frameCounter >= m_frameDelay)
        {
            m_frameCounter = 0;
            m_currentFrame = (m_currentFrame + 1) % m_frames.size();
        }
    }

    Frame getCurrentFrame() const
    {
        return m_frames[m_currentFrame];
    }
};

class AnimationController
{
private:
    std::unordered_map<std::string, Animation> m_animations;
    Animation *m_currentAnimation = nullptr;

public:
    void addAnimation(const std::string name, const Animation &animation)
    {
        m_animations[name] = animation;
    }

    void setCurrentAnimation(const std::string &name)
    {
        m_currentAnimation = &m_animations[name];
    }

    void update()
    {
        if (m_currentAnimation)
        {
            m_currentAnimation->update();
        }
    }

    Frame getCurrentFrame() const
    {
        if (m_currentAnimation)
        {
            return m_currentAnimation->getCurrentFrame();
        }
        return Frame{0, 0, 32, 32};
    }

    AnimationController loadAnimations(const std::string &filename)
    {
        std::vector<Animation> animations;
        AnimationController controller;
        std::ifstream file(filename);

        if (!file.is_open())
        {
            std::cerr << "Erro ao abrir arquivo\n";
            return controller;
        }

        std::string line;

        while (std::getline(file, line))
        {
            if (line.empty())
                continue;

            std::stringstream ss(line);

            Animation anim;
            int x, y, w, h, totalFrames;

            std::string name;
            int frameDelay;
            ss >> name >> x >> y >> w >> h >> totalFrames >> frameDelay;

            std::vector<Frame> frames;
            for (int i = 0; i < totalFrames; ++i)
            {
                Frame frame;
                frame.x = x + (i * w); // anda na horizontal
                frame.y = y;
                frame.w = w;
                frame.h = h;

                frames.push_back(frame);
            }

            animations.push_back(anim);
        }

        return controller;
    }
};
