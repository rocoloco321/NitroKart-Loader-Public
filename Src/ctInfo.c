#include "common.h"
#include "archive.h"
#include "race/courseModel.h"
#include "race/raceConfig.h"
#include "ctInfo.h"

static ctInfo_t* ctInfo;

extern mapScale_t LocalMapScaleTable[];
extern mapScale_t GlobalMapScaleTable[];
u8 isBridgePresent = 0;

extern void arc_setHeapGroupId(u32 id);
extern void sub_20B6B18(VecFx32 *a1, VecFx32 *a2, s16 xmin, s16 ymin, s16 xmax, s16 ymax); //Sets the local map scale
extern void sub_20B6BD4(VecFx32 *a1, VecFx32 *a2, s16 xmin, s16 ymin, s16 xmax, s16 ymax); //Sets the global map scale
extern BOOL m2d_isPointOnLowerMap(VecFx32* a);

extern crsmdl_t crsmdl_sState;

ncp_call(0x02062C04) //Load CT info inmediatly after course carc is loaded
void ctInf_init(void)
{
    arc_setHeapGroupId(5);
    ctInfo = arc_getCourseArcFile("course_info.nkldr");
    if(ctInfo)
    {
        if(ctInfo->header.magic != CINF_MAGIC)
        {
            ctInfo = NULL;
        }
    }
    
    if(rconf_getDisplayMode() == RACE_DISPLAY_MODE_DEFAULT) //Only reload music on default display mode
    {
        sub_2105FCC();
        sysdat_stopSeq();
        sub_2105EC0();
        sysdat_unloadSeq();
        sub_21074AC(0); // call the function that loads the course music again because that is done way before the course arc is loaded
    }
    arc_setHeapGroupId(9); 
    map2d_load(); // Resume normal code execution
}


ncp_call(0x020AF908)
void ctInf_finalize(void)
{
    ctInfo = NULL;
    isBridgePresent = 0;
    m2d_finalize();
}

ncp_jump(0x020B6A98)
void ctInf_getLocalMapScale(VecFx32* minCord, VecFx32* maxCord)
{
    if(ctInfo) // read map coords from ctinfo file
    {
        sub_20B6B18(minCord, maxCord, ctInfo->localMapScale.min.x, ctInfo->localMapScale.min.y,
            ctInfo->localMapScale.max.x,ctInfo->localMapScale.max.y);
    }
    else if(rconf_getCourse() <= COURSE_STAFFROLLTRUE) // if ct is not an extra track use the vanilla map scale table 
    {
        mapScale_t* mapScale = &LocalMapScaleTable[rconf_getCourse()];
        sub_20B6B18(minCord, maxCord, mapScale->min.x, mapScale->min.y,
            mapScale->max.x, mapScale->max.y);
    }
    else //default to yoshi circuit vals
    {
        mapScale_t* mapScale = &LocalMapScaleTable[COURSE_OLD_YOSHI_GC];
        sub_20B6B18(minCord, maxCord, mapScale->min.x, mapScale->min.y,
            mapScale->max.x, mapScale->max.y);
    }
}

ExtendedMapType ctInf_getExMapType(void)
{
    if(ctInfo)
    {
        return ctInfo->extendedMapType;
    }
    else
    {
        return EXMAP_TYPE_INVALID;
    }
}

