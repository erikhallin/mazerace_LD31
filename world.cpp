#include "world.h"

world::world()
{
    //ctor
}

bool world::init(int window_size[2],particle_engine* pPart_eng)
{
    m_window_width=window_size[0];
    m_window_height=window_size[1];
    m_pParticle_engine=pPart_eng;
    //draw scale depends on width of the screen
    m_draw_scale=m_window_width/960.0;
    m_time=0;

    //load level data
    if(!load_level())
    {
        cout<<"ERROR: Could not load level data\n";
        return false;
    }

    m_world_draw_start_height=(m_window_height-m_world_height*m_draw_scale)*0.5;
    //cout<<m_world_draw_start_height<<endl;

    //insert movable walls
    float pos_a[2]={360,85};
    float pos_b[2]={485,85};
    float wall_size[2]={10,1};
    float speed=1000;
    m_vec_movable_walls.push_back( movable_wall() );
    m_vec_movable_walls.back().init(window_size,pos_a,wall_size,pos_b,speed);
    pos_a[0]=469; pos_a[1]=10;
    pos_b[0]=469; pos_b[1]=94;
    wall_size[0]=1; wall_size[1]=9;
    speed=1000;
    m_vec_movable_walls.push_back( movable_wall() );
    m_vec_movable_walls.back().init(window_size,pos_a,wall_size,pos_b,speed);
    pos_a[0]=508; pos_a[1]=201;
    pos_b[0]=508; pos_b[1]=115;
    wall_size[0]=1; wall_size[1]=9;
    speed=1000;
    m_vec_movable_walls.push_back( movable_wall() );
    m_vec_movable_walls.back().init(window_size,pos_a,wall_size,pos_b,speed);
    pos_a[0]=589; pos_a[1]=126;
    pos_b[0]=497; pos_b[1]=126;
    wall_size[0]=10; wall_size[1]=1;
    speed=1000;
    m_vec_movable_walls.push_back( movable_wall() );
    m_vec_movable_walls.back().init(window_size,pos_a,wall_size,pos_b,speed);
    pos_a[0]=588; pos_a[1]=216;
    pos_b[0]=588; pos_b[1]=377;
    wall_size[0]=13; wall_size[1]=1;
    speed=4000;
    m_vec_movable_walls.push_back( movable_wall() );
    m_vec_movable_walls.back().init(window_size,pos_a,wall_size,pos_b,speed);
    pos_a[0]=588; pos_a[1]=246;
    pos_b[0]=588; pos_b[1]=406;
    wall_size[0]=13; wall_size[1]=1;
    speed=4000;
    m_vec_movable_walls.push_back( movable_wall() );
    m_vec_movable_walls.back().init(window_size,pos_a,wall_size,pos_b,speed);
    pos_a[0]=363; pos_a[1]=369;
    pos_b[0]=363; pos_b[1]=256;
    wall_size[0]=1; wall_size[1]=40;
    speed=1100;
    m_vec_movable_walls.push_back( movable_wall() );
    m_vec_movable_walls.back().init(window_size,pos_a,wall_size,pos_b,speed);
    pos_a[0]=396; pos_a[1]=369;
    pos_b[0]=396; pos_b[1]=256;
    wall_size[0]=1; wall_size[1]=40;
    speed=1200;
    m_vec_movable_walls.push_back( movable_wall() );
    m_vec_movable_walls.back().init(window_size,pos_a,wall_size,pos_b,speed);
    pos_a[0]=433; pos_a[1]=369;
    pos_b[0]=433; pos_b[1]=256;
    wall_size[0]=1; wall_size[1]=40;
    speed=1300;
    m_vec_movable_walls.push_back( movable_wall() );
    m_vec_movable_walls.back().init(window_size,pos_a,wall_size,pos_b,speed);
    pos_a[0]=471; pos_a[1]=369;
    pos_b[0]=471; pos_b[1]=256;
    wall_size[0]=1; wall_size[1]=40;
    speed=1400;
    m_vec_movable_walls.push_back( movable_wall() );
    m_vec_movable_walls.back().init(window_size,pos_a,wall_size,pos_b,speed);
    pos_a[0]=504; pos_a[1]=369;
    pos_b[0]=504; pos_b[1]=256;
    wall_size[0]=1; wall_size[1]=40;
    speed=1500;
    m_vec_movable_walls.push_back( movable_wall() );
    m_vec_movable_walls.back().init(window_size,pos_a,wall_size,pos_b,speed);
    pos_a[0]=537; pos_a[1]=369;
    pos_b[0]=537; pos_b[1]=256;
    wall_size[0]=1; wall_size[1]=40;
    speed=1600;
    m_vec_movable_walls.push_back( movable_wall() );
    m_vec_movable_walls.back().init(window_size,pos_a,wall_size,pos_b,speed);
    pos_a[0]=632; pos_a[1]=499;
    pos_b[0]=632; pos_b[1]=450;
    wall_size[0]=10; wall_size[1]=1;
    speed=1600;
    m_vec_movable_walls.push_back( movable_wall() );
    m_vec_movable_walls.back().init(window_size,pos_a,wall_size,pos_b,speed);
    pos_a[0]=676; pos_a[1]=499;
    pos_b[0]=676; pos_b[1]=450;
    wall_size[0]=10; wall_size[1]=1;
    speed=1500;
    m_vec_movable_walls.push_back( movable_wall() );
    m_vec_movable_walls.back().init(window_size,pos_a,wall_size,pos_b,speed);
    pos_a[0]=722; pos_a[1]=499;
    pos_b[0]=722; pos_b[1]=450;
    wall_size[0]=10; wall_size[1]=1;
    speed=1400;
    m_vec_movable_walls.push_back( movable_wall() );
    m_vec_movable_walls.back().init(window_size,pos_a,wall_size,pos_b,speed);
    pos_a[0]=767; pos_a[1]=499;
    pos_b[0]=767; pos_b[1]=450;
    wall_size[0]=10; wall_size[1]=1;
    speed=1300;
    m_vec_movable_walls.push_back( movable_wall() );
    m_vec_movable_walls.back().init(window_size,pos_a,wall_size,pos_b,speed);
    pos_a[0]=812; pos_a[1]=499;
    pos_b[0]=812; pos_b[1]=450;
    wall_size[0]=10; wall_size[1]=1;
    speed=1200;
    m_vec_movable_walls.push_back( movable_wall() );
    m_vec_movable_walls.back().init(window_size,pos_a,wall_size,pos_b,speed);
    pos_a[0]=857; pos_a[1]=499;
    pos_b[0]=857; pos_b[1]=450;
    wall_size[0]=10; wall_size[1]=1;
    speed=1100;
    m_vec_movable_walls.push_back( movable_wall() );
    m_vec_movable_walls.back().init(window_size,pos_a,wall_size,pos_b,speed);

    return true;
}

