#include <OpenGL/gl.h>
#include <stdio.h>
#include "game.h"

static void
render(struct game *g)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, game_window_width(g), game_window_height(g), 0, 0, -1);

    glBegin(GL_QUADS);
    glVertex2f(0, 5);
    glVertex2f(0, 0);
    glVertex2f(5, 0);
    glVertex2f(5, 5);
    glEnd();
}

int
main(int argc, char **argv)
{
    struct game *g;
    struct game_ops ops = {
        .render = render,
    };

    if (argc != 2) {
        fprintf(stderr, "usage: %s cfg_file\n", *argv);
        return 1;
    }

    if (!(g = game_new(argv[1], &ops)))
        return 2;

    game_run(g);
    game_free(g);

    return 0;
}
