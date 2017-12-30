#ifndef _GOL_GAME_H_
#define _GOL_GAME_H_

struct game;

struct game *
game_new(const char *cfg_path);

void
game_run(struct game *g);

void
game_free(struct game *g);

#endif  /* _GOL_GAME_H_ */