ncp_jump(0x20B681C)
void ctInf_getExtendedLocalMapScale(VecFx32* minCord, VecFx32* maxCord)
{
    if(ctInfo) // read map coords from ctinfo file
    {
        if(ctInf_getExMapType() == EXMAP_TYPE_EXTEND)
        {
            sub_20B6B18(minCord, maxCord, ctInfo->localMap2Scale.min.x, ctInfo->localMap2Scale.min.y,
                ctInfo->localMap2Scale.max.x,ctInfo->localMap2Scale.max.y);
        }
        
        else
        {
            ctInf_getLocalMapScale(minCord, maxCord);
        }
        
    }
    
    else // if ct is not an extra track use the vanilla map scale table 
    {
        switch (rconf_getCourse())
        {
            case COURSE_OLD_LUIGI_GC:
                sub_20B6B18(minCord, maxCord, -3020, -10, 2980, 5990);
                break;
            case COURSE_MANSION_COURSE:
                sub_20B6B18(minCord, maxCord, -2112, -1000, 3888, 5000);
                break;
            case COURSE_CROSS_COURSE:
                sub_20B6B18(minCord, maxCord, 0, -3002, 6000, 2998);
                break;
            case COURSE_TOWN_COURSE:
                sub_20B6B18(minCord, maxCord, -190, -3790, 6310, 2710);
                break;
            case COURSE_SNOW_COURSE:
                sub_20B6B18(minCord, maxCord, -2110, -20, 3890, 5980);
                break;
            case COURSE_PINBALL_COURSE:
                sub_20B6B18(minCord, maxCord, -3005, -30, 2995, 5970);
                break;
            case COURSE_OLD_KINOKO_GC:
                sub_20B6B18(minCord, maxCord, -10, -3020, 5990, 2980);
                break;
            default:
                ctInf_getLocalMapScale(minCord, maxCord);
                break;
        }
    }
    
}

ncp_jump(0x20B64E8)
BOOL ctInf_shouldLoadExtendedMap()
{   
    if(ctInfo)
    {
        if(ctInf_getExMapType() != EXMAP_TYPE_NONE)
        {
            return TRUE;
        }
    }
    else
    {
        switch (rconf_getCourse())
        {
            case COURSE_OLD_YOSHI_GC:
            case COURSE_OLD_MOMO_64:
            case COURSE_OLD_LUIGI_GC:
            case COURSE_OLD_FRAPPE_64:
            case COURSE_CLOCK_COURSE:
            case COURSE_MANSION_COURSE:
            case COURSE_AIRSHIP_COURSE:
            case COURSE_CROSS_COURSE:
            case COURSE_OLD_HYUDORO_64:
            case COURSE_RIDGE_COURSE:
            case COURSE_MARIO_COURSE:
            case COURSE_GARDEN_COURSE:
            case COURSE_DESERT_COURSE:
            case COURSE_TOWN_COURSE:
            case COURSE_SNOW_COURSE:
            case COURSE_PINBALL_COURSE:
            case COURSE_STADIUM_COURSE:
            case COURSE_OLD_KINOKO_GC:
            case COURSE_OLD_SKY_AGB:
            case COURSE_MR_STAGE1:
            case COURSE_MR_STAGE3:
                return TRUE;
                break;
        }
    }
    return FALSE;
}

ncp_jump(0x20B6430)
BOOL ctInf_isBackgroundExtendedMap()
{
    if(ctInfo)
    {
        if(ctInf_getExMapType() == EXMAP_TYPE_BACKGROUND || ctInf_getExMapType() == EXMAP_TYPE_ANIMBACKGROUND)
        {
            return TRUE;
        }
    }
    else
    {
        switch (rconf_getCourse())
        {
            case COURSE_OLD_YOSHI_GC:
            case COURSE_OLD_MOMO_64:
            case COURSE_OLD_FRAPPE_64:
            case COURSE_OLD_HYUDORO_64:
            case COURSE_RIDGE_COURSE:
            case COURSE_MARIO_COURSE:
            case COURSE_GARDEN_COURSE:
            case COURSE_DESERT_COURSE:
            case COURSE_STADIUM_COURSE:
            case COURSE_OLD_SKY_AGB:
            case COURSE_MR_STAGE1:
            case COURSE_MR_STAGE3:
                return TRUE;
                break;
        }
    }
    return FALSE;
}

ncp_jump(0x020B4E70)
BOOL ctinf_isPointOnLowerMapHook(VecFx32* a)
{
    if(ctInfo)
    {
        
        if(ctInf_getExMapType() != EXMAP_TYPE_LAYER)
        {
            return TRUE;
        }
        if((a->x >= ctInfo->bottomMapBounds.min.x && a->x <= ctInfo->bottomMapBounds.max.x)
            && (a->z >= ctInfo->bottomMapBounds.min.z && a->z <= ctInfo->bottomMapBounds.max.z)
            && a->y < ctInfo->bottomMapBounds.max.y)
        {
            return FALSE;
        }
        return TRUE;
    }
    else
    {
        BOOL returnval = TRUE;
        switch (rconf_getCourse())
        {
            case COURSE_CLOCK_COURSE:
                if((a->x >= FX32_CONST(-887) && a->x <= FX32_CONST(887))
                    && (a->z >= FX32_CONST(-887) && a->z <= FX32_CONST(887))
                    && a->y < FX32_CONST(702.5))
                {
                    returnval = FALSE;
                }
                break;
            case COURSE_AIRSHIP_COURSE:
                if((a->x >= FX32_CONST(-1600) && a->x <= FX32_CONST(2450))
                    && (a->z >= FX32_CONST(-7400) && a->z <= FX32_CONST(-6050))
                    && a->y < FX32_CONST(738))
                {
                    returnval = FALSE;
                }
                break;
        }
        return returnval;
    }
}

