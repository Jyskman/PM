
#include <iostream>
#include <vector>
#include "environment.h"
#include "render.h"
#include "setup_sprites.h"
#include <math.h>

#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;










vector<block> blocks;
vector<room_object> room_objects;
//vector<portal> portal_objects;
vector<room_portal> room_portals;

block::block(int x_pos, int y_pos, int type, int x_start, int x_stop, int y_start, int y_stop ) {
x_location = x_pos;
y_location = y_pos;

xstart = x_start;
xstop = x_stop;
ystart = y_start;
ystop = y_stop;

current_palette = 1;
block_type = type; // also called index type/index
set_index();
sprite_nr = Relation_Spritenr_type();
friction_coeff = setFriction(type);
};

block::block(int x_pos, int y_pos, int palette, int type) {

x_location = x_pos;
y_location = y_pos;
current_palette = palette;
block_type = type; // also called index type/index
sprite_nr = Relation_Spritenr_type();
friction_coeff = setFriction(type);
};

block::block(int x_pos, int y_pos, int type) {

x_location = x_pos;
y_location = y_pos;
current_palette = 1;
block_type = type; // also called index type/index
set_index();
sprite_nr = Relation_Spritenr_type();
friction_coeff = setFriction(type);
};

block::block(int x_pos, int y_pos, int type, int sprite__index, bool special) {

x_location = x_pos;
y_location = y_pos;
current_palette = 1;
block_type = type; // also called index type/index
sprite_index = sprite__index;
sprite_nr = Relation_Spritenr_type();
friction_coeff = setFriction(type);
};

// set index dependent on type, various types can have the same sprite
void block::set_index() {
destroyed = false;

    switch (block_type) {

        case(1):
            sprite_index = block_type;
            destructible = false;
        break;
        case(2):
            sprite_index = block_type;
            destructible = false;
        break;
        case(3):
            sprite_index = block_type;
            destructible = false;
        break;
        case(4):
            sprite_index = block_type;
            destructible = false;
        break;
        case(5):
                     
            sprite_index = 1;
            destructible = true;
        break;
		case(100):
            sprite_index = 5;
            destructible = false;
            xvel = 1;
            yvel = 1;
        break;



    }

};

block::~block(){};

void block::setContactpoints() {
contact_points[0][0] = 0; // x
contact_points[1][0] = 0 + 3; // y

contact_points[0][1] = all_sprites.at( sprite_nr ).getWidth();
contact_points[1][1] = 0 + 3;

contact_points[0][2] = 0;
contact_points[1][2] = all_sprites.at(sprite_nr).getHeight();

contact_points[0][3] = all_sprites.at(sprite_nr).getWidth();
contact_points[1][3] = all_sprites.at(sprite_nr).getHeight();

// deflection surface

deflection_points[0][0] = 0; // x
deflection_points[1][0] = 0; // y

deflection_points[0][1] = all_sprites.at( sprite_nr ).getWidth();
deflection_points[1][1] = 0;

deflection_points[0][2] = 0;
deflection_points[1][2] = all_sprites.at(sprite_nr).getHeight();

deflection_points[0][3] = all_sprites.at(sprite_nr).getWidth();
deflection_points[1][3] = all_sprites.at(sprite_nr).getHeight();



};


float block::setFriction(int type) {
float return_value = 0;
switch (type) {
    case 1:
        return_value = 0.8;
    break;

}


return return_value;
};

void block::destruction() {
		
		int mid_x = x_location + contact_points[0][1]/2;
		int mid_y = y_location + contact_points[1][2]/2;	
	
		if ( active == false && destroyed == false ) {
			animation_requests * anim = new animation_requests(11, mid_x, mid_y, 0, 0);
			anime_req.push_back(*anim);
			delete anim;
			anim = 0;
			
			destroyed = true;
			
		} 
		else {
		};
		
	};

