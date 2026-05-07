/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package ctinfoexport;

import java.io.Serializable;

/**
 *
 * @author Roco
 */
public class CourseInfo implements Serializable{
    //Header
    private static final long serialVersionUID = 1L;
    final int magic = 0x464E4943;
    final short version = 1;
    short flags = 0;
    long padding = 0;   
    
    MapScale localMap;
    MapScale globalMap;
    MapScale exMap;
    MapBounds exMapBounds;
    
    int seqID;
    int bnkID;
    
    WeatherType weatherType;
    ExMapType exMapType;
    CannonBehavior cannonBehavior;
    int globalMapRotation;
    int partialFog;
    int partialFogV;
    
    
    enum ExMapType
    {
        EXMAP_TYPE_NONE,
        EXMAP_TYPE_EXTEND,
        EXMAP_TYPE_LAYER,
        EXMAP_TYPE_BACKGROUND,
        EXMAP_TYPE_ANIMBACKGROUND,
        EXMAP_TYPE_INVALID
    };
    
    enum WeatherType
    {
        WEATHER_TYPE_NONE,
        WEATHER_TYPE_RAIN,
        WEATHER_TYPE_SNOW,
        WEATHER_TYPE_CUSTOM //Load an SPA file from the course carc
    }
    
    enum CannonBehavior
    {
        CANNON_TYPE_NORMAL,
        CANNON_TYPE_WARP,
        CANNON_TYPE_FAST,
        CANNON_TYPE_SLOW,
        CANNON_TYPE_WARP_NO_JUMP
    }
    
}