ncp_repl(0x020B4E18, "B 0x020B4E2C"); //patch sub_20B4E0C to always check if the map layers should switch

ncp_jump(0x020B517C)
void refreshLocalMapHook(void)
{
    asm(R"(
	    BL      ctInf_getExMapType
        CMP     R0, #1
        BEQ     0x020B5218
        CMP     R0, #4
        BEQ     0x020B5228
        CMP     R0, #5
        BLEQ    m2d_race_getCurrentCourse
        BEQ     0x020B5180
        B       0x020B51FC
    )");
}

ncp_jump(0x020B6B54)
void ctInf_getGlobalMapScale(VecFx32* minCord, VecFx32* maxCord)
{
    if(ctInfo) // read map coords from ctinfo file
    {
        sub_20B6BD4(minCord, maxCord, ctInfo->globalMapScale.min.x, ctInfo->globalMapScale.min.y,
                    ctInfo->globalMapScale.max.x,ctInfo->globalMapScale.max.y);
    }
    else if(rconf_getCourse() <= COURSE_STAFFROLLTRUE) // if ct is not an extra track use the vanilla map scale table 
    {
        mapScale_t* mapScale = &GlobalMapScaleTable[rconf_getCourse()];
        sub_20B6BD4(minCord, maxCord, mapScale->min.x, mapScale->min.y,
            mapScale->max.x, mapScale->max.y);
    }
    else //default to yoshi circuit vals
    {
        mapScale_t* mapScale = &GlobalMapScaleTable[COURSE_OLD_YOSHI_GC];
        sub_20B6BD4(minCord, maxCord, mapScale->min.x, mapScale->min.y,
            mapScale->max.x, mapScale->max.y);
    }
}

ncp_thumb void ctInf_getMusicDestination(int courseId, music_table_entry_t *dest, int slotId) {
	const music_table_entry_t *sequenceTable = (music_table_entry_t *) 0x0215316C;
	if(ctInfo)
    {
        dest->unk1 = UNKNOWN1_FALSE;
		dest->seqId = ctInfo->seqId;
		dest->bankId = ctInfo->bankId;
		dest->unk2 = UNKNOWN2_FALSE;
    }
	else if (courseId <= COURSE_STAFFROLLTRUE)
    {
		dest->unk1 = sequenceTable[slotId].unk1;
		dest->seqId = sequenceTable[slotId].seqId;
		dest->bankId = sequenceTable[slotId].bankId;
		dest->unk2 = sequenceTable[slotId].unk2;
	}
    else
    {
		dest->unk1 = sequenceTable[9].unk1;
		dest->seqId = sequenceTable[9].seqId;
		dest->bankId = sequenceTable[9].bankId;
		dest->unk2 = sequenceTable[9].unk2;
	}
}

ncp_arm ncp_repl(0x02025748, R"(
	MOV	R2, R12
	PUSH	{R12,LR}
	BLX	ctInf_getMusicDestination
	POP	{R12,LR}
	BX	LR
)");

WeatherType ctInf_getWeatherType(void)
{
    WeatherType weatherType;
    if(ctInfo)
    {
        weatherType = ctInfo->weatherType;
    }
    else
    {
        switch (rconf_getCourse())
        {
            case COURSE_OLD_LUIGI_AGB:
                weatherType = WEATHER_TYPE_RAIN;
                break;
            case COURSE_OLD_FRAPPE_64:
                weatherType = WEATHER_TYPE_SNOW;
                break;
            default:
                weatherType = WEATHER_TYPE_NONE;
                break;
        }
    }
    return weatherType;
}

