#ifndef _GOL_GAME_H_
#define _GOL_GAME_H_

#include "game_ops.h"

struct game;

struct game *
game_new(const char *cfg_path, const struct game_ops *ops);

void
game_run(struct game *g);

void
game_free(struct game *g);

int
game_window_width(struct game *g);

int
game_window_height(struct game *g);

#endif  /* _GOL_GAME_H_ */
