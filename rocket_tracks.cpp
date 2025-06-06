// sync data implementation
#include "rocket/track.h"
static track_key cube_scale_keys[] = {{ 0, 0.001000, KEY_LINEAR}, { 56, 1.000000, KEY_RAMP}, { 58, 2.000000, KEY_STEP}, { 60, 1.000000, KEY_RAMP}, { 62, 2.000000, KEY_RAMP}, { 87, 10.000000, KEY_STEP}, };
sync_track cube_scale_a = { "cube_scale", cube_scale_keys,6};
static track_key camera_distance_keys[] = {{ 0, 24.000000, KEY_LINEAR}, };
sync_track camera_distance_a = { "camera:distance", camera_distance_keys,1};

sync_track* cube_scale = &cube_scale_a;
sync_track* camera_distance = &camera_distance_a;
