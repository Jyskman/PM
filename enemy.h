#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <iostream>
#include "physics.h"
#include "champ.h"



class enemy {



public:
enemy(int e_type, int start_x, int start_y);

int _id = 100;

bool triggered = false;

int x_location, y_location, x_v_int, y_v_int, x_location_prev, y_location_prev;
float x_float = 0;

float x_v_float = 0;
float y_v_float = 0;
float y_float = 0;

void perception(champ &parameter);
void motion( physics &parameter );
float main_v;

int shot_x_vel_factor = 1;
int shot_y_vel_factor = 1;


float perception_distance;
bool perception_above;
bool perception_right;

float perception_angle = 0.00;
float motion_angle = 0.00;
int grid_distance = 15;


int center_x, center_y;
int enemy_type;
bool destroy = false;

float champ_direction;

// Render stuff
vector<render_state> RSV;
vector<hitbox_object> enemy_hitbox_set;

vector<int> previous_x;
vector<int> previous_y;

void set_hitbox_set();
void setRender();
void test();
int render_req_mode = 2;
int internal_state = 1;

bool contact_left = false;
bool contact_right = false;
bool contact_roof = false;
bool floor_contact = false;
bool roof_contact = false;
int gun_direction = 3;
int jump_counter = 1;

int destroy_v_x, destroy_v_y;

bool sprite_error = false;
bool can_take_damage;
int life;

bool current_sprite_direction = true; // true is right orientation
bool current_sprite_v_direction = true; // true is oriented up, as sprite is drawn
int rotation = 1; // exp rotation parameter
int height = 0;
int width = 0;
bool general_contact;
int x_mirror_gun, RSV_x_gun, RSV_y_gun, rot_gun, gun_sprite_nr;
bool horisontal_gun, vertical_gun;
int palette_current = 1;

int RSV_x_end, RSV_y_end;

void RSV_setup();
void vulnerability_setup();



int enemy_offset[2][10];

void resolve_damage( vector<attack> &parameter, champ &hero_parameter );

void item_drop(int room);

void create_Enemy_attacks( game * parameter );


};


void create_and_reset_enemies( int room_nr, vector<enemy>& parameter );

void set_RSV_hitbox_relation( vector<enemy>& parameter );







#endif // EN
