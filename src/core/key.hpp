#pragma once

enum class Key {
    NONE = 0,
    A, B, C, D, E, F, G,
    H, I, J, K, L, M, N,
    O, P, Q, R, S, T, U,
    V, W, X, Y, Z,

    LEFT,
    RIGHT,
    UP,
    DOWN,

    SPACE,
    ENTER,
    ESCAPE,
    SHIFT,
    CTRL,
    ALT,

    COUNT
};

Key mapAllegroKey(int k);

