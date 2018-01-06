Import('env')

# Build the engine library
engine = SConscript(
    dirs = Dir('engine').srcnode(),
    variant_dir = env.subst('$BUILD_DIR/engine'),
    duplicate = False,
    exports = {'env': env.Clone()},
)

# Build the game
game = SConscript(
    dirs = Dir('game').srcnode(),
    variant_dir = env.subst('$BUILD_DIR/game'),
    duplicate = False,
    exports = {'env': env.Clone()},
)

Return('engine game')
