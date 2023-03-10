#pragma once
#include <cstdint>
namespace VALROM {
    namespace offsets
    {
        constexpr uintptr_t uworld_state = 0x8853600;
        constexpr uintptr_t uworld_key = 0x8853638;
 game_instance // TYPE=uintptr_t
        constexpr uintptr_t persistent_level = 0x38; // world + persistent_level // TYPE=uintptr_t

        constexpr uintptr_t local_player_array = 0x44; // game_instance + local_player_array // TYPE=uintptr_t
        constexpr uintptr_t local_player_controller = 0x38; // local_player + local_player_controller // TYPE=uintptr_t
        constexpr uintptr_t local_player_pawn = 0x460; // local_player_controller + local_player_pawn // TYPE=uintptr_t (=actor)
        constexpr uintptr_t control_rotation = 0x470; // local_player_controller + control_rotation // TYPE=Vector3

        constexpr uintptr_t camera_manager = 0x478; // local_player_controller + camera_manager // TYPE=uintptr_t
        constexpr uintptr_t camera_position = 0x1240; // camera_manager + camera_position // TYPE=Vector3
        constexpr uintptr_t camera_rotation = 0x144C;  // camera_manager + camera_rotation // TYPE=Vector3
        constexpr uintptr_t camera_fov = 0x1258;  // camera_manager + camera_fov // TYPE=float

        constexpr uintptr_t actor_array = 0xA0; // persistent_level + actor_array // TYPE=uintptr_t
        constexpr uintptr_t actor_count = actor_array + 0x8; // persistent_level + actor_count // TYPE=int

        constexpr uintptr_t unique_id = 0x38;  // actor + actor_id // TYPE=uintptr_t
        constexpr uintptr_t mesh_component = 0x420; // actor + mesh_component // TYPE=uintptr_t
        constexpr uintptr_t last_render_time = 0x350; // mesh_component + last_render_time // TYPE=float
        constexpr uintptr_t last_submit_time = 0x358; // mesh_component + last_submit_time // TYPE=float
        constexpr uintptr_t bone_array = 0x558; // mesh_component + bone_array // TYPE=uintptr_t
        constexpr uintptr_t bone_array_Cached = 0x568; // mesh_component + bone_array // TYPE=uintptr_t
        constexpr uintptr_t bone_count = 0x560; // actor + bone_count // TYPE=uintptr_t
        constexpr uintptr_t component_to_world = 0x250; // mesh_component + component_to_world // TYPE=uintptr_t
        constexpr uintptr_t root_component = 0x230; // actor + root_component // TYPE=uintptr_t
        constexpr uintptr_t root_position = 0x164; // root_component + root_position // TYPE=Vector3
        constexpr uintptr_t damage_handler = 0x9A8; // actor/local_player_pawn + damage_handler // TYPE=uintptr_t
        constexpr uintptr_t health = 0x1B0; // damage_handler + health // TYPE=float
        constexpr uintptr_t dormant = 0x100; // actor + dormant // TYPE=bool
        constexpr uintptr_t player_state = 0x3F0; // actor/local_player_pawn + player_state // TYPE=uintptr_t
        constexpr uintptr_t team_component = 0x628; // player_state + team_component // TYPE=uintptr_t
        constexpr uintptr_t team_id = 0xF8; // team_component + team_id
    }
}
