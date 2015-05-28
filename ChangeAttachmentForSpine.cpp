#include "ExtendsToLua.h"
#include "spine/spine-cocos2dx.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"

#include <spine/extension.h>
#include <spine/PolygonBatch.h>
#include <algorithm>



//kokokele
int lua_cocos2dx_spine_SkeletonRenderer_changeSkin(lua_State* tolua_S)
{
    int argc = 0;
    spine::SkeletonRenderer* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
//#if COCOS2D_DEBUG >= 1
//    if (!tolua_isusertype(tolua_S,1,"sp.SkeletonRenderer",0,&tolua_err)) goto tolua_lerror;
//#endif
    
    cobj = (spine::SkeletonRenderer*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_spine_SkeletonRenderer_changeSkin", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        std::string arg0;
        
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sp.SkeletonRenderer:changeSkin");
        if(!ok) return 0;
        
        
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_spine_SkeletonRenderer_changeSkin'", nullptr);
            return 0;
        }
        
        //-------------------------------
        spAtlas* atlas = spAtlas_createFromFile(arg0.c_str(), 0);
        spAtlasAttachmentLoader* attachmentLoader = spAtlasAttachmentLoader_create(atlas);
        
        spAtlasRegion* region, *nextRegion;
        region= atlas->regions;
        while (region) {
            nextRegion = region->next;
            //CCLOG("%s", region->name);
            
            
            std::string name = region->name;
            
            spRegionAttachment* regionOld = SUB_CAST(spRegionAttachment, cobj->getAttachment(name.c_str(),name.c_str()));
            
            
            spAttachment* attachment = spAttachmentLoader_newAttachment(SUPER(attachmentLoader), 0, SP_ATTACHMENT_REGION, name.c_str(), name.c_str());
            
            //spAtlasRegion *r = spAtlas_findRegion(atlas, skinName.c_str());
            spRegionAttachment* regionNew = SUB_CAST(spRegionAttachment, attachment);
            regionNew->x = regionOld->x;
            regionNew->y = regionOld->y;
            regionNew->rotation = regionOld->rotation;
            regionNew->width = regionOld->width;
            regionNew->height = regionOld->height;
            //region->regionOffsetX = regionOld->regionOffsetX;
            //region->regionOffsetY = regionOld->regionOffsetY;
            
            
            spRegionAttachment_updateOffset(regionNew);
            
            spSlot* slot = cobj->findSlot(name.c_str());
            spSlot_setAttachment(slot, attachment);
            
            
            region = nextRegion;
        }
        //-------------------------------
        CCLOG("SPINE_EXTENDS_TO_LUA");
        return 1;
        
    } else if (argc == 2)
    {
        
        
        std::string arg0;
        std::string arg1;
        
        
        luaval_to_std_string(tolua_S, 2,&arg0, "sp.SkeletonRenderer:changeSkin");
        luaval_to_std_string(tolua_S, 3, &arg1, "sp.SkeletonRenderer:changeSkin");
        
        spAtlas* atlas = spAtlas_createFromFile(arg0.c_str(), 0);
        spAtlasAttachmentLoader* attachmentLoader = spAtlasAttachmentLoader_create(atlas);
        
        spAtlasRegion* region, *nextRegion;
        region= atlas->regions;
        while (region) {
            nextRegion = region->next;
            
            std::string name = region->name;
            std::string oldName = arg1;
            
            spRegionAttachment* regionOld = SUB_CAST(spRegionAttachment, cobj->getAttachment(oldName.c_str(), oldName.c_str()));
            
            
            spAttachment* attachment = spAttachmentLoader_newAttachment(SUPER(attachmentLoader), 0, SP_ATTACHMENT_REGION, name.c_str(), name.c_str());
            
            spRegionAttachment* regionNew = SUB_CAST(spRegionAttachment, attachment);
            regionNew->x = regionOld->x;
            regionNew->y = regionOld->y;
            regionNew->rotation = regionOld->rotation;
            regionNew->width = regionOld->width;
            regionNew->height = regionOld->height;
            
            
            spRegionAttachment_updateOffset(regionNew);
            
            spSlot* slot = cobj->findSlot(oldName.c_str());
            spSlot_setAttachment(slot, attachment);
            
            
            region = nextRegion;
            
            break;
        }
        
        return 1;
        
    }

    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "sp.SkeletonRenderer:changekin",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_spine_SkeletonRenderer_changeSkin'.",&tolua_err);
#endif
    
    return 0;
}


int lua_register_extendsToLua(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sp.SkeletonRenderer");
    tolua_cclass(tolua_S,"SkeletonRenderer","sp.SkeletonRenderer","cc.Node",nullptr);
    
    tolua_beginmodule(tolua_S,"SkeletonRenderer");
    
    tolua_function(tolua_S,"changeSkin",lua_cocos2dx_spine_SkeletonRenderer_changeSkin);
    
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(spine::SkeletonRenderer).name();
    g_luaType[typeName] = "sp.SkeletonRenderer";
    g_typeCast["SkeletonRenderer"] = "sp.SkeletonRenderer";
    return 1;
}

TOLUA_API int register_extendsToLua_module(lua_State* tolua_S)
{
    tolua_open(tolua_S);
    
    tolua_module(tolua_S,"sp",0);
    tolua_beginmodule(tolua_S,"sp");
    
    lua_register_extendsToLua(tolua_S);
    
    tolua_endmodule(tolua_S);
    return 1;
}