void block::motion() {

	switch ( block_type ) {
		
		case(100):
			xvel_communicated = false;
			yvel_communicated = false;
			//~ cout << "xloc " << x_location << " xstart " << xstart << "xstop" << xstop << endl;
			if ( x_location < xstart ) {
				xvel = xvel * -1;
			} else {
			};
			if ( x_location > xstop ) {
				xvel = xvel * - 1;
			} else {
			};
			
			if ( y_location < ystart ) {
				yvel = yvel * -1;
			} else {
			};
			if ( y_location > ystop ) {
				yvel = yvel * - 1;
			} else {
			};
		
			x_location += xvel;
			y_location += yvel;
					
		break;
		
	};




};

void block::convey_v( champ * parameter ) {

	
	if ( xvel_communicated == false ) {
		parameter->x_location = parameter->x_location + xvel;
		xvel_communicated = true;

	} else {
	};
	
	if ( yvel_communicated == false ) {
		parameter->y_location = parameter->y_location + yvel;
		//~ cout << " y v" << yvel << endl;
		yvel_communicated = true;

	} else {
	};
	

	

	
};

void block::setRender_Block(){

	motion();
	
    if ( sprite_error == false) {
            render_requests * obj_e = new render_requests(sprite_nr, x_location, y_location, current_palette);

            render_req.push_back(*obj_e);
            delete obj_e;
            obj_e = 0;
    } else {
    };


};

// draw error will be true if no relation between index/type and vector index can be established in the forloop all_sprites
int block::Relation_Spritenr_type() {
    int return_value = 0;
    sprite_error = true;
        for (int i=0; i < all_sprites.size(); i++) {
            if ( all_sprites.at(i).sprite_index == sprite_index ) {
                return_value = i;
                sprite_error = false;
                //cout << return_value << endl;
            } else {

            };
        };

    return return_value;

};




// Room_object class below

room_object::room_object(int *arr,int *arr_pal , int row, int col, int x_up, int x_low, int y_up, int y_low, int nr) : roomblocks() {

adress = arr;
adress_pal = arr_pal;
rows = row;
cols = col;
xlim_low = x_low;
xlim_up =x_up;
ylim_low = y_low;
ylim_up = y_up;
room_nr = nr;


room_object_setup();
};

room_object::room_object(int *arr, int row, int col, int x_up, int x_low, int y_up, int y_low, int nr) : roomblocks() {

adress = arr;

rows = row;
cols = col;
xlim_low = x_low;
xlim_up =x_up;
ylim_low = y_low;
ylim_up = y_up;
room_nr = nr;


    room_object_setup();


};

void room_object::update_hitbox() {

	for ( int i = 0; i < room_items.size(); i++ ) {
			
			
			
			for ( int j = 0; j < room_items.at(i).item_hitbox.size(); j++ ) {
				room_items.at(i).item_hitbox.at(j).load_base( room_items.at(i).x_pos, room_items.at(i).y_pos );
			
			}; 
	
	};
	
	for ( int i = 0; i < room_drop_items.size(); i++ ) {
			
			
			
			for ( int j = 0; j < room_drop_items.at(i).item_hitbox.size(); j++ ) {
				room_drop_items.at(i).item_hitbox.at(j).load_base( room_drop_items.at(i).x_pos, room_drop_items.at(i).y_current );
			
			}; 
	
	};


	
};



void room_object::set_terminator() {
	
	
	for ( int i = 1; i < (columns_storage.size() / column_items); i++ ) {


        if ( columns_storage.at(16).at(i) <= -100 && columns_storage.at(16).at(i) != -666 ) {

				hitbox_object * new_box_1 = new hitbox_object( columns_storage.at(20).at(i), columns_storage.at(21).at(i), columns_storage.at(22).at(i), columns_storage.at(23).at(i)  );
				
				
				terminator_box.push_back( *new_box_1 );
				delete new_box_1;
				new_box_1 = 0;




        } else {
        }
        
        if ( columns_storage.at(16).at(i) == -666 ) {
			boss_room = true;
			cout << " once " << endl;
		
		} else {
		};

    }
    
    
    
};