bool world::update(void)
{
    m_time+=_game_update_step*0.001;
    while(m_time>360.0) m_time-=360.0;

    //portal particles
    if(rand()%10==0)
    {
        float pos1[2]={m_teleport_in_pos[0][0],m_teleport_in_pos[0][1]};
        float pos2[2]={m_teleport_in_pos[1][0],m_teleport_in_pos[1][1]};
        float pos3[2]={m_teleport_out_pos[0][0],m_teleport_out_pos[0][1]};
        float pos4[2]={m_teleport_out_pos[1][0],m_teleport_out_pos[1][1]};
        float pos5[2]={m_goal_pos[0],m_goal_pos[1]};
        float color1[3]={0.8,0.8,1};
        float color2[3]={0.4,0.4,0.8};
        float color3[3]={0.8,0.4,0.8};
        m_pParticle_engine->add_explosion(pos1,1,0.02,1000,color1);
        m_pParticle_engine->add_explosion(pos2,1,0.02,1000,color1);
        m_pParticle_engine->add_explosion(pos3,1,0.02,1000,color2);
        m_pParticle_engine->add_explosion(pos4,1,0.02,1000,color2);
        m_pParticle_engine->add_explosion(pos5,1,0.03,1000,color3);
    }


    //update movable objects
    for(int i=0;i<(int)m_vec_movable_walls.size();i++)
    {
        m_vec_movable_walls[i].update();
    }

    //update particle engine
    m_pParticle_engine->update();

    return true;
}

