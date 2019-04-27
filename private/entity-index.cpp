#include "state.h"

#include <queue>
#include <vector>

static const uint32_t ENTITY_INDEX_BITS = 24;
static const uint32_t ENTITY_INDEX_MASK = (1 << ENTITY_INDEX_BITS) - 1;

static const uint32_t ENTITY_GENERATION_BITS = 8;
static const uint32_t ENTITY_GENERATION_MASK = (1 << ENTITY_GENERATION_BITS) - 1;

struct entity_index_o
{
	std::vector<uint8_t> generations;
	std::queue<uint32_t> free_indices;
};

struct entity_t
{
	uint32_t index : 24;
	uint32_t generation : 8;
};

struct entity_union_t
{
	uint32_t raw;
	entity_t impl;
};

static entity_index_o state;

uint32_t entity_index_create()
{
	uint32_t idx;

	if (state.free_indices.size() > 1)
	{
		idx = state.free_indices.front();

		state.free_indices.pop();
	}
	else
	{
		idx = state.generations.size();

		state.generations.push_back(0);
	}

	entity_union_t pun;
	pun.impl = { idx, state.generations[idx] };

	return pun.raw;
}

void entity_index_destroy(uint32_t entity)
{
	entity_union_t pun;
	pun.raw = entity;

	++state.generations[pun.impl.index];

	state.free_indices.push(pun.impl.index);
}