void room_object::set_limits() {

	// For a static room you add 320 resp 240 to the low value of x and y eg xlim 0 -> xlim uo 320
	//~ Previously there was an original limit derived from the first line se commented below
	//~ xlim_low = columns_storage.at(0).at(0);
	//~ xlim_up = columns_storage.at(2).at(0);
	//~ ylim_low = columns_storage.at(1).at(0);
	//~ ylim_up = columns_storage.at(3).at(0);
	
	xlim_low = 0;
	xlim_up = 320;
	ylim_low = 0;
	ylim_up = 240;

	xlim_low_set = xlim_low;
	xlim_up_set = xlim_up;
	ylim_low_set = ylim_low;
	ylim_up_set = ylim_up;
	// So the low is closest to zero

    for ( int i = 1; i < (columns_storage.size() / column_items); i++ ) {


        if ( columns_storage.at(16).at(i) > 0 || columns_storage.at(17).at(i) > 0 || columns_storage.at(18).at(i) > 0 || columns_storage.at(19).at(i) > 0 ||
			columns_storage.at(20).at(i) > 0 || columns_storage.at(21).at(i) > 0 || columns_storage.at(22).at(i) > 0 || columns_storage.at(23).at(i) > 0 ) {

				room_limits * new_lim_1 = new room_limits( columns_storage.at(16).at(i), columns_storage.at(17).at(i), columns_storage.at(18).at(i), columns_storage.at(19).at(i),
														   columns_storage.at(20).at(i), columns_storage.at(21).at(i), columns_storage.at(22).at(i), columns_storage.at(23).at(i)  );
				
				
				limits.push_back( *new_lim_1 );
				delete new_lim_1;
				new_lim_1 = 0;




        } else {
        }

    }









};

void room_object::set_modifiers() {
 //~ configure for example the star field modifier	
 int type = 0;
 
	    for ( int i = 1; i < (columns_storage.size() / column_items); i++ ) {


        if ( columns_storage.at(16).at(i) < 0  ) {


				type = columns_storage.at(16).at(i) * -1 ;
				stars * new_stars_1 = new stars(  type ,
			    columns_storage.at(20).at(i), columns_storage.at(21).at(i), columns_storage.at(22).at(i), columns_storage.at(23).at(i)  );
				
				
				starfields.push_back( *new_stars_1 );
				delete new_stars_1;
				new_stars_1 = 0;




        } else {
        }

    }
	
	
};

void room_object::setup_functions() {
	room_object_setupCSV();
	create_blocks();
	set_limits();
	set_terminator();
	set_modifiers();
};


room_object::room_object( string file, int room) : roomblocks(), columns_storage() {

name = file;
room_nr = room;


//~ room_object_setupCSV();
//~ create_blocks();
//~ set_limits();
//~ set_modifiers();
//cout << " end const " << endl;

};


room_object::~room_object() {

};

void room_object::room_object_setupCSV() {
// How many col of data to create

column_items = 3; // redundant


    string file_name = name;
    string line;
    ifstream room_2;
    room_2.open(file_name);

    // counter for once only col items +1 loop, could be bool
    int counter = 0;
    while ( room_2.good() ) {

        // First time only read 4 values and ignore the -1 index in the CSV
        if ( counter == 0 ) {
        getline(room_2, line, ',');
        column_items = -1 * stoi (line.c_str()) ;
        //cout << column_items << endl;

        } else {
        }
        // end first time only, 3 values stored -1 ignored
        counter++;
        for ( int i = 0; i < column_items; i++ ) {

        // v within v creation
        vector<int> *obj = new vector<int> ;
        columns_storage.push_back( *obj );
        delete obj;
        obj = 0;

        };

        // here the rest of the CSV is cycled within the while loop 3 items at a time, the -1 is sacrificed to get the right readings. Sacrifice necessary for lack of comma at end of CSV rows
        for ( int i = 0; i < column_items; i++ ) {
        getline(room_2, line, ',');
        columns_storage.at(i).push_back( stoi (line.c_str()));
        }



    }
//    int room_type, x, y;

    //~ for ( int j = 0; j < columns_storage.at(0).size() ; j++ ) {
        //~ //cout << columns_storage.at(0).at(j) << "_" << columns_storage.at(1).at(j) << "_" << columns_storage.at(2).at(j) << endl;
        //~ for ( int i = 0; i < column_items; i++ ) {
//~ //            cout << columns_storage.at(i).at(j) << "_ ";

        //~ }
//~ //        cout << "_" << endl;


    //~ }
//~ //    cout << "____" << endl;

    room_2.close();
//    cout << " after close" << endl;

}