ncp_jump(0x02082B78)
void weatherHook(void)
{
    asm(R"(
	    BL ctInf_getWeatherType
        CMP R0, #1
        BEQ 0x02082B90
        CMP R0, #2
        BEQ 0x02082C74
        BNE 0x02082D1C
    )");
}


void ctInf_setIsBridgePresent(void)
{
    isBridgePresent = 1;
}

int ctInf_getBridgeProgress(void)
{
    if(isBridgePresent)
        return bridge_getProgress();
    else
        return 0;
}

ncp_repl(0x020CF5AC, "BL ctInf_getBridgeProgress");

ncp_jump(0x020E3EA8)
void bridgeInitHook(void)
{
    asm(R"(
	    BL  ctInf_setIsBridgePresent
        BL  proc_getCurrent
        B   0x020E3EAC
    )");
}

int ctInf_getCannonType(void)
{
    if(ctInfo)
    {
        return ctInfo->cannonBehavior;
    }
    return CANNON_TYPE_NORMAL;
}

ncp_jump(0x0206FFA8)
void handleCannonHook(void)
{
    asm(R"(
        push {r0}
        bl ctInf_getCannonType
        cmp r0, #1
        moveq r2, #2
        ldrne R2, [R1,#8]
        pop {r0}
        b 0x0206FFAC
    )");
}

int ctInf_getGlobalMapRotationType(void)
{
    if(ctInfo)
    {
        return ctInfo->globalMapRotation;
    }
    return MAP_ROTATION_INVALID;
}

ncp_jump(0x020B60AC)
void globalMapHook(void)
{
    asm(R"(
        BL  ctInf_getGlobalMapRotationType
        CMP R0, #0
        BEQ 0x020B60D0
        CMP R0, #1
        BEQ 0x020B61AC
        CMP R0, #2
        BEQ 0x020B60E8
        BL m2d_race_getCurrentCourse
        B 0x020B60B0
    )");
}

ncp_jump(0x0206302C)
static void setupFog()
{
    u32 i;
    u32 j;
    NNSG3dResMdl* resMdl;
    crsmdl_sState.modelHasPartialFog = FALSE;
    crsmdl_sState.modelFogFlags = 0;
    crsmdl_sState.modelVHasPartialFog = FALSE;
    crsmdl_sState.modelVFogFlags = 0;
    if(ctInfo)
    {
        crsmdl_sState.modelHasPartialFog = ctInfo->hasPartialFog;
        crsmdl_sState.modelVHasPartialFog = ctInfo->hasPartialFogV;
    }
    else
    {
        switch (rconf_getCourse())
        {
            case COURSE_MANSION_COURSE:
            case COURSE_DESERT_COURSE:
            case COURSE_MINI_STAGE2:
                crsmdl_sState.modelHasPartialFog = TRUE;
                break;
            case COURSE_RAINBOW_COURSE:
                crsmdl_sState.modelVHasPartialFog = TRUE;
                break;
        }
    }
    if (crsmdl_sState.modelHasPartialFog)
    {
        resMdl = NNS_G3dRenderObjGetResMdl(&crsmdl_sState.model->renderObj);
        for (i = 0; i < resMdl->info.numMat; i++)
        {
            //BUG: because only a 32 bit shift is used, the top 32 bits
            //     of the 64 bit field modelFogFlags are unused
            if (NNS_G3dMdlGetMdlFogEnableFlag(resMdl, i))
                crsmdl_sState.modelFogFlags |= 1 << i;
        }
    }
    else
        NNS_G3dMdlSetMdlFogEnableFlagAll(NNS_G3dRenderObjGetResMdl(&crsmdl_sState.model->renderObj), TRUE);
    if (crsmdl_sState.modelV && crsmdl_sState.modelVHasPartialFog)
    {
        resMdl = NNS_G3dRenderObjGetResMdl(&crsmdl_sState.modelV->renderObj);
        for (j = 0; j < resMdl->info.numMat; j++)
        {
            if (NNS_G3dMdlGetMdlFogEnableFlag(resMdl, j))
                crsmdl_sState.modelVFogFlags |= 1 << j;
        }
    }
}