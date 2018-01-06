# Set up the environments
env = Environment(
    BUILD_ROOT = '#build',
    BUILD_DIR = '$BUILD_ROOT/$MODE',
    STAGING_ROOT = '$BUILD_ROOT/bin',
    STAGING_DIR = '$STAGING_ROOT/$MODE',

    CFLAGS = [
        '-Wall',
        '-Werror',
        '-Wextra',
    ],
    CPPPATH = [
        '#engine/include',
    ],
    LIBPATH = ['$STAGING_DIR'],
)

debug_env = env.Clone(MODE='debug')
debug_env.Append(CFLAGS=['-g'])

test_env = env.Clone(MODE='test')
test_env.Append(
    CFLAGS = ['--coverage'],
    LINKFLAGS = ['--coverage'],
    CPPPATH = [
        '#test/lib/unity/include',
        '#test/lib/unity/src',
    ],
)

release_env = env.Clone(MODE='release')
# TODO add extra action to strip

# Build the tests
SConscript(
    dirs = 'test',
    variant_dir = test_env.subst('$BUILD_DIR/test'),
    duplicate = False,
    exports = {'env': test_env.Clone()},
)

for env in (debug_env, release_env):
    # Build the libraries
    libs = SConscript(
        dirs = 'lib',
        variant_dir = env.subst('$BUILD_DIR/lib'),
        duplicate = False,
        exports = {'env': env.Clone()},
    )

    env.Install('$STAGING_DIR', libs)

    # Build the objects
    objs = SConscript(
        dirs = '.',
        variant_dir = env.subst('$BUILD_DIR'),
        duplicate = False,
        exports = {'env': env.Clone()},
    )

    env.Install('$STAGING_DIR', objs)
