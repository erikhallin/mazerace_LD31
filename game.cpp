#include "game.h"

game::game()
{
    //ctor
}

bool game::init(int screen_size[2],bool* pKeys,bool* pMouse_but,int* pMouse_pos)
{
    cout<<"Game: Initialization start\n";

    m_screen_width=screen_size[0];
    m_screen_height=screen_size[1];
    m_pKeys=pKeys;
    m_pMouse_but=pMouse_but;
    m_pMouse_pos=pMouse_pos;
    m_time_this_cycle=m_time_last_cycle=(float)clock()/(float)CLOCKS_PER_SEC;
    m_music_channel=20;
    m_music_loop_started=false;
    m_game_over=false;
    m_in_menu=true;

    //texture
    if(!load_textures())
    {
        cout<<"ERROR: Could not load textures\n";
        return false;
    }

    //sound
    if(!load_sounds())
    {
        cout<<"ERROR: Could not load sounds\n";
        return false;
    }

    //start music
    m_pSound->playSimpleSound(wav_music_intro,1.0,m_music_channel);

    //init gamepads
    m_pGamepads=new gamepad[4];
    for(int gamepad_i=0;gamepad_i<4;gamepad_i++)
    {
        m_pGamepads[gamepad_i]=gamepad(gamepad_i);
        if( m_pGamepads[gamepad_i].IsConnected() )
         m_gamepad_connected[gamepad_i]=true;
        else
         m_gamepad_connected[gamepad_i]=false;
    }

    //init particle engine
    m_pParticle_engine=new particle_engine();
    m_pParticle_engine->init();

    //init world
    m_pWorld=new world();
    if( !m_pWorld->init(screen_size,m_pParticle_engine) )
    {
        cout<<"ERROR: Could not initialize world\n";
    }

    //init players
    for(int player_i=0;player_i<4;player_i++)
    {
        m_players[player_i].init(player_i,m_pKeys,m_pWorld,m_pGamepads,m_pParticle_engine);
    }

    cout<<"Game: Initialization complete\n";

    return true;
}

