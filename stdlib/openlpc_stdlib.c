#include <stdint.h>
#include <openlpc_stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

void *memcpy (void *dest, const void *src, uint32_t n) {
	uint32_t i;
	for (i = 0; i < n; i++)
		((uint8_t *)dest)[i] = ((const uint8_t *)src)[i];

	return dest;
}

#ifdef __cplusplus
}
#endif