bool world::draw(void)
{
    /*//debug draw, pixel by pixel
    //walls
    glColor3f(1,0,0);
    glBegin(GL_POINTS);
    for(int x=0;x<m_world_width;x++)
    for(int y=0;y<m_world_height;y++)
    {
        if(m_pWorld_array[x*m_world_height+y]==1)
         glVertex2f(x,m_world_height-y);
    }
    glEnd();*/

    for(int i=0;i<(int)m_vec_movable_walls.size();i++)
    {
        m_vec_movable_walls[i].draw();
    }

    //draw goal
    {
        /*//square
        float goal_width=5;
        glColor3f(1,0.5,1);
        glBegin(GL_QUADS);
        glVertex2f(m_goal_pos[0]-goal_width,m_goal_pos[1]-goal_width);
        glVertex2f(m_goal_pos[0]-goal_width,m_goal_pos[1]+goal_width);
        glVertex2f(m_goal_pos[0]+goal_width,m_goal_pos[1]+goal_width);
        glVertex2f(m_goal_pos[0]+goal_width,m_goal_pos[1]-goal_width);
        glEnd();*/

        float goal_width=5+1.0*sinf(m_time*100.0*_Deg2Rad);

        //circle outer
        glColor3f(0.9,0.7,0.9);
        glBegin(GL_TRIANGLE_FAN);
        for(int ii = 0; ii < 10; ii++)
        {
            float theta = 2.0f * _pi * float(ii) / float(10);//get the current angle

            float x = goal_width * cosf(theta);//calculate the x component
            float y = goal_width * sinf(theta);//calculate the y component

            glVertex2f(x + m_goal_pos[0], y + m_goal_pos[1]);//output vertex

        }
        glEnd();

        //circle inner
        glColor3f(0.8,0.5,0.8);
        glBegin(GL_TRIANGLE_FAN);
        for(int ii = 0; ii < 10; ii++)
        {
            float theta = 2.0f * _pi * float(ii) / float(10);//get the current angle

            float x = goal_width*0.8 * cosf(theta);//calculate the x component
            float y = goal_width*0.8 * sinf(theta);//calculate the y component

            glVertex2f(x + m_goal_pos[0], y + m_goal_pos[1]);//output vertex

        }
        glEnd();

        //circle inin
        glColor3f(0.6,0.3,0.6);
        glBegin(GL_TRIANGLE_FAN);
        for(int ii = 0; ii < 10; ii++)
        {
            float theta = 2.0f * _pi * float(ii) / float(10);//get the current angle

            float x = goal_width*0.5 * cosf(theta);//calculate the x component
            float y = goal_width*0.5 * sinf(theta);//calculate the y component

            glVertex2f(x + m_goal_pos[0], y + m_goal_pos[1]);//output vertex

        }
        glEnd();
    }

    //draw teleport in
    float teleport_in_width=3+0.5*sinf(m_time*200.0*_Deg2Rad);
    for(int i=0;i<2;i++)
    {
        /*//square
        glBegin(GL_QUADS);
        glVertex2f(m_teleport_in_pos[i][0]-teleport_in_width,m_teleport_in_pos[i][1]-teleport_in_width);
        glVertex2f(m_teleport_in_pos[i][0]-teleport_in_width,m_teleport_in_pos[i][1]+teleport_in_width);
        glVertex2f(m_teleport_in_pos[i][0]+teleport_in_width,m_teleport_in_pos[i][1]+teleport_in_width);
        glVertex2f(m_teleport_in_pos[i][0]+teleport_in_width,m_teleport_in_pos[i][1]-teleport_in_width);
        glEnd();*/

        //circle outer
        glColor3f(0.5,0.5,0.8);
        glBegin(GL_TRIANGLE_FAN);
        for(int ii = 0; ii < 10; ii++)
        {
            float theta = 2.0f * _pi * float(ii) / float(10);//get the current angle

            float x = teleport_in_width * cosf(theta);//calculate the x component
            float y = teleport_in_width * sinf(theta);//calculate the y component

            glVertex2f(x + m_teleport_in_pos[i][0], y + m_teleport_in_pos[i][1]);//output vertex

        }
        glEnd();

        //circle inner
        glColor3f(0.6,0.6,0.9);
        glBegin(GL_TRIANGLE_FAN);
        for(int ii = 0; ii < 10; ii++)
        {
            float theta = 2.0f * _pi * float(ii) / float(10);//get the current angle

            float x = teleport_in_width*0.7 * cosf(theta);//calculate the x component
            float y = teleport_in_width*0.7 * sinf(theta);//calculate the y component

            glVertex2f(x + m_teleport_in_pos[i][0], y + m_teleport_in_pos[i][1]);//output vertex

        }
        glEnd();

        //circle inin
        glColor3f(0.7,0.7,1.0);
        glBegin(GL_TRIANGLE_FAN);
        for(int ii = 0; ii < 10; ii++)
        {
            float theta = 2.0f * _pi * float(ii) / float(10);//get the current angle

            float x = teleport_in_width*0.5 * cosf(theta);//calculate the x component
            float y = teleport_in_width*0.5 * sinf(theta);//calculate the y component

            glVertex2f(x + m_teleport_in_pos[i][0], y + m_teleport_in_pos[i][1]);//output vertex

        }
        glEnd();
    }

    //draw teleport out
    float teleport_out_width=3+0.5*sinf((m_time*200.0+180.0)*_Deg2Rad);;
    for(int i=0;i<2;i++)
    {
        /*//square
        glBegin(GL_QUADS);
        glVertex2f(m_teleport_out_pos[i][0]-teleport_out_width,m_teleport_out_pos[i][1]-teleport_out_width);
        glVertex2f(m_teleport_out_pos[i][0]-teleport_out_width,m_teleport_out_pos[i][1]+teleport_out_width);
        glVertex2f(m_teleport_out_pos[i][0]+teleport_out_width,m_teleport_out_pos[i][1]+teleport_out_width);
        glVertex2f(m_teleport_out_pos[i][0]+teleport_out_width,m_teleport_out_pos[i][1]-teleport_out_width);
        glEnd();*/

        //circle outer
        glColor3f(0.4,0.4,0.7);
        glBegin(GL_TRIANGLE_FAN);
        for(int ii = 0; ii < 10; ii++)
        {
            float theta = 2.0f * _pi * float(ii) / float(10);//get the current angle

            float x = teleport_out_width * cosf(theta);//calculate the x component
            float y = teleport_out_width * sinf(theta);//calculate the y component

            glVertex2f(x + m_teleport_out_pos[i][0], y + m_teleport_out_pos[i][1]);//output vertex

        }
        glEnd();

        //circle inner
        glColor3f(0.3,0.3,0.5);
        glBegin(GL_TRIANGLE_FAN);
        for(int ii = 0; ii < 10; ii++)
        {
            float theta = 2.0f * _pi * float(ii) / float(10);//get the current angle

            float x = teleport_out_width*0.7 * cosf(theta);//calculate the x component
            float y = teleport_out_width*0.7 * sinf(theta);//calculate the y component

            glVertex2f(x + m_teleport_out_pos[i][0], y + m_teleport_out_pos[i][1]);//output vertex

        }
        glEnd();

        //circle inin
        glColor3f(0.2,0.2,0.3);
        glBegin(GL_TRIANGLE_FAN);
        for(int ii = 0; ii < 10; ii++)
        {
            float theta = 2.0f * _pi * float(ii) / float(10);//get the current angle

            float x = teleport_out_width*0.5 * cosf(theta);//calculate the x component
            float y = teleport_out_width*0.5 * sinf(theta);//calculate the y component

            glVertex2f(x + m_teleport_out_pos[i][0], y + m_teleport_out_pos[i][1]);//output vertex

        }
        glEnd();
    }

    //draw particles
    m_pParticle_engine->draw();

    return true;
}