int room_object::random_vector_element( vector<int> &parameter  ) {
	
	int return_value = 0;
	
	int roll = rand() % 100;
	
	int test_low = 0;
	int test_high = 0;
	
	bool confirm = false;
	
	for ( int i = 0; i < parameter.size(); i++  ) {
	
		test_low = i * (100 / parameter.size() ) ;
		test_high = (i + 1) * (100 / parameter.size() ) ;
	
	
	
		if (  roll > test_low && roll < test_high   ) {
			confirm = true;
		
			return_value = i;
		
		} else {
		};
	
	
	};
	
	
	
return parameter.at( return_value );	
	
	
};




// Function will be separate for creating blocks

void room_object::create_blocks() {


    for ( int i = 1; i < (columns_storage.size() / column_items); i++ ) {


        if ( columns_storage.at(0).at(i) > 0 && columns_storage.at(0).at(i) < 100 ) {

                //~ block * obj = new block(columns_storage.at(1).at(i), columns_storage.at(2).at(i), columns_storage.at(0).at(i) ) ;
                //~ obj->setContactpoints();
                //~ roomblocks.push_back(*obj);
                //~ obj = 0;
                
                
                //~ cout << columns_storage.at(0).at(i) << endl;
                switch ( columns_storage.at(0).at(i) ) {
					
					case(1): {
						
						block * obj = new block(columns_storage.at(1).at(i), columns_storage.at(2).at(i), 1 ) ;
						//~ obj->sprite_index = normal_block_sprite_index.at(0);
						obj->sprite_index = random_vector_element( normal_block_sprite_index ) ;
						
						obj->sprite_nr = obj->Relation_Spritenr_type(); 
						obj->setContactpoints();
						roomblocks.push_back(*obj);
						obj = 0;
						
					break;
					}
					case(5): {
						
						block * obj = new block(columns_storage.at(1).at(i), columns_storage.at(2).at(i), 5 ) ;
						//~ obj->sprite_index = destructible_block_sprite_index.at(0);
						obj->sprite_index = random_vector_element( destructible_block_sprite_index ) ;
						obj->sprite_nr = obj->Relation_Spritenr_type();
						obj->setContactpoints();
						roomblocks.push_back(*obj);
						obj = 0;
						
					break;
					}
					case(10): {
						
						//~ Here there will be waypoints
						
						waypoint * obj = new waypoint(columns_storage.at(1).at(i), columns_storage.at(2).at(i)) ;

						room_waypoint.push_back(*obj);
						obj = 0;
						
					break;
					}
					
					default: {
						block * obj = new block(columns_storage.at(1).at(i), columns_storage.at(2).at(i), 1 ) ;
						obj->setContactpoints();
						roomblocks.push_back(*obj);
						obj = 0;
						
					break;
					}
					
				};
                
                
                

        } else {
        }
        // item creation 
		if ( columns_storage.at(0).at(i) > 500 ) {

                item * obj = new item(columns_storage.at(0).at(i), columns_storage.at(1).at(i), columns_storage.at(2).at(i) ) ;
                obj->setup();
                room_items.push_back(*obj);
                obj = 0;
                

        } else {
        }
        
        
        
        
        // Here special blocks like motion blocks is made
		if ( columns_storage.at(0).at(i) >= 100 && columns_storage.at(0).at(i) < 500 ) {
                block * obj_1 = new block(columns_storage.at(1).at(i), columns_storage.at(2).at(i), columns_storage.at(0).at(i) ) ;
                obj_1->setContactpoints();
                //cout << *( (adress_pal + i*cols) +ii ) << endl;
                block_temp.push_back(*obj_1);
                obj_1 = 0;


        } else {
        }



    }

	


	// Sort the temp vector
   sort(block_temp.begin(), block_temp.end(), [](const block& lhs, const block& rhs) {
      return lhs.block_type < rhs.block_type;
   });
   //~ cout << "X" << endl;
   for ( int i = 0; i < block_temp.size(); i ++ ) {
		
		//cout << block_temp.at(i).block_type << endl;
	};

	// The special creation will assume an even number, two temp blocks for one real 

	for (int i = 0; i < block_temp.size()/2; i++ ) {
		
				
        //cout << "xloc " << block_temp.at( 0 + i*2 ).x_location << " xstart " << block_temp.at(0 + i*2).x_location << "xstop" << block_temp.at(1 + i*2).x_location << endl;
		block * obj_m = new block(	block_temp.at( 0 + i*2 ).x_location , block_temp.at(0 + i*2).y_location, 100,
									block_temp.at(0 + i*2).x_location, block_temp.at(1 + i*2).x_location, block_temp.at(0 + i*2).y_location, block_temp.at(1 + i*2).y_location ) ;
		obj_m->setContactpoints();
		obj_m->sprite_index = moving_block_sprite_index.at(0);
		obj_m->sprite_nr = obj_m->Relation_Spritenr_type(); 
		roomblocks.push_back(*obj_m);
		obj_m = 0;
	
	};

};




