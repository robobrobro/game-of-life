#ifndef _GOL_LOG_H_
#define _GOL_LOG_H_

#include <stdio.h>

#define LOG_DEBUG(fmt, ...) { \
    fprintf(stderr, "[DEBUG %s:%s:%d] " fmt "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    /* TODO log to file */ \
}

#define LOG_ERROR(fmt, ...) { \
    fprintf(stderr, "[ERROR %s:%s:%d] " fmt "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    /* TODO log to file */ \
}

#endif /* _GOL_LOG_H_ */
