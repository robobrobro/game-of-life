#ifndef _GOL_GAME_OPS_H_
#define _GOL_GAME_OPS_H_

struct game;

typedef void (*game_op_render_t)(struct game *g);

struct game_ops
{
    game_op_render_t render;
};

#endif  /* _GOL_GAME_OPS_H_ */