// update the limits for the render function 

void room_object::update_limits( int xoff, int yoff, champ &parameter ) {
	int v = 10;

	int type = 1;
	switch ( type ) {
		case(0):
				//~ update the x lims. Doesnt work.. all commented text works wierd. its circular and inabsolute. 
				

		break;
		case(1):
				if ( xlim_low < xlim_low_set || xlim_low < (parameter.x_location - 200) ) {
					
					xlim_low += v;

				} else {
				};
				
				if ( xlim_low > xlim_low_set && xlim_low > (parameter.x_location - 200) ) {

					xlim_low -= v;

				} else {
				};
				if ( abs( abs(xlim_low) - abs(xlim_low_set) ) < v ) {

				} else {
				};
				//
				if ( xlim_up < xlim_up_set && xlim_up < (parameter.x_location + 200) ) {
					
					xlim_up += v;

				} else {
				};
				
				if ( xlim_up > xlim_up_set || xlim_up > (parameter.x_location + 200) ) {

					xlim_up -= v;

				} else {
				};
				if ( abs( abs(xlim_up) - abs(xlim_up_set) ) < v ) {

				} else {
				};	
				// YY //
				if ( ylim_low < ylim_low_set || ylim_low < (parameter.y_location - 150) ) {
					
					ylim_low += v;

				} else {
				};
				
				if ( ylim_low > ylim_low_set && ylim_low > (parameter.y_location - 150) ) {

					ylim_low -= v;

				} else {
				};
				
				if ( abs( abs(ylim_low) - abs(ylim_low_set) ) < v ) {

				} else {
				};
				//
				if ( ylim_up < ylim_up_set && ylim_up < (parameter.y_location + 150) ) {
					
					ylim_up += v;

				} else {
				};
				
				if ( ylim_up > ylim_up_set || ylim_up > (parameter.y_location + 150)  ) {

					ylim_up -= v;

				} else {
				};
				if ( abs( abs(ylim_up) - abs(ylim_up_set) ) < v ) {

				} else {
				};	
				// //

		break;
		
	};



};







void room_object::room_object_setup() {

    for ( int i = 0; i < rows; i++ ) {
        for ( int ii = 0; ii < cols; ii++ ) {
            if ( *( (adress + i*cols) +ii ) > 0 ) {
                //block * obj = new block(ii*15, i*15, *( (adress_pal + i*cols) +ii ), *( (adress + i*cols) +ii ));
                block * obj = new block(ii*15, i*15, *( (adress + i*cols) +ii ));
                obj->setContactpoints();
                //cout << *( (adress_pal + i*cols) +ii ) << endl;
                roomblocks.push_back(*obj);

                delete obj;
            } else {
            }
        };
    };

};

void room_object::testfunc() {
cout << roomblocks.size() << endl;
};

portal::portal( int type, int x_location, int y_location, int height, int width, int radius, int room_dest, int dest_x, int dest_y ) {

    portal_type = type;
    x_loc = x_location;
    y_loc = y_location;
    portal_height = height;
    portal_width = width;
    portal_radius = radius;

    room_destination = room_dest;
    destination_x = dest_x;
    destination_y = dest_y;

    if ( portal_type == 1 ) {
        sprite_index = 301;
    } else {
    }

    if ( portal_type == 2 ) {
        sprite_index = 301;
    } else {
    }



    portal_config();
};

