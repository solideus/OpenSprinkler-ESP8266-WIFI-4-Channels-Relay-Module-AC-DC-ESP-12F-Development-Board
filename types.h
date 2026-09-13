#pragma once

#include <stdint.h>

#if defined(ESP8266)
typedef uint32_t time_os_t;
#else
#include <time.h>
typedef uint32_t time_os_t;
#endif
