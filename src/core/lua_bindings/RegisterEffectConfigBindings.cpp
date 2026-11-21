#include "core/LuaBindings.h"
#include "packages/EffectConfig.h"

void registerEffectConfigBindings(sol::state& lua)
{
    lua.new_enum<EffectType>
    (
        "EffectType",
        {
            {"LeiTan_Air",EffectType::LeiTan_Air},
            {"Bullet_Air",EffectType::Bullet_Air},
            {"PlayerBullet_Air",EffectType::PlayerBullet_Air},
            {"VoidUpdate",EffectType::VoidUpdate}
        }
    );

    lua.new_enum<OverlayType>
    (
        "OverlayType",
        {
            {"Picture_Overlay",OverlayType::Picture_Overlay},
            {"Text_Overlay",OverlayType::Text_Overlay}
        }
    );

    lua.new_usertype<EffectConfig>
    (
        "EffectConfig",
        sol::constructors<EffectConfig(sf::Texture& texture)>(),
        "spawn_point_",&EffectConfig::spawn_point_,
        "effecttype_",&EffectConfig::effecttype_,
        "time_",&EffectConfig::time_,
        "a_",&EffectConfig::a_,
        "v_",&EffectConfig::v_,
        "v2_",&EffectConfig::v2_,
        "color_alpha_",&EffectConfig::color_alpha_,
        "direction_",&EffectConfig::direction_,
        "texture_",&EffectConfig::texture_,
        "texturelist_size_",&EffectConfig::texturelist_size_,
        "current_texture_num_",&EffectConfig::current_texture_num_,
        "random_rotate_",&EffectConfig::random_rotate_,
        "effect_index_",&EffectConfig::effect_index_,
        "isText",&EffectConfig::isText,
        //"font_",&EffectConfig::font_,
        "text_",&EffectConfig::text_,
        "text_size_",&EffectConfig::text_size_
    );
}