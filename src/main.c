#include <stdio.h>
#include "game.h"

int main(int argc, char **argv)
{
    struct game *g;

    if (argc != 2) {
        fprintf(stderr, "usage: %s cfg_file\n", *argv);
        return 1;
    }

    if (!(g = game_new(argv[1])))
        return 2;

    game_run(g);
    game_free(g);

    return 0;
}
