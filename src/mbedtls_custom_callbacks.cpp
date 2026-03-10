#include <string.h>
#include "mbedtls/platform_util.h"
#include "pico/rand.h"

extern "C" int mbedtls_hardware_poll(void *data, unsigned char *output, size_t len, size_t *olen)
{
    (void)data;
    size_t bytes_left = len;
    unsigned char *output_ptr = output;
    uint64_t random_data;
    *olen = 0;

    while (bytes_left) {
        random_data = get_rand_64();
        size_t cpy_cnt = bytes_left < sizeof(random_data) ? bytes_left : sizeof(random_data);
        memcpy(output_ptr, &random_data, cpy_cnt);
        bytes_left -= cpy_cnt;
        output_ptr += cpy_cnt;
        *olen += cpy_cnt;
    }

    mbedtls_platform_zeroize(&random_data, sizeof(random_data));
    return 0;
}