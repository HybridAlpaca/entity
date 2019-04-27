#pragma once

#include <entity.h>

struct kernel_i;

extern kernel_i * kernel;

uint32_t entity_index_create();

void entity_index_destroy(uint32_t entity);
