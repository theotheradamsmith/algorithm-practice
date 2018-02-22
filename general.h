#pragma once

#define print_debug(fmt, ...) \
	do { if (DEBUG) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
							__LINE__, __func__, __VA_ARGS__); } while (0)


