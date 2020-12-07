


// This is start of the header guard.  ADD_H can be any unique name.  By convention, we use the name of the header file.
#ifndef SETUP_SPRITES_H
#define SETUP_SPRITES_H

#include <iostream>

#include "sprite_objects.h"
#include <vector>
#include "render.h"
// The extern declaration in combination with an implementation i the cxx file makes global var
extern std::vector<sprite_objects> all_sprites;
extern std::vector<sprite_objects*> sprite_pointers;
//

void setup_sprites(render& parameter);


//~ extern unsigned char new_enemy1_body[];











// This is the end of the header guard
#endif
