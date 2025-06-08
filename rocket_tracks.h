// sync data declaration
#ifdef SYNC_PLAYER
#pragma once
#include "rocket/track.h"
extern sync_track* scene;
extern sync_track* clear_i;
extern sync_track* logo_pentaBorder;
extern sync_track* logo_pentaRadius;
extern sync_track* logo_pentaScale;
extern sync_track* logo_pentaScaleStep;
extern sync_track* logo_pentaRotation;
extern sync_track* logo_pentaRotationStep;
extern sync_track* logo_pentaIntensity;
extern sync_track* logo_pentaSharpness;
extern sync_track* logo_pentaAmount;
extern sync_track* logo_nekoScale;
extern sync_track* logo_nekoY;
extern sync_track* logo_nekoColor;
extern sync_track* logo_textY;
extern sync_track* logo_textColor;
extern sync_track* logo_textSize;
extern sync_track* mist_camera_distance;
extern sync_track* mist_camera_roll;
extern sync_track* mist_cube_scale;
extern sync_track* mist_cube_colorLerp;
extern sync_track* mist_cube_light;
extern sync_track* mist_text_scale;
#endif
 // SYNC_PLAYER