void portal::portal_config() {


// Sprite relation config
    for (int i=0; i < all_sprites.size(); i++) {
        if ( all_sprites.at(i).sprite_index == sprite_index ) {
            sprite_nr = i;


        } else {

        };
    };

};

void portal::portal_render() {

//cout << "test" << endl;
            int x_off = 0;
            int y_off = 0;

    switch (portal_type) {

        case (1):
        {

            render_requests_quad( sprite_nr, x_loc, y_loc, true, true, true );

            break;
            }
        case (2):
        {
            render_requests_dual(sprite_nr, x_loc, y_loc, true, true, true);
            //render_requests_dual(sprite_nr, x_loc, y_loc-20, true, false);
        break;
        }


        default:
        break;

    };


};



void portal::transport( champ &parameter, int &game_room ) {




    switch (portal_type) {

        case (1):
            //render_primitive_line(x_loc, y_loc, x_loc, y_loc-20, 1, 401);
            p_x = (float)x_loc ;
            p_y = (float)y_loc ;
            //cout << p_x << " flaots " << p_y << endl;
            h_x = (float)parameter.x_location + (float)parameter.width/2  ;
            h_y = (float)parameter.y_location + (float)parameter.height/2  ;



            distance = sqrt( ( (p_x - h_x)*(p_x - h_x) + (p_y - h_y)*(p_y - h_y) ) );

            if (distance <= 20 ) {
                game_room = room_destination;
                parameter.x_location = destination_x;
                parameter.y_location = destination_y;
                
                // need to set this to zero to avoid crash
                parameter.grab_block_nr = 0;
                
					for ( int i = 0; i < anime_req.size(); i++ ) {
	
						anime_req.at(i).destroy = true;


					};
                
                
                
            } else {
            }

        break;

        default:
        break;

    };


};

room_portal::room_portal(int *address) {
    addr = address;
};

room_portal::room_portal( portal &parameter ) {

    portals.push_back(parameter);
};

room_portal::room_portal( int room ) {

    room_nr = room;
};

void room_portal::load_portalobject(portal &parameter) {

    portals.push_back(parameter);
};




