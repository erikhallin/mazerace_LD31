#ifndef MOVABLE_WALL_H
#define MOVABLE_WALL_H

#include <iostream>
#include <gl/gl.h>
#include "definitions.h"

using namespace std;

class movable_wall
{
    public:
        movable_wall();

        bool init(int window_size[2],float wall_pos[2],float wall_size[2],float pos_b[2],float speed);
        bool update(void);
        bool draw(void);
        bool is_pos_ok(float pos[2]);

    private:

        int   m_window_width,m_window_height;
        float m_pos[2];
        float m_size[2];
        float m_pos_a[2];
        float m_pos_b[2];
        float m_speed;
        bool  m_move_dir_reverse;
        float m_time_left;
};

#endif // MOVABLE_WALL_H
