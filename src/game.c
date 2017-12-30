#include "game.h"

#include <assert.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "log.h"

struct game
{
    int window_width;
    int window_height;
};

static int
parse_cfg_item(const char *key, const char *value, void *ctx)
{
    struct game *g = ctx;

    assert(key != NULL);
    assert(value != NULL);
    assert(ctx != NULL);

    LOG_DEBUG("key:[%s], value:[%s]", key, value);

    if (strcmp(key, "window_width") == 0)
        g->window_width = atoi(value);
    else if (strcmp(key, "window_height") == 0)
        g->window_height = atoi(value);
    else
        LOG_ERROR("invalid key");

    return 0;
}

struct game *
game_new(const char *cfg_path)
{
    struct game *g;

    assert(cfg_path != NULL);
    if (!glfwInit()) {
        LOG_ERROR("failed to initialize GLFW");
        return NULL;
    }

    g = malloc(sizeof(*g));
    if (!g)
        return NULL;

    memset(g, 0, sizeof(*g));

    *g = (typeof(*g)) {
        .window_width = 800,
        .window_height = 600,
    };

    if (!config_parse(cfg_path, parse_cfg_item, g)) {
        LOG_ERROR("failed to parse config");
        free(g);
        return NULL;
    }

    return g;
}

void
game_run(struct game *g)
{
    GLFWwindow *window;

    assert(g != NULL);

    window = glfwCreateWindow(g->window_width, g->window_height, "Game of Life", NULL, NULL);
    if (!window) {
        LOG_ERROR("failed to create window");
        return;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
}

void
game_free(struct game *g)
{
    glfwTerminate();

    assert(g != NULL);
    free(g);
}