void room_setup( game *parameter ) {

// 1 - 7 - 6 is blue index

// 5 3 8 9 is stone index

//room_object * new_room1 = new room_object( (int*)room_1,room1_rows, room1_cols, room1_xlimit_upper, room1_xlimit_lower, room1_ylimit_upper, room1_ylimit_lower,0);
room_object * new_room0 = new room_object( "room0.csv",0);
new_room0->normal_block_sprite_index.push_back(1);
new_room0->normal_block_sprite_index.push_back(17);
new_room0->moving_block_sprite_index.push_back(7);
new_room0->destructible_block_sprite_index.push_back(6);
new_room0->destructible_block_sprite_index.push_back(18);
new_room0->setup_functions();
room_objects.push_back( *new_room0 );
delete new_room0;



//room_object * new_room2 = new room_object( (int*)room_2, room2_rows, room2_cols, room2_xlimit_upper, room2_xlimit_lower, room2_ylimit_upper, room2_ylimit_lower,1);
room_object * new_room1 = new room_object( "room1.csv",1);
new_room1->normal_block_sprite_index.push_back(8);
new_room1->normal_block_sprite_index.push_back(15);
new_room1->normal_block_sprite_index.push_back(14);
new_room1->moving_block_sprite_index.push_back(9);
new_room1->destructible_block_sprite_index.push_back(5);
new_room1->setup_functions();
room_objects.push_back( *new_room1 );
delete new_room1;

//room_object * new_room3 = new room_object( (int*)room_3, room3_rows, room3_cols, room3_xlimit_upper, room3_xlimit_lower, room3_ylimit_upper, room3_ylimit_lower,2);
room_object * new_room2 = new room_object( "room2.csv",2);
new_room2->normal_block_sprite_index.push_back(10);
new_room2->normal_block_sprite_index.push_back(13);
new_room2->moving_block_sprite_index.push_back(11);
new_room2->destructible_block_sprite_index.push_back(12);
new_room2->setup_functions();
room_objects.push_back( *new_room2 );
delete new_room2;





    // make one portal container for each room
    for ( int i = 0; i < parameter->room_max; i++ ) {
    // room portal objects

        room_portal * new_1 = new room_portal(i);

        room_portals.push_back( *new_1 );

        delete new_1;
        new_1 = 0;




    }






    int room_nr;
    for (int j = 0; j < 2; j++) {
    room_nr = j;

        // attempt reading from the col storage for creation of portals
        for ( int i = 0; i < room_objects.at(room_nr).columns_storage.size()/room_objects.at(room_nr).column_items ; i++ ) {

            //index 6 is the in-room locator variable
            if ( room_objects.at(room_nr).columns_storage.at(7).at(i)  > 0 ) {

                //general room
                int in_room = room_objects.at(room_nr).columns_storage.at(6).at(i);
                int c_index = 0;
                int x_pos = room_objects.at(room_nr).columns_storage.at(8).at(i);
                int y_pos = room_objects.at(room_nr).columns_storage.at(9).at(i);
                int h = room_objects.at(room_nr).columns_storage.at(10).at(i);
                int w = room_objects.at(room_nr).columns_storage.at(11).at(i);
                int r = room_objects.at(room_nr).columns_storage.at(12).at(i);
                int dest_room = room_objects.at(room_nr).columns_storage.at(13).at(i);
                int dest_x = room_objects.at(room_nr).columns_storage.at(14).at(i);
                int dest_y = room_objects.at(room_nr).columns_storage.at(15).at(i);


                portal * portal_room1_1 = new portal(1, x_pos, y_pos, h, w, r, dest_room, dest_x, dest_y);
                //room_1_portals.load_portalobject( *portal_room1_1 );
                room_portals.at(in_room).load_portalobject(*portal_room1_1);
                delete portal_room1_1;

            }else {
            }


        }


    }














};

void room_render_req(int roomnr, champ &parameter, physics &parameter_physics) {

    // remove dest room blocks
    //~ room_objects.at(roomnr).roomblocks.erase(
    //~ remove_if(room_objects.at(roomnr).roomblocks.begin(), room_objects.at(roomnr).roomblocks.end(),
    //~ [](const block & o) { return o.destroyed == true; }),
    //~ room_objects.at(roomnr).roomblocks.end());
    
    
    
    
    
    
    
    
    //~ need to find the potentially grabbed block and reasign after potential block destruction
	for (int i = 0; i < room_objects.at(roomnr).roomblocks.size(); i++ ) {

		if ( room_objects.at(roomnr).roomblocks.at(i).grabbed == true ) {
	
			
			parameter.grab_block_nr = i;
		} else {
		};
	
	};
    
    

	for (int i = 0; i < room_objects.at(roomnr).starfields.size(); i++ ) {

		room_objects.at(roomnr).starfields.at(i).render_stars();

	};


	for (int i = 0; i < room_objects.at(roomnr).roomblocks.size(); i++ ) {

		if ( room_objects.at(roomnr).roomblocks.at(i).active == true ) {
		
				room_objects.at(roomnr).roomblocks.at(i).setRender_Block();
		
		} else {
		};
	
	

	};
	
	// items render
	for (int i = 0; i < room_objects.at(roomnr).room_items.size(); i++ ) {

		
		
		// For boss rooms all room items will render after boss room == false
		if ( room_objects.at(roomnr).boss_room == false ) {
		
			room_objects.at(roomnr).room_items.at(i).render_item();
		
		} else {
		};
		
		

	};
	
	for (int i = 0; i < room_objects.at(roomnr).room_drop_items.size(); i++ ) {

		room_objects.at(roomnr).room_drop_items.at(i).motion( parameter_physics );
		room_objects.at(roomnr).room_drop_items.at(i).render_item();

	};


};