int world::is_pos_ok(float old_pos[2],float new_pos[2])
{
    int final_pos[2]={ int(new_pos[0]+0.5), int(new_pos[1]+0.5) };

    //test if within world limit
    if(final_pos[0]<0) return 1;
    if(final_pos[1]<0) return 1;
    if(final_pos[0]>=m_world_width) return 1;
    if(final_pos[1]>=m_world_height) return 1;

    //test curr pos
    if( m_pWorld_array[final_pos[0]*m_world_height+m_world_height-final_pos[1]] != 0 )
    {
        return m_pWorld_array[ final_pos[0]*m_world_height+m_world_height-final_pos[1] ];
    }

    //test path from old pos to new
    float dir[2]={ new_pos[0]-old_pos[0], new_pos[1]-old_pos[1] };
    int steps_taken=(int)fabs(dir[0]);
    if( fabs(dir[1]) > fabs(dir[0]) ) steps_taken=(int)fabs(dir[1]);
    if(steps_taken<1) return 0;//no change
    //cout<<steps_taken<<endl;

    for(int step_i=0;step_i<steps_taken;step_i++)
    {
        float temp_pos[2]={ old_pos[0]+dir[0]*(float)step_i,
                            old_pos[1]+dir[1]*(float)step_i };
        int test_pos[2]={ int(temp_pos[0]+0.5), int(temp_pos[1]+0.5) };
        //cout<<"test: "<<temp_pos[0]<<", "<<temp_pos[1]<<endl;

        if( m_pWorld_array[test_pos[0]*m_world_height+m_world_height-test_pos[1]] != 0 )
        {
            return m_pWorld_array[ test_pos[0]*m_world_height+m_world_height-test_pos[1] ];
        }
    }

    //test for movable walls
    for(int i=0;i<(int)m_vec_movable_walls.size();i++)
    {
        if( m_vec_movable_walls[i].is_pos_ok(new_pos) )
        {
            return 2;
        }
    }

    return 0;//pos ok
}

