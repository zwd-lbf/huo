#ifndef _FOR_EACH_H
#define _FOR_EACH_H

#include "../structures/structures.h"

struct Value for_each(struct Tree * ast, struct Tree_map * defined, struct Scopes * scopes, int max_depth);
struct Value for_each_string(struct Value string, struct Tree * ast, struct Tree_map * defined, struct Scopes * scopes, int max_depth);

#endif