// Attacks will be destroyed and destroy
void roomblocks_attack_interaction( int room, vector<attack> &parameter ) {

    bool hit = true;

    int X_1_A, X_2_A, Y_1_A, Y_2_A, X_1_B, X_2_B, Y_1_B, Y_2_B;

        for (int i = 0; i < room_objects.at(room).roomblocks.size(); i++) {

            for ( int j = 0; j < parameter.size() ; j++ ) {

                // blocks

                X_1_A = room_objects.at(room).roomblocks.at(i).deflection_points[0][0]+room_objects.at(room).roomblocks.at(i).x_location ;
                X_2_A = room_objects.at(room).roomblocks.at(i).deflection_points[0][1]+room_objects.at(room).roomblocks.at(i).x_location ;
                Y_1_A = room_objects.at(room).roomblocks.at(i).deflection_points[1][0]+room_objects.at(room).roomblocks.at(i).y_location ;
                Y_2_A = room_objects.at(room).roomblocks.at(i).deflection_points[1][3]+room_objects.at(room).roomblocks.at(i).y_location ;


                // Shot
                X_1_B = parameter.at(j).a_x_pos + parameter.at(j).attack_hitbox.at(0).x_u_left;
                X_2_B = parameter.at(j).a_x_pos + parameter.at(j).attack_hitbox.at(0).x_l_right;
                Y_1_B = parameter.at(j).a_y_pos + parameter.at(j).attack_hitbox.at(0).y_u_left;
                Y_2_B = parameter.at(j).a_y_pos + parameter.at(j).attack_hitbox.at(0).y_l_right;;


                //cout << " X1_l_right shot " << X_1_B << " X2 " << X_2_A << " Y1 " << Y_1_A << " Y2 " << Y_2_A << endl;
                //cout << " X1 " << X_1_B << " X2 " << X_2_B << " Y1 " << Y_1_B << " Y2 " << Y_2_B << endl;

                    hit = true;
                if (  X_1_B < X_2_A && X_2_B > X_1_A && Y_1_B < Y_2_A && Y_2_B > Y_1_A ) {
                        hit = false;


                } else {

                }

                if ( hit == false &&  room_objects.at(room).roomblocks.at(i).active == true ) {

                    parameter.at(j).destroy = true;

                        animation_requests * obj = new animation_requests(13, parameter.at(j).mid_x, parameter.at(j).mid_y , 0, 0);
                        anime_req.push_back(*obj);
                        delete obj;
                        obj = 0;


                    particle_generator(parameter.at(j).mid_x, parameter.at(j).mid_y, 403, 5, true, 10, 10);
                    particle_generator(parameter.at(j).mid_x, parameter.at(j).mid_y, 403, 5, true, 10, 10);

                    // if block destructible destroyed will become true
                    if ( room_objects.at(room).roomblocks.at(i).destructible == true ) {
                        //~ room_objects.at(room).roomblocks.at(i).destroyed = true;
                        room_objects.at(room).roomblocks.at(i).active = false;
                        room_objects.at(room).roomblocks.at(i).destruction();
                    } else {
                    }


                } else {
                }


            };




        };




};



void roomblocks_simple_deflection( int room, float x_f, float y_f, float &x_v, float &y_v ) {
// simple deflector attempt
int x = (int)x_f;
int y = (int)y_f;


    for ( int i = 0; i < room_objects.at(room).roomblocks.size(); i++ ) {

        if ( x >= room_objects.at(room).roomblocks.at(i).contact_points[0][0]+room_objects.at(room).roomblocks.at(i).x_location && x <= room_objects.at(room).roomblocks.at(i).contact_points[0][1]+room_objects.at(room).roomblocks.at(i).x_location &&
        y >= room_objects.at(room).roomblocks.at(i).contact_points[1][0]+room_objects.at(room).roomblocks.at(i).y_location && y <= room_objects.at(room).roomblocks.at(i).contact_points[1][3]+room_objects.at(room).roomblocks.at(i).y_location ) {

                y_v = -1*y_v;

                if ( x <= room_objects.at(room).roomblocks.at(i).contact_points[0][0]+room_objects.at(room).roomblocks.at(i).x_location ||
                x >= room_objects.at(room).roomblocks.at(i).contact_points[0][1]+room_objects.at(room).roomblocks.at(i).x_location ) {
                    x_v = -1*x_v;
                } else {
                };


        } else {

        };

    };

};