bool world::get_player_start_pos(int player_id,int pos[2])
{
    if(player_id<0 || player_id>3) return false;

    pos[0]=m_player_start_pos[player_id][0];
    pos[1]=m_player_start_pos[player_id][1];

    return true;
}

float world::get_world_scale(void)
{
    return m_draw_scale;
}

int world::get_world_draw_height_pos(void)
{
    return m_world_draw_start_height;
}

bool world::get_goal_pos(float goal_pos[2])
{
    goal_pos[0]=m_goal_pos[0];
    goal_pos[1]=m_goal_pos[1];

    return true;
}



//PRIVATE

bool world::load_level(void)
{
    //load bmp file to get world coordinates

    //read bmp
    FILE *fp = fopen("texture\\level.bmp", "r");
    if(!fp)
    {
        cout<<"ERROR: Could not find level.bmp\n";
        return 1;
    }
    unsigned short uint;
    unsigned int dword;
    unsigned short word;
    long llong;
    //read some data we don't need
    fread(&uint, sizeof(uint), 1, fp);
    fread(&dword, sizeof(dword), 1, fp);
    fread(&uint, sizeof(uint), 1, fp);
    fread(&uint, sizeof(uint), 1, fp);
    fread(&dword, sizeof(dword), 1, fp);
    fread(&dword, sizeof(dword), 1, fp);
    long width, height;
    fread(&width, sizeof(long), 1, fp);
    fread(&height, sizeof(long), 1, fp);
    fread(&word, sizeof(word), 1, fp);
    cout<<"Size of bitmap: "<<width<<", "<<height<<endl;

    //world size is the size of level bmp
    m_world_width=width;
    m_world_height=height;
    //reserve memory
    m_pWorld_array=new int[m_world_width*m_world_height];
    //reset map to void
    for(int x=0;x<m_world_width;x++)
    for(int y=0;y<m_world_height;y++)
     m_pWorld_array[x*m_world_height+y]=0;

    if(width%4!=0 || height%4!=0)
    {
        cout<<"ERROR: Width and Height of the bitmap have to be devisible by 4\n";
        return 1;
    }
    unsigned short bitcount;
    fread(&bitcount, sizeof(unsigned short), 1, fp);
    if(bitcount != 24)
    {
        cout << "ERROR: Bitmap is not an 24bit image\n";
        return 1;
    }
    unsigned long compression;
    fread(&compression, sizeof(unsigned long), 1, fp);
    if(compression != 0)
    {
        cout << "ERROR: Invalid compression. Make sure the BMP is not using RLE\n";
        return 1;
    }
    fread(&dword, sizeof(dword), 1, fp);
    fread(&llong, sizeof(long), 1, fp);
    fread(&llong, sizeof(long), 1, fp);
    fread(&dword, sizeof(dword), 1, fp);
    fread(&dword, sizeof(dword), 1, fp);
    unsigned char *imagedata;
    imagedata = new unsigned char[width * height * 4];

    //go through pixels
    int curr_player_pos=0;
    int curr_teleport_in_pos=0;
    int curr_teleport_out_pos=0;
    for(int y=0; y < height; y++)
    {
        for(int x=0; x < width; x++)
        {
            fread(&imagedata[(x * height + y)*4+0], sizeof(char), 1, fp);
            fread(&imagedata[(x * height + y)*4+1], sizeof(char), 1, fp);
            fread(&imagedata[(x * height + y)*4+2], sizeof(char), 1, fp);

            //BGR to RGB format
            int r = imagedata[(x * height + y)*4+2];
            int g = imagedata[(x * height + y)*4+1];
            int b = imagedata[(x * height + y)*4+0];
            imagedata[(x * height + y)*4+0] = r;
            //imagedata[(x * height + y)*4+1] = g;
            imagedata[(x * height + y)*4+2] = b;

            /*//hot pink for alpha channel
            if(imagedata[(x * height + y)*4+0] == 255 &&
               imagedata[(x * height + y)*4+1] == 0   &&
               imagedata[(x * height + y)*4+2] == 255)
             imagedata[(x * height + y)*4+3] = 0;
            else
             imagedata[(x * height + y)*4+3] = 255;*/

            //cout<<r<<", "<<g<<", "<<b<<endl;
            //mark if have color
            //WHITE
            if(r>250 && g>250 && b>250)
            {
                //height inverted due to read order (higher value = further down in pic)
                //vec_coords.push_back( st_coord(x,height-y-1) );
                //cout<<x<<", "<<height-y-1<<endl;
                m_player_start_pos[curr_player_pos][0]=x;
                m_player_start_pos[curr_player_pos][1]=height-y;
                curr_player_pos++;
                if(curr_player_pos>3) curr_player_pos=3;//max 4 players
            }
            //BLUE
            if(r<10 && g<10 && b>250)
            {
                //height inverted due to read order (higher value = further down in pic)
                //vec_object_pos.push_back( st_coord(x,height-y-1,1) );
                m_teleport_in_pos[curr_teleport_in_pos][0]=x;
                m_teleport_in_pos[curr_teleport_in_pos][1]=height-y;
                curr_teleport_in_pos++;
                if(curr_teleport_in_pos>1) curr_teleport_in_pos=1;//max 2 teleports
            }
            //RED
            if(r>250 && g<10 && b<10)
            {
                //height inverted due to read order (higher value = further down in pic)
                //vec_enemy_pos.push_back( st_coord(x,height-y-1,1) );
                m_pWorld_array[x*m_world_height+y]=1;
            }
            //ORANGE
            if(r>250 && g<130 && g>110 && b<10)
            {
                //height inverted due to read order (higher value = further down in pic)
                //vec_enemy_pos.push_back( st_coord(x,height-y-1,2) );
            }
            //GREEN
            if(r<10 && g>250 && b<10)
            {
                //will be replaced if several green dots
                //player_start_pos[0]=x;
                //player_start_pos[1]=height-y;
                m_goal_pos[0]=x;
                m_goal_pos[1]=height-y;
            }
            //YELLOW
            if(r>250 && g>250 && b<10)
            {
                m_teleport_out_pos[curr_teleport_out_pos][0]=x;
                m_teleport_out_pos[curr_teleport_out_pos][1]=height-y;
                curr_teleport_out_pos++;
                if(curr_teleport_out_pos>1) curr_teleport_out_pos=1;//max 2 teleports
            }
        }
        //read end of row, nonsense data (did not work yet, have to use height and width devisable by 4 instead)
        /*for(int i=width; i%4!=0 ;i++)
        {
            char dump;
            fread(&dump, sizeof(char), 1, fp);
            fread(&dump, sizeof(char), 1, fp);
            fread(&dump, sizeof(char), 1, fp);
        }*/
    }
    delete[] imagedata;
    fclose(fp);

    return true;
}

bool world::unload_world(void)
{
    delete[] m_pWorld_array;

    return true;
}

bool world::get_teleport_in1_pos(float pos[2])
{
    pos[0]=m_teleport_in_pos[0][0];
    pos[1]=m_teleport_in_pos[0][1];

    return true;
}

bool world::get_teleport_out1_pos(float pos[2])
{
    pos[0]=m_teleport_out_pos[0][0];
    pos[1]=m_teleport_out_pos[0][1];

    return true;
}

bool world::get_teleport_in2_pos(float pos[2])
{
    pos[0]=m_teleport_in_pos[1][0];
    pos[1]=m_teleport_in_pos[1][1];

    return true;
}

bool world::get_teleport_out2_pos(float pos[2])
{
    pos[0]=m_teleport_out_pos[1][0];
    pos[1]=m_teleport_out_pos[1][1];

    return true;
}



