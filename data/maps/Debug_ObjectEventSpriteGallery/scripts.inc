Debug_ObjectEventSpriteGallery_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Debug_ObjectEventSpriteGallery_OnTransition
	.byte 0

Debug_ObjectEventSpriteGallery_OnTransition::
	copyvar VAR_OBJ_GFX_ID_1, VAR_DEBUG
	compare VAR_OBJ_GFX_ID_1, 0
	goto_if_lt Debug_ObjectEventSpriteGallery_SetMin
	compare VAR_OBJ_GFX_ID_1, 243
	goto_if_gt Debug_ObjectEventSpriteGallery_SetMax
	return

Debug_ObjectEventSpriteGallery_SetMin::
	setvar VAR_OBJ_GFX_ID_1, 0
	end

Debug_ObjectEventSpriteGallery_SetMax::
	setvar VAR_OBJ_GFX_ID_1, 243
	end

Debug_ObjectEventSpriteGallery_IncOne::
	addvar VAR_DEBUG, 1
	goto Debug_ObjectEventSpriteGallery_Warp
	end

Debug_ObjectEventSpriteGallery_IncTen::
	addvar VAR_DEBUG, 10
	goto Debug_ObjectEventSpriteGallery_Warp
	end

Debug_ObjectEventSpriteGallery_DecOne::
	addvar VAR_DEBUG, -1
	goto Debug_ObjectEventSpriteGallery_Warp
	end

Debug_ObjectEventSpriteGallery_DecTen::
	addvar VAR_DEBUG, -10
	goto Debug_ObjectEventSpriteGallery_Warp
	end
	
Debug_ObjectEventSpriteGallery_Warp::
	warpsilent MAP_DEBUG_OBJECT_EVENT_SPRITE_GALLERY, 0, 0, 0
	end