bool game::update(void)
{
    //time
    m_time_last_cycle=m_time_this_cycle;
    m_time_this_cycle=(float)clock()/(float)CLOCKS_PER_SEC;
    //static time shift (_game_update_step)

    //test if music intro done
    if(!m_music_loop_started)
    {
        if(m_pSound->get_source_status(m_music_channel))
        {
            m_music_loop_started=true;
            m_pSound->playSimpleSound(wav_music_loop,1.0,m_music_channel,true);
        }
    }

    //get gamepad data
    st_gamepad_data gamepad_data[4];
    for(int gamepad_i=0;gamepad_i<4;gamepad_i++)
    {
        if( m_pGamepads[gamepad_i].IsConnected() )
        {
            //new gamepad?
            if(!m_gamepad_connected[gamepad_i])
            {
                cout<<"New connection to controller: "<<gamepad_i+1<<endl;
            }

            m_gamepad_connected[gamepad_i]=true;
            gamepad_data[gamepad_i]=m_pGamepads[gamepad_i].GetState();
        }
        else//lost controller
        {
            if( m_gamepad_connected[gamepad_i] )//had connection and lost it
            {
                m_gamepad_connected[gamepad_i]=false;
                cout<<"Lost connection to controller: "<<gamepad_i+1<<endl;
            }
        }
    }

    if(m_in_menu)
    {
        for(int i=0;i<256;i++)
        {
            if(m_pKeys[i])
            {
                m_pKeys[i]=false;
                m_in_menu=false;
            }
        }
        //gamepad start
        for(int gamepad_i=0;gamepad_i<4;gamepad_i++)
        {
            if(m_gamepad_connected[gamepad_i])
            {
                if(gamepad_data[gamepad_i].button_start)
                {
                    m_in_menu=false;
                }
            }
        }
    }
    else if(m_game_over)
    {
        //wait for restart key
        for(int i=0;i<256;i++)
        {
            if(m_pKeys[i])
            {
                m_pKeys[i]=false;
                m_game_over=false;
                m_in_menu=true;
                //reset player pos
                for(int player_i=0;player_i<4;player_i++)
                {
                    m_players[player_i].init(player_i,m_pKeys,m_pWorld,m_pGamepads,m_pParticle_engine);
                }
            }
        }
        //gamepad start
        for(int gamepad_i=0;gamepad_i<4;gamepad_i++)
        {
            if(m_gamepad_connected[gamepad_i])
            {
                if(gamepad_data[gamepad_i].button_start)
                {
                    m_game_over=false;
                    m_in_menu=true;
                    //reset player pos
                    for(int player_i=0;player_i<4;player_i++)
                    {
                        m_players[player_i].init(player_i,m_pKeys,m_pWorld,m_pGamepads,m_pParticle_engine);
                    }
                }
            }
        }
    }
    else//update all
    {
        //update world
        m_pWorld->update();

        //update players
        for(int player_i=0;player_i<4;player_i++)
        {
            if( !m_players[player_i].update(m_gamepad_connected[player_i]) )
            {
                //collision, play sound
                m_pSound->playSimpleSound(wav_collision,1.0);
            }
        }

        //test player-player collision
        float player_pos[4][2];
        for(int player_i=0;player_i<4;player_i++)
        {
            m_players[player_i].get_player_pos(player_pos[player_i]);
        }
        for(int player_i1=0;player_i1<4;player_i1++)
        {
            for(int player_i2=0;player_i2<4;player_i2++)
            {
                if(player_i1==player_i2) continue;

                if( player_pos[player_i1][0] > player_pos[player_i2][0] - _player_size*2.0 &&
                    player_pos[player_i1][0] < player_pos[player_i2][0] + _player_size*2.0 &&
                    player_pos[player_i1][1] > player_pos[player_i2][1] - _player_size*2.0 &&
                    player_pos[player_i1][1] < player_pos[player_i2][1] + _player_size*2.0 )
                {
                    //inside, change speed
                    //highest y or x dist
                    float x_dist=player_pos[player_i1][0]-player_pos[player_i2][0];
                    float y_dist=player_pos[player_i1][1]-player_pos[player_i2][1];
                    bool x_split=false;
                    if( fabs(x_dist) > fabs(y_dist) ) x_split=true;
                    if(x_split)
                    {
                        if(x_dist>0.0)
                        {
                            float speed_p1[2]={_player_speed,0};
                            float speed_p2[2]={-_player_speed,0};
                            m_players[player_i1].set_speed(speed_p1);
                            m_players[player_i2].set_speed(speed_p2);
                        }
                        else
                        {
                            float speed_p1[2]={-_player_speed,0};
                            float speed_p2[2]={_player_speed,0};
                            m_players[player_i1].set_speed(speed_p1);
                            m_players[player_i2].set_speed(speed_p2);
                        }
                    }
                    else
                    {
                        if(y_dist>0.0)
                        {
                            float speed_p1[2]={0,_player_speed};
                            float speed_p2[2]={0,-_player_speed};
                            m_players[player_i1].set_speed(speed_p1);
                            m_players[player_i2].set_speed(speed_p2);
                        }
                        else
                        {
                            float speed_p1[2]={0,-_player_speed};
                            float speed_p2[2]={0,_player_speed};
                            m_players[player_i1].set_speed(speed_p1);
                            m_players[player_i2].set_speed(speed_p2);
                        }
                    }

                    //draw explosion
                    float color[3]={1,1,1};
                    float exp_pos[2];
                    exp_pos[0]=player_pos[player_i1][0]+x_dist*0.5;
                    exp_pos[1]=player_pos[player_i1][1]+y_dist*0.5;
                    m_pParticle_engine->add_explosion(exp_pos,5,0.2,200,color);
                }
            }
        }

        //test if player near goal
        float goal_pos[2];
        m_pWorld->get_goal_pos(goal_pos);
        for(int player_i=0;player_i<4;player_i++)
        {
            if( player_pos[player_i][0] > goal_pos[0] - _player_size*3.0 &&
                player_pos[player_i][0] < goal_pos[0] + _player_size*3.0 &&
                player_pos[player_i][1] > goal_pos[1] - _player_size*3.0 &&
                player_pos[player_i][1] < goal_pos[1] + _player_size*3.0 )
            {
                m_game_over=true;
                //play sound
                m_pSound->playSimpleSound(wav_teleport,1);
            }
        }

        //test if near teleport 1
        float teleport_in_pos[2];
        float teleport_out_pos[2];
        m_pWorld->get_teleport_in1_pos(teleport_in_pos);
        m_pWorld->get_teleport_out1_pos(teleport_out_pos);
        for(int player_i=0;player_i<4;player_i++)
        {
            if( player_pos[player_i][0] > teleport_in_pos[0] - _player_size*3.0 &&
                player_pos[player_i][0] < teleport_in_pos[0] + _player_size*3.0 &&
                player_pos[player_i][1] > teleport_in_pos[1] - _player_size*3.0 &&
                player_pos[player_i][1] < teleport_in_pos[1] + _player_size*3.0 )
            {
                //move player to teleport out
                m_players[player_i].set_player_pos(teleport_out_pos);
                //flip speed
                float move_speed[2];
                m_players[player_i].get_speed(move_speed);
                move_speed[0]=-move_speed[0];
                move_speed[1]=-move_speed[1];
                m_players[player_i].set_speed(move_speed);
                //play sound
                m_pSound->playSimpleSound(wav_teleport,1);
            }
        }
        //test if near teleport 2
        m_pWorld->get_teleport_in2_pos(teleport_in_pos);
        m_pWorld->get_teleport_out2_pos(teleport_out_pos);
        for(int player_i=0;player_i<4;player_i++)
        {
            if( player_pos[player_i][0] > teleport_in_pos[0] - _player_size*3.0 &&
                player_pos[player_i][0] < teleport_in_pos[0] + _player_size*3.0 &&
                player_pos[player_i][1] > teleport_in_pos[1] - _player_size*3.0 &&
                player_pos[player_i][1] < teleport_in_pos[1] + _player_size*3.0 )
            {
                //move player to teleport out
                m_players[player_i].set_player_pos(teleport_out_pos);
                //flip speed
                float move_speed[2];
                m_players[player_i].get_speed(move_speed);
                move_speed[0]=-move_speed[0];
                move_speed[1]=-move_speed[1];
                m_players[player_i].set_speed(move_speed);
                //play sound
                m_pSound->playSimpleSound(wav_teleport,1);
            }
        }
    }

    return true;
}

