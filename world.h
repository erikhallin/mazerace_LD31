#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <gl/gl.h>
#include <vector>
#include "definitions.h"
#include "movable_wall.h"
#include "particle_engine.h"

/*COLOR CODE
Nothing - Black
Wall - Red
Player - White
Goal - Green
Teleport In - Blue
Teleport Out - Yellow

*/

using namespace std;

class world
{
    public:
        world();

        bool init(int window_size[2],particle_engine* pPart_eng);
        bool update(void);
        bool draw(void);

        int   is_pos_ok(float old_pos[2],float new_pos[2]);
        bool  get_player_start_pos(int player_id,int pos[2]);
        float get_world_scale(void);
        int   get_world_draw_height_pos(void);
        bool  get_goal_pos(float pos[2]);
        bool  get_teleport_in1_pos(float pos[2]);
        bool  get_teleport_out1_pos(float pos[2]);
        bool  get_teleport_in2_pos(float pos[2]);
        bool  get_teleport_out2_pos(float pos[2]);

    private:

        particle_engine* m_pParticle_engine;

        int*  m_pWorld_array;
        int   m_world_width,m_world_height,m_window_width,m_window_height;
        int   m_player_start_pos[4][2];
        float m_draw_scale;
        int   m_world_draw_start_height;
        int   m_goal_pos[2],m_teleport_in_pos[2][2],m_teleport_out_pos[2][2];
        float m_time;

        vector<movable_wall> m_vec_movable_walls;

        bool  load_level(void);
        bool  unload_world(void);
};

#endif // WORLD_H
