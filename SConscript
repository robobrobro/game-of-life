Import('env')

env.Append(
    LIBS = [
        'glfw3',
        'yaml',
    ],

    LINKFLAGS = [
        '-framework', 'Cocoa',
        '-framework', 'CoreFoundation',
        '-framework', 'CoreVideo',
        '-framework', 'IOKit',
        '-framework', 'OpenGL',
    ],
)

target = 'game-of-life'
source = (
    'src/config.c',
    'src/game.c',
    'src/main.c',
)

program = env.Program(target, source)

Return('program')
