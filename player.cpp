#include "player.h"

player::player()
{
    //ctor
}

bool player::init(int player_id,bool* pKeys,world* pWorld,gamepad* pGamepad,particle_engine* pPart_eng)
{
    m_vec_ghost_pos.clear();
    m_id=player_id;
    m_pKeys=pKeys;
    m_pWorld=pWorld;
    m_pParticle_engine=pPart_eng;
    //get start pos
    int start_pos[2]={0,0};
    m_pWorld->get_player_start_pos(m_id,start_pos);
    m_pos[0]=m_pos_start[0]=start_pos[0];
    m_pos[1]=m_pos_start[1]=start_pos[1];
    m_size=_player_size;
    m_speed[0]=0.0;
    m_speed[1]=0.0;
    m_gamepad_on=false;
    m_gamepad=pGamepad[player_id];
    m_trigger_ready_up=m_trigger_ready_left=m_trigger_ready_down=m_trigger_ready_right=true;

    return true;
}

bool player::update(bool gamepad_on)
{
    //get gamepad data
    st_gamepad_data gamepad_data;
    if(m_gamepad.IsConnected())
    {
        m_gamepad_on=true;
        gamepad_data=m_gamepad.GetState();
    }
    else m_gamepad_on=false;

    //read gamepad input
    if(m_gamepad_on)
    {
        int thumbstick_trigger_limit=10000;

        if(gamepad_data.button_Y || gamepad_data.dpad_up ||
           gamepad_data.thumbstick_left_y > thumbstick_trigger_limit ||
           gamepad_data.thumbstick_right_y > thumbstick_trigger_limit)
        {
            if(m_trigger_ready_up)
            {
                m_speed[0]=0.0;
                m_speed[1]=-_player_speed;
                m_trigger_ready_up=false;
            }
        } else m_trigger_ready_up=true;

        if(gamepad_data.button_B || gamepad_data.dpad_right ||
           gamepad_data.thumbstick_left_x > thumbstick_trigger_limit ||
           gamepad_data.thumbstick_right_x > thumbstick_trigger_limit)
        {
            if(m_trigger_ready_right)
            {
                m_speed[0]=_player_speed;
                m_speed[1]=0.0;
                m_trigger_ready_right=false;
            }
        } else m_trigger_ready_right=true;

        if(gamepad_data.button_A || gamepad_data.dpad_down ||
           gamepad_data.thumbstick_left_y < -thumbstick_trigger_limit ||
           gamepad_data.thumbstick_right_y < -thumbstick_trigger_limit)
        {
            if(m_trigger_ready_down)
            {
                m_speed[0]=0.0;
                m_speed[1]=_player_speed;
                m_trigger_ready_down=false;
            }
        } else m_trigger_ready_down=true;

        if(gamepad_data.button_X || gamepad_data.dpad_left ||
           gamepad_data.thumbstick_left_x < -thumbstick_trigger_limit ||
           gamepad_data.thumbstick_right_x < -thumbstick_trigger_limit)
        {
            if(m_trigger_ready_left)
            {
                m_speed[0]=-_player_speed;
                m_speed[1]=0.0;
                m_trigger_ready_left=false;
            }
        } else m_trigger_ready_left=true;
    }

    //get set of keys to read
    int key_input[4];//up,right,down,left
    switch(m_id)
    {
        case 0:
        {
            key_input[dir_up]=cont_p1_up;
            key_input[dir_left]=cont_p1_left;
            key_input[dir_down]=cont_p1_down;
            key_input[dir_right]=cont_p1_right;
        }break;

        case 1:
        {
            key_input[dir_up]=cont_p2_up;
            key_input[dir_left]=cont_p2_left;
            key_input[dir_down]=cont_p2_down;
            key_input[dir_right]=cont_p2_right;
        }break;

        case 2:
        {
            key_input[dir_up]=cont_p3_up;
            key_input[dir_left]=cont_p3_left;
            key_input[dir_down]=cont_p3_down;
            key_input[dir_right]=cont_p3_right;
        }break;

        case 3:
        {
            key_input[dir_up]=cont_p4_up;
            key_input[dir_left]=cont_p4_left;
            key_input[dir_down]=cont_p4_down;
            key_input[dir_right]=cont_p4_right;
        }break;
    }

    //read keyboard input
    if(m_pKeys[ key_input[dir_up] ])
    {
        m_speed[0]=0.0;
        m_speed[1]=-_player_speed;
        m_pKeys[ key_input[dir_up] ]=false;
    }
    if(m_pKeys[ key_input[dir_right] ])
    {
        m_speed[0]=_player_speed;
        m_speed[1]=0.0;
        m_pKeys[ key_input[dir_right] ]=false;
    }
    if(m_pKeys[ key_input[dir_down] ])
    {
        m_speed[0]=0.0;
        m_speed[1]=_player_speed;
        m_pKeys[ key_input[dir_down] ]=false;
    }
    if(m_pKeys[ key_input[dir_left] ])
    {
        m_speed[0]=-_player_speed;
        m_speed[1]=0.0;
        m_pKeys[ key_input[dir_left] ]=false;
    }

    //update pos
    float new_pos[2]={m_pos[0],m_pos[1]};
    new_pos[0]+=m_speed[0];
    new_pos[1]+=m_speed[1];

    /*//test if new pos is ok (test center only)
    if( m_pWorld->is_pos_ok(m_pos,new_pos)==0 )
    {
        //cout<<"pos ok\n";
        m_pos[0]=new_pos[0];
        m_pos[1]=new_pos[1];
    }*/

    //test if new pos is ok (test all edges)
    float old_edge_pos_TL[2]={ m_pos[0]-m_size, m_pos[1]+m_size };
    float old_edge_pos_TR[2]={ m_pos[0]+m_size, m_pos[1]+m_size };
    float old_edge_pos_DR[2]={ m_pos[0]+m_size, m_pos[1]-m_size };
    float old_edge_pos_DL[2]={ m_pos[0]-m_size, m_pos[1]-m_size };
    float old_edge_pos_T[2]={ m_pos[0], m_pos[1]+m_size };
    float old_edge_pos_R[2]={ m_pos[0]+m_size, m_pos[1] };
    float old_edge_pos_D[2]={ m_pos[0], m_pos[1]-m_size };
    float old_edge_pos_L[2]={ m_pos[0]-m_size, m_pos[1] };
    float new_edge_pos_TL[2]={ new_pos[0]-m_size, new_pos[1]+m_size };
    float new_edge_pos_TR[2]={ new_pos[0]+m_size, new_pos[1]+m_size };
    float new_edge_pos_DR[2]={ new_pos[0]+m_size, new_pos[1]-m_size };
    float new_edge_pos_DL[2]={ new_pos[0]-m_size, new_pos[1]-m_size };
    float new_edge_pos_T[2]={ new_pos[0], new_pos[1]+m_size };
    float new_edge_pos_R[2]={ new_pos[0]+m_size, new_pos[1] };
    float new_edge_pos_D[2]={ new_pos[0], new_pos[1]-m_size };
    float new_edge_pos_L[2]={ new_pos[0]-m_size, new_pos[1] };
    if( m_pWorld->is_pos_ok(old_edge_pos_TL,new_edge_pos_TL)==0 &&
        m_pWorld->is_pos_ok(old_edge_pos_TR,new_edge_pos_TR)==0 &&
        m_pWorld->is_pos_ok(old_edge_pos_DR,new_edge_pos_DR)==0 &&
        m_pWorld->is_pos_ok(old_edge_pos_DL,new_edge_pos_DL)==0 &&
        m_pWorld->is_pos_ok(old_edge_pos_T,new_edge_pos_T)==0 &&
        m_pWorld->is_pos_ok(old_edge_pos_R,new_edge_pos_R)==0 &&
        m_pWorld->is_pos_ok(old_edge_pos_D,new_edge_pos_D)==0 &&
        m_pWorld->is_pos_ok(old_edge_pos_L,new_edge_pos_L)==0 )
    {
        //cout<<"pos ok\n";
        m_pos[0]=new_pos[0];
        m_pos[1]=new_pos[1];
    }
    else //collision, reset to start pos
    {
        //explosion
        float color[3]={1,1,1};
        switch(m_id)
        {
            case 0: color[0]=1.0; color[1]=0.6; color[2]=0.6; break;
            case 1: color[0]=0.6; color[1]=0.6; color[2]=1.0; break;
            case 2: color[0]=0.6; color[1]=1.0; color[2]=0.6; break;
            case 3: color[0]=1.0; color[1]=1.0; color[2]=0.6; break;
        }
        m_pParticle_engine->add_explosion(new_pos,40,0.40,400.0,color);

        m_pos[0]=m_pos_start[0];
        m_pos[1]=m_pos_start[1];

        m_speed[0]=m_speed[1]=0.0;

        //create ghost
        m_vec_ghost_pos.push_back(st_pos(new_pos));

        return false;
    }

    //test if near goal


    return true;
}