bool game::draw(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    if(m_in_menu)
    {
        //menu texture draw
        glTranslatef( 0, m_pWorld->get_world_draw_height_pos(), 0 );
        //float draw_scale=m_pWorld->get_world_scale();
        //glScalef(draw_scale,draw_scale,draw_scale);

        glColor3f(1,1,1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,m_tex_menu);
        glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex2f(0,0);
        glTexCoord2f(0,0);
        glVertex2f(0,m_screen_height-m_pWorld->get_world_draw_height_pos()*2.0);
        glTexCoord2f(1,0);
        glVertex2f(m_screen_width,m_screen_height-m_pWorld->get_world_draw_height_pos()*2.0);
        glTexCoord2f(1,1);
        glVertex2f(m_screen_width,0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    else if(m_game_over)
    {
        //gameover texture draw
        glTranslatef( 0, m_pWorld->get_world_draw_height_pos(), 0 );
        //float draw_scale=m_pWorld->get_world_scale();
        //glScalef(draw_scale,draw_scale,draw_scale);

        glColor3f(1,1,1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,m_tex_gameover);
        glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex2f(0,0);
        glTexCoord2f(0,0);
        glVertex2f(0,m_screen_height-m_pWorld->get_world_draw_height_pos()*2.0);
        glTexCoord2f(1,0);
        glVertex2f(m_screen_width,m_screen_height-m_pWorld->get_world_draw_height_pos()*2.0);
        glTexCoord2f(1,1);
        glVertex2f(m_screen_width,0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    else
    {
        //get world draw scale
        glTranslatef( 0, m_pWorld->get_world_draw_height_pos(), 0 );

        //draw world texture
        glColor3f(1,1,1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,m_tex_world);
        glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex2f(0,0);
        glTexCoord2f(0,0);
        glVertex2f(0,m_screen_height-m_pWorld->get_world_draw_height_pos()*2.0);
        glTexCoord2f(1,0);
        glVertex2f(m_screen_width,m_screen_height-m_pWorld->get_world_draw_height_pos()*2.0);
        glTexCoord2f(1,1);
        glVertex2f(m_screen_width,0);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        //draw world
        float draw_scale=m_pWorld->get_world_scale();
        glScalef(draw_scale,draw_scale,draw_scale);
        m_pWorld->draw();

        //draw players
        for(int player_i=0;player_i<4;player_i++)
        {
            m_players[player_i].draw();
        }
    }



    glPopMatrix();

    return true;
}


//PRIVATE

bool game::load_textures(void)
{
    cout<<"Loading textures\n";

    m_tex_menu=SOIL_load_OGL_texture
	(
		"texture\\menu.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT //SOIL_FLAG_MIPMAPS (mer suddig)
	);

	m_tex_world=SOIL_load_OGL_texture
	(
		"texture\\world.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT //SOIL_FLAG_MIPMAPS (mer suddig)
	);

	m_tex_gameover=SOIL_load_OGL_texture
	(
		"texture\\gameover.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT //SOIL_FLAG_MIPMAPS (mer suddig)
	);

	if(m_tex_menu==0 || m_tex_world==0 || m_tex_gameover==0 )
	{
	    return false;
	}

    return true;
}

bool game::load_sounds(void)
{
    cout<<"Loading sounds\n";

    m_pSound=new sound();

    bool error_flag=false;

    //if( !m_pSound->load_WAVE_from_file( wav_beep1,"sound\\beep1.wav" ) ) error_flag=true;
    if( !m_pSound->load_WAVE_from_file( wav_music_intro,"sound\\music_intro.wav" ) ) error_flag=true;
    if( !m_pSound->load_WAVE_from_file( wav_music_loop,"sound\\music_loop.wav" ) ) error_flag=true;
    if( !m_pSound->load_WAVE_from_file( wav_collision,"sound\\collision.wav" ) ) error_flag=true;
    if( !m_pSound->load_WAVE_from_file( wav_teleport,"sound\\teleport.wav" ) ) error_flag=true;

    if(error_flag)
    {
        cout<<"ERROR: Problem loading sound files\n";
        return false;
    }

    return true;
}
