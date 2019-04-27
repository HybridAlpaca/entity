#include "state.h"
#include <kernel.h>

kernel_api * kernel;

static entity_index_i entity_index
{
	entity_index_create,
	entity_index_destroy
};

bool start(kernel_api * api)
{
	kernel = api;

	kernel->api_impl_add(ENTITY_INDEX_INTERFACE_NAME, &entity_index);

	return true;
}

bool stop()
{
	return true;
}

bool update()
{
	return true;
}

const char * exports[]{ ENTITY_INDEX_INTERFACE_NAME };

extern "C" module_t module
{
	"entity",

	exports,
	nullptr,

	1,
	0,

	start,
	stop,
	update
};

