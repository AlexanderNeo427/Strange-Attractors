#ifndef ECS_TYPES
#define ECS_TYPES

#include <assert.h>
#include <cstdint>
#include <bitset>
#include <memory>

#include <unordered_map>
#include <queue>
#include <array>
#include <set>

namespace ECS
{
	using EntityID = std::uint32_t;
	const EntityID MAX_ENTITIES = 4096;

	using ComponentTypeID = std::uint8_t;
	const ComponentTypeID MAX_COMPONENTS = 32;

	using Signature = std::bitset<MAX_COMPONENTS>;
};

#endif
