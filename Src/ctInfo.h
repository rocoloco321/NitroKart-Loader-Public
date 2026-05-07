#pragma once
#include "common.h"

typedef enum
{
    WEATHER_TYPE_NONE,
    WEATHER_TYPE_RAIN,
    WEATHER_TYPE_SNOW,
    WEATHER_TYPE_CUSTOM //Load an SPA file from the course carc
} WeatherType;

typedef enum
{
    EXMAP_TYPE_NONE,
    EXMAP_TYPE_EXTEND,
    EXMAP_TYPE_LAYER,
    EXMAP_TYPE_BACKGROUND,
    EXMAP_TYPE_ANIMBACKGROUND,
    EXMAP_TYPE_INVALID
} ExtendedMapType;

typedef enum
{
    CANNON_TYPE_NORMAL,
    CANNON_TYPE_WARP,
    CANNON_TYPE_FAST,
    CANNON_TYPE_SLOW,
    CANNON_TYPE_WARP_NO_JUMP
} CannonTypes; 

typedef enum
{
    MAP_ROTATION_NONE,
    MAP_ROTATION_TYPE_CLOCKWISE,
    MAP_ROTATION_TYPE_COUNTERCLOCKWISE,
    MAP_ROTATION_INVALID
} GlobalMapRotationType; 

typedef struct
{
    s16 x;
    s16 y;
} coord_t;


typedef struct
{
    coord_t min;
    coord_t max;
} mapScale_t;

typedef struct  
{
    VecFx32 min;
    VecFx32 max;
} exMapBounds_t; 

/*
typedef struct
{
    u16 diffuse;
    u16 ambient;
    u16 specular;
    u16 emission;
} kartcrsmat_entry_t;
*/

#define CINF_MAGIC 0x464E4943

typedef struct
{
    u32 magic;
    u16 version;
    u16 flags; // flags related to misc patches (such as the item bounds fix, etc)
    u32 padding[2]; 
} header_t;


typedef struct
{
    header_t header;
    mapScale_t localMapScale; // offset 0x0
    mapScale_t globalMapScale; //offset 0x8
    mapScale_t localMap2Scale; // offset 0x10
    exMapBounds_t bottomMapBounds;
    u8 seqId;
    u8 bankId;
    u8 weatherType;
    u8 extendedMapType;
    u8 cannonBehavior;
    u8 globalMapRotation;
    u8 hasPartialFog;
    u8 hasPartialFogV;
    //kartcrsmat_entry_t kartcrsmat; 
} ctInfo_t;

//Unknown1
#define UNKNOWN1_TRUE   2
#define UNKNOWN1_FALSE  255
//Unknown2
#define UNKNOWN2_TRUE   34
#define UNKNOWN2_FALSE  255

typedef struct {
	u8 unk1;
	u8 seqId;
	u8 bankId;
	u8 unk2;
} music_table_entry_t;