bool player::draw(void)
{
    //draw player
    switch(m_id)
    {
        case 0: glColor3f(1,0,0); break;
        case 1: glColor3f(0.3,0.3,1); break;
        case 2: glColor3f(0,1,0); break;
        case 3: glColor3f(1,1,0); break;
    }
    glBegin(GL_QUADS);
    glVertex2f(m_pos[0]-m_size,m_pos[1]-m_size);
    glVertex2f(m_pos[0]-m_size,m_pos[1]+m_size);
    glVertex2f(m_pos[0]+m_size,m_pos[1]+m_size);
    glVertex2f(m_pos[0]+m_size,m_pos[1]-m_size);
    glEnd();

    //draw ghosts
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float brightness=0.4;
    switch(m_id)
    {
        case 0: glColor4f(0.6,0,0,brightness); break;
        case 1: glColor4f(0,0,0.6,brightness); break;
        case 2: glColor4f(0,0.6,0,brightness); break;
        case 3: glColor4f(0.6,0.6,0,brightness); break;
    }
    glBegin(GL_QUADS);
    for(int i=0;i<(int)m_vec_ghost_pos.size();i++)
    {
        glVertex2f(m_vec_ghost_pos[i].pos[0]-m_size,m_vec_ghost_pos[i].pos[1]-m_size);
        glVertex2f(m_vec_ghost_pos[i].pos[0]-m_size,m_vec_ghost_pos[i].pos[1]+m_size);
        glVertex2f(m_vec_ghost_pos[i].pos[0]+m_size,m_vec_ghost_pos[i].pos[1]+m_size);
        glVertex2f(m_vec_ghost_pos[i].pos[0]+m_size,m_vec_ghost_pos[i].pos[1]-m_size);
    }
    glEnd();
    glDisable(GL_BLEND);

    return true;
}

bool player::get_player_pos(float pos[2])
{
    pos[0]=m_pos[0];
    pos[1]=m_pos[1];

    return true;
}

bool player::set_player_pos(float pos[2])
{
    m_pos[0]=pos[0];
    m_pos[1]=pos[1];

    return true;
}

bool player::get_speed(float speed[2])
{
    speed[0]=m_speed[0];
    speed[1]=m_speed[1];

    return true;
}

bool player::set_speed(float speed[2])
{
    m_speed[0]=speed[0];
    m_speed[1]=speed[1];

    return true;
}
