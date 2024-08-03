#pragma once
#include <cstdint>

// Not used yet
struct Vector3
{
  float x{};
  float y{};
  float z{};
}vector3, Vec3, vec3;

// Maybe use a struct with padding instead of individual offsets?
namespace Offsets
{
inline constexpr std::uintptr_t playerBase{ 0x10f4f4 };
inline constexpr std::uintptr_t entityList{ 0x10f4f8 };
 
// from playerBase/entityList
inline constexpr std::uintptr_t v3_PlayerPosition{ 0x34 }; // Vector3
inline constexpr std::uintptr_t i_Health{ 0xf8 };
inline constexpr std::uintptr_t i_Armor{ 0xfc };
inline constexpr std::uintptr_t b_ForceAttack{ 0x224 };
inline constexpr std::uintptr_t s_Name{ 0x225 }; // char[16]
inline constexpr std::uintptr_t c_Team{ 0x32c }; // byte
}
