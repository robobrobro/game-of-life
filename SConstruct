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
        '#lib/unity/include',
        '#lib/unity/src',
    ],
    LIBPATH = ['$STAGING_DIR'],
)

debug_env = env.Clone(MODE='debug')
debug_env.Append(
    CFLAGS = ['--coverage'],
    LINKFLAGS = ['--coverage'],
)

release_env = env.Clone(MODE='release')
# TODO add extra action to strip

for env in (debug_env, release_env):
    # Build the libraries
    libs = SConscript(
        dirs = 'lib',
        variant_dir = env.subst('$BUILD_DIR/lib'),
        duplicate = False,
        exports = {'env': env.Clone()},
    )

    env.Install('$STAGING_DIR', libs)

    # Build the tests
    SConscript(
        dirs = 'test',
        variant_dir = debug_env.subst('$BUILD_DIR/test'),
        duplicate = False,
        exports = {'env': env.Clone()},
    )

    # Build the objects
    objs = SConscript(
        dirs = '.',
        variant_dir = env.subst('$BUILD_DIR'),
        duplicate = False,
        exports = {'env': env.Clone()},
    )

    env.Install('$STAGING_DIR', objs)
