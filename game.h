#ifndef GAME_H
#define GAME_H

#include <SOIL/SOIL.h>
#include <iostream>
#include <ctime>
#include <gl/gl.h>
#include "definitions.h"
#include "player.h"
#include "world.h"
#include "gamepad.h"
#include "sound.h"
#include "particle_engine.h"

using namespace std;

class game
{
    public:
        game();

        bool init(int screen_size[2],bool* pKeys,bool* pMouse_but,int* pMouse_pos);
        bool update(void);
        bool draw(void);

    private:

        int   m_screen_width,m_screen_height;
        bool* m_pKeys;
        bool* m_pMouse_but;
        int*  m_pMouse_pos;
        float m_time_last_cycle,m_time_this_cycle;
        int   m_tex_menu,m_tex_world,m_tex_gameover,m_music_channel;
        bool  m_gamepad_connected[4];
        bool  m_music_loop_started,m_game_over,m_in_menu;

        gamepad* m_pGamepads;
        sound*   m_pSound;
        world*   m_pWorld;
        player   m_players[4];
        particle_engine* m_pParticle_engine;

        bool load_textures(void);
        bool load_sounds(void);
};

#endif // GAME_H
