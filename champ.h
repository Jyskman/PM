
// This is start of the header guard.  ADD_H can be any unique name.  By convention, we use the name of the header file.
#ifndef CHAMP_H
#define CHAMP_H


#include "buttons.h"
#include <iostream>
#include <vector>
#include "sprite_objects.h"
#include "physics.h"



//#include "render.h"
// This is the content of the .h file, which is where the declarations go

class game;


class champ {


public:

int hero_id = 1;

metronome runcycle;
//champ(int a, unsigned char sprites[], int size, int Height, int Width, std::vector<sprite_objects>& parameter);
champ(int a, int size, int Height, int Width);	// constructor
int Relation_Spritenr_type();
int Relation_Spritenr_type_dev( int parameter );
bool sprite_error;
bool only_once = true;
int render_req_mode = 2;
// hitbox contactpoints
int contact_points_all[2][12];
vector<hitbox_object> hero_hitbox;

int internal_state;
int current_gun;
int current_gun_index;
int current_gun_cycle = 0;




int current_legs;
int current_torso;

bool contact_left;
bool contact_right;
bool contact_roof;
bool floor_contact;
bool roof_contact;
int gun_direction;
int jump_counter;
int jump_counter_set;
int jump_v;
int nr_of_jumps_set;
int nr_of_jumps;

bool grab_left, grab_right, grab_lock;

bool current_sprite_direction = true; // true is right orientation
bool current_sprite_v_direction = true; // true is oriented up, as sprite is drawn
int rotation = 1; // exp rotation parameter

bool general_contact;
vector<int> contact_position;
vector<render_state> RSV;
vector<item*> hero_items;
vector<int> available_weapon_index;

//~ item * temp;

int x_location, y_location;
int x_location_prev, y_location_prev;
float x_location_intersection, y_location_intersection;
int x_location_intersection_int, y_location_intersection_int;


//float x_1, x_2, y_1, y_2;
float delta_x, delta_y, increment, delta_increment, cos_alfa, a_cos, length;

int height = 30;
int width = 25;

int life_bar_index = 701;
int life_bar_nr;

int life_max_index = 703;
int life_max_nr;

int weapon_frame_index = 421;
int weapon_frame_nr;

int black_index = 704;
int black_nr;

int destroy_counter = 0;
int hero_life = 10;
int hero_max_life = 5;


int hero_invincible_counter = 0;
bool hero_destroy = false;
//vector<int> x_destroy_pos;
//vector<int> y_destroy_pos;
vector<bool> destroy_animation;
vector<bool> destroy_animation_extra;
vector<float> x_destroy_pos_float;
vector<float> y_destroy_pos_float;
vector<float> x_destroy_v_float;
vector<float> y_destroy_v_float;

float x_center, y_center;
int sprite_size;

int palette_current;
int sprite_current;
int sprite_nr;
int current_form_info[10] = {101,102,0,0,0,0,0,0,25,30}; // sprite 1/sprite 2, 3, 4 plus indexes and hitbox size // probably obsolete
float x_velocity;
int y_velocity;
float y_vel;

float champ_area;


// for RSV
int x_mirror_gun, RSV_x_gun, RSV_y_gun, rot_gun, gun_sprite_nr;
bool horisontal_gun, vertical_gun;


int x_max_speed;

int getHeight();
int getWidth();

int getX();
int getY();

int getSpriteSize();

void setX(int x);
void setY(int y);

void updateV(button_input& parameter, physics& physics_parameter, int room);
void setPos(button_input& parameter, physics& physics_parameter);
int getPalette();
//int blockCompare_y(int champ_x, int champ_y, int block_x, int block_y, int block_p3x, int block_p3y, int block_p4x, int block_p4y ); // for determination of position in upp blocks left and rigt
double Det(double a, double b, double c, double d);

bool LineLineIntersect(double x1, double y1, //Line 1 start
    double x2, double y2, //Line 1 end
    double x3, double y3, //Line 2 start
    double x4, double y4, //Line 2 end
    double &ixOut, double &iyOut);

unsigned char getChar(int x);
void setRender(button_input& parameter, physics &physics_parameter, int room, bool attack_trigger);
void render_life();
int lifepos_x = 105;
int lifepos_y = 10;

void setContactPoints();
void setContact(int room);
int grab_block_nr = 0;
void check_items( int room );
void run_items( game * parameter );
void cycle_weapon( button_input& parameter );

void upgrade_animation();
bool upgrade_animation_trigger = false;
int upgrade_animation_counter = 0;

//vector<render_requests> *internal;

};


void champ_setup(champ &parameter);

// This is the end of the header guard
#endif


