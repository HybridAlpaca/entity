#pragma once

#include <entity.h>

struct kernel_api;

extern kernel_api * kernel;

uint32_t entity_index_create();

void entity_index_destroy(uint32_t entity);
