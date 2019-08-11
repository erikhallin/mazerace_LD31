#include "movable_wall.h"

movable_wall::movable_wall()
{
    //ctor
}

bool movable_wall::init(int window_size[2],float wall_pos[2],float wall_size[2],float pos_b[2],float speed)
{
    m_window_width=window_size[0];
    m_window_height=window_size[1];
    m_pos[0]=wall_pos[0];
    m_pos[1]=wall_pos[1];
    m_size[0]=wall_size[0];
    m_size[1]=wall_size[1];
    m_pos_a[0]=m_pos[0];
    m_pos_a[1]=m_pos[1];
    m_pos_b[0]=pos_b[0];
    m_pos_b[1]=pos_b[1];
    m_speed=speed;
    m_time_left=m_speed;
    m_move_dir_reverse=false;

    return true;
}

bool movable_wall::update(void)
{
    //update pos
    float dir[2]={ m_pos_b[0]-m_pos_a[0], m_pos_b[1]-m_pos_a[1] };

    m_pos[0]=m_pos_a[0]+dir[0]*(m_time_left/m_speed);
    m_pos[1]=m_pos_a[1]+dir[1]*(m_time_left/m_speed);

    if(m_move_dir_reverse)
    {
        m_time_left-=_game_update_step;
        if(m_time_left<=0)
        {
            m_move_dir_reverse=!m_move_dir_reverse;
            m_time_left=0;
        }
    }
    else
    {
        m_time_left+=_game_update_step;
        if(m_time_left>m_speed)
        {
            m_move_dir_reverse=!m_move_dir_reverse;
            m_time_left=m_speed;
        }
    }

    return true;
}

bool movable_wall::draw(void)
{
    glColor3f(1,1,0);
    glBegin(GL_QUADS);
    glVertex2f(m_pos[0]-m_size[0],m_pos[1]-m_size[1]);
    glVertex2f(m_pos[0]-m_size[0],m_pos[1]+m_size[1]);
    glVertex2f(m_pos[0]+m_size[0],m_pos[1]+m_size[1]);
    glVertex2f(m_pos[0]+m_size[0],m_pos[1]-m_size[1]);
    glEnd();

    return true;
}

bool movable_wall::is_pos_ok(float pos[2])
{
    if( pos[0]<m_pos[0]+m_size[0] && pos[0]>m_pos[0]-m_size[0] &&
        pos[1]<m_pos[1]+m_size[1] && pos[1]>m_pos[1]-m_size[1] )
    {
        return true;
    }

    return false;
}
