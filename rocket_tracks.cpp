// sync data implementation
#ifdef SYNC_PLAYER
#include "rocket/track.h"
static track_key scene_keys[] = {};
static sync_track scene_array = { "scene", scene_keys,0};
sync_track* scene = &scene_array;
static track_key cube_scale_keys[] = {{ 0, 0.001000, KEY_LINEAR}, { 56, 1.000000, KEY_RAMP}, { 58, 2.000000, KEY_STEP}, { 60, 1.000000, KEY_RAMP}, { 62, 2.000000, KEY_RAMP}, { 87, 10.000000, KEY_STEP}, };
static sync_track cube_scale_array = { "cube_scale", cube_scale_keys,6};
sync_track* cube_scale = &cube_scale_array;
static track_key camera_distance_keys[] = {{ 0, 24.000000, KEY_LINEAR}, };
static sync_track camera_distance_array = { "camera:distance", camera_distance_keys,1};
sync_track* camera_distance = &camera_distance_array;
static track_key clear_i_keys[] = {{ 0, 0.600000, KEY_STEP}, };
static sync_track clear_i_array = { "clear_i", clear_i_keys,1};
sync_track* clear_i = &clear_i_array;
static track_key logo_pentaBorder_keys[] = {{ 0, 0.200000, KEY_STEP}, };
static sync_track logo_pentaBorder_array = { "logo:pentaBorder", logo_pentaBorder_keys,1};
sync_track* logo_pentaBorder = &logo_pentaBorder_array;
static track_key logo_pentaRadius_keys[] = {{ 0, 1.500001, KEY_STEP}, };
static sync_track logo_pentaRadius_array = { "logo:pentaRadius", logo_pentaRadius_keys,1};
sync_track* logo_pentaRadius = &logo_pentaRadius_array;
static track_key logo_pentaScale_keys[] = {{ 0, 11.199997, KEY_STEP}, };
static sync_track logo_pentaScale_array = { "logo:pentaScale", logo_pentaScale_keys,1};
sync_track* logo_pentaScale = &logo_pentaScale_array;
static track_key logo_pentaScaleStep_keys[] = {{ 0, 1.000000, KEY_STEP}, };
static sync_track logo_pentaScaleStep_array = { "logo:pentaScaleStep", logo_pentaScaleStep_keys,1};
sync_track* logo_pentaScaleStep = &logo_pentaScaleStep_array;
static track_key logo_pentaRotation_keys[] = {{ 0, 0.000000, KEY_STEP}, };
static sync_track logo_pentaRotation_array = { "logo:pentaRotation", logo_pentaRotation_keys,1};
sync_track* logo_pentaRotation = &logo_pentaRotation_array;
static track_key logo_pentaRotationStep_keys[] = {{ 0, 10.000000, KEY_STEP}, };
static sync_track logo_pentaRotationStep_array = { "logo:pentaRotationStep", logo_pentaRotationStep_keys,1};
sync_track* logo_pentaRotationStep = &logo_pentaRotationStep_array;
static track_key logo_pentaIntensity_keys[] = {{ 0, 1.000000, KEY_STEP}, };
static sync_track logo_pentaIntensity_array = { "logo:pentaIntensity", logo_pentaIntensity_keys,1};
sync_track* logo_pentaIntensity = &logo_pentaIntensity_array;
static track_key logo_pentaSharpness_keys[] = {{ 0, 0.500000, KEY_STEP}, };
static sync_track logo_pentaSharpness_array = { "logo:pentaSharpness", logo_pentaSharpness_keys,1};
sync_track* logo_pentaSharpness = &logo_pentaSharpness_array;
static track_key logo_pentaAmount_keys[] = {{ 0, 5.000000, KEY_STEP}, };
static sync_track logo_pentaAmount_array = { "logo:pentaAmount", logo_pentaAmount_keys,1};
sync_track* logo_pentaAmount = &logo_pentaAmount_array;
static track_key logo_nekoScale_keys[] = {{ 0, 10.200000, KEY_STEP}, };
static sync_track logo_nekoScale_array = { "logo:nekoScale", logo_nekoScale_keys,1};
sync_track* logo_nekoScale = &logo_nekoScale_array;
static track_key logo_nekoY_keys[] = {{ 0, 199.000000, KEY_STEP}, };
static sync_track logo_nekoY_array = { "logo:nekoY", logo_nekoY_keys,1};
sync_track* logo_nekoY = &logo_nekoY_array;
static track_key logo_nekoColor_keys[] = {};
static sync_track logo_nekoColor_array = { "logo:nekoColor", logo_nekoColor_keys,0};
sync_track* logo_nekoColor = &logo_nekoColor_array;
#endif
 // SYNC_PLAYER