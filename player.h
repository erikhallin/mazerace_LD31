#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <gl/gl.h>
#include <vector>
#include "definitions.h"
#include "world.h"
#include "gamepad.h"
#include "particle_engine.h"

struct st_pos
{
    st_pos(float _pos[2])
    {
        pos[0]=_pos[0];
        pos[1]=_pos[1];
    }

    float pos[2];
};

enum en_directions
{
    dir_up=0,
    dir_right,
    dir_down,
    dir_left
};

enum en_controls
{
    //arrows
    cont_p1_up=38,
    cont_p1_right=39,
    cont_p1_down=40,
    cont_p1_left=37,
    //wasd
    cont_p2_up=87,
    cont_p2_right=68,
    cont_p2_down=83,
    cont_p2_left=65,
    //ilkj
    cont_p3_up=73,
    cont_p3_right=76,
    cont_p3_down=75,
    cont_p3_left=74,
    //numpad
    cont_p4_up=104,
    cont_p4_right=102,
    cont_p4_down=101,
    cont_p4_left=100
};

using namespace std;

class player
{
    public:
        player();

        bool init(int player_id,bool* pKeys,world* pWorld,gamepad* pGamepad,particle_engine* pPart_eng);
        bool update(bool gamepad_on);
        bool draw(void);
        bool get_player_pos(float pos[2]);
        bool set_player_pos(float pos[2]);
        bool get_speed(float speed[2]);
        bool set_speed(float speed[2]);

    private:

        bool* m_pKeys;
        int   m_id;
        float m_pos[2];
        float m_pos_start[2];
        float m_size;
        float m_speed[2];

        particle_engine* m_pParticle_engine;
        vector<st_pos> m_vec_ghost_pos;

        bool    m_gamepad_on;
        gamepad m_gamepad;
        bool    m_trigger_ready_up,m_trigger_ready_left,m_trigger_ready_down,m_trigger_ready_right;

        world* m_pWorld;
};

#endif // PLAYER_H
