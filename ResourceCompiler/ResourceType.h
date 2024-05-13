#pragma once

// Enums
enum ResourceType
{
	Unknown_ResourceType = 0,
	Image_RGBA_U8_ResourceType,
	Image_Grayscale_U16_ResourceType,	// NOT IMPLEMENTED
	Image_Grayscale_F32_ResourceType,	// NOT IMPLEMENTED
	Model_Obj_ResourceType,				// NOT IMPLEMENTED
	Shader_Vertex_ResourceType,			// NOT IMPLEMENTED
	Shader_Pixel_ResourceType,			// NOT IMPLEMENTED
	Shader_Geometry_ResourceType,		// NOT IMPLEMENTED
	Level_ResourceType,					// NOT IMPLEMENTED
	Script_Lua_ResourceType,			// NOT IMPLEMENTED
	Sound_ResourceType,					// NOT IMPLEMENTED
	Music_ResourceType,					// NOT IMPLEMENTED
	Font_ResourceType					// NOT IMPLEMENTED
};

// ---------------------------------------------------------------------------------------------------------------

u32 get_resource_type(str file_extension)
{
	if (strcmp(file_extension, "png") == 0)
		return Image_RGBA_U8_ResourceType;
	else if (strcmp(file_extension, "obj") == 0)
		return Model_Obj_ResourceType;
	else if (strcmp(file_extension, "vs") == 0)
		return Shader_Vertex_ResourceType;
	else if (strcmp(file_extension, "ps") == 0)
		return Shader_Pixel_ResourceType;
	else if (strcmp(file_extension, "gs") == 0)
		return Shader_Geometry_ResourceType;
	else if (strcmp(file_extension, "lvl") == 0)
		return Level_ResourceType;
	else if (strcmp(file_extension, "lua") == 0)
		return Script_Lua_ResourceType;
	else if (strcmp(file_extension, "wav") == 0)
		return Sound_ResourceType;
	else if (strcmp(file_extension, "mus") == 0)
		return Music_ResourceType;
	else if (strcmp(file_extension, "ttf") == 0)
		return Font_ResourceType;

	return Unknown_ResourceType; // Did not find a match
}

str get_resource_type_name(u32 resource_type)
{
	switch (resource_type)
	{
		case Image_RGBA_U8_ResourceType: return "png";
		case Model_Obj_ResourceType: return "obj";
		case Shader_Vertex_ResourceType: return "vs";
		case Shader_Pixel_ResourceType: return "ps";
		case Shader_Geometry_ResourceType: return "gs";
		case Level_ResourceType: return "lvl";
		case Script_Lua_ResourceType: return "lua";
		case Sound_ResourceType: return "wav";
		case Music_ResourceType: return "mus";
		case Font_ResourceType: return "ttf";
		default: return "unknown";
	}
}
