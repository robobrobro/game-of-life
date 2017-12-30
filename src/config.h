#ifndef _GOL_CONFIG_H_
#define _GOL_CONFIG_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum {
    CONFIG_PARSE_CONTINUE = 0,
    CONFIG_PARSE_STOP = 1,
    CONFIG_PARSE_RESTART = 2,
} config_parse_action_t;

typedef int (*config_parse_cb_t)(const char *key, const char *value, void *ctx);

bool
config_parse(const char *path, config_parse_cb_t cb, void *ctx);

#endif  /* _GOL_CONFIG_H_ */
