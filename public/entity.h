#pragma once

#include <stdint.h>

static const char * ENTITY_INDEX_INTERFACE_NAME = "entity_index_i";
static const char * COMPONENT_INTERFACE_NAME = "component_i";

struct entity_index_i
{
	uint32_t (*create)();

	void (*destroy)(uint32_t entity);
};

struct component_i
{
	void (*create)(const uint32_t * entities, uint32_t entity_count, uint64_t * instances);
	void (*lookup)(const uint32_t * entities, uint32_t entity_count, uint64_t * instances);
	void (*destroy)(uint32_t * entities, uint32_t entity_count);

	void * (*get_interface)(const char * id);
};
