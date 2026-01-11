#include <allegro5/allegro.h>
#include "key.hpp"

Key mapAllegroKey(int k) {
    switch(k) {
        
        case ALLEGRO_KEY_LEFT:  return Key::LEFT;
        case ALLEGRO_KEY_RIGHT: return Key::RIGHT;
        case ALLEGRO_KEY_UP:    return Key::UP;
        case ALLEGRO_KEY_DOWN:  return Key::DOWN;
        case ALLEGRO_KEY_ENTER: return Key::ENTER;
        case ALLEGRO_KEY_ESCAPE:return Key::ESCAPE;
        case ALLEGRO_KEY_SPACE: return Key::SPACE;
        case ALLEGRO_KEY_LSHIFT: return Key::SHIFT;
        case ALLEGRO_KEY_LCTRL:  return Key::CTRL;
        case ALLEGRO_KEY_A:     return Key::A;
        case ALLEGRO_KEY_B:     return Key::B;
        case ALLEGRO_KEY_C:     return Key::C;
        case ALLEGRO_KEY_D:     return Key::D;
        case ALLEGRO_KEY_E:     return Key::E;
        case ALLEGRO_KEY_F:     return Key::F;
        case ALLEGRO_KEY_G:     return Key::G;
        case ALLEGRO_KEY_H:     return Key::H;
        case ALLEGRO_KEY_I:     return Key::I;
        case ALLEGRO_KEY_J:     return Key::J;
        case ALLEGRO_KEY_K:     return Key::K;
        case ALLEGRO_KEY_L:     return Key::L;
        case ALLEGRO_KEY_M:     return Key::M;
        case ALLEGRO_KEY_N:     return Key::N;
        case ALLEGRO_KEY_O:     return Key::O;
        case ALLEGRO_KEY_P:     return Key::P;
        case ALLEGRO_KEY_Q:     return Key::Q;
        case ALLEGRO_KEY_R:     return Key::R;
        case ALLEGRO_KEY_S:     return Key::S;
        case ALLEGRO_KEY_T:     return Key::T;
        case ALLEGRO_KEY_U:     return Key::U;
        case ALLEGRO_KEY_V:     return Key::V;
        case ALLEGRO_KEY_W:     return Key::W;
        case ALLEGRO_KEY_X:     return Key::X;
        case ALLEGRO_KEY_Y:     return Key::Y;
        case ALLEGRO_KEY_Z:     return Key::Z;      
        default:                return Key::NONE;
    }
}
