Import('env')

env.Append(CPPPATH=['src'])

target = 'game-of-life'
source = (
    'src/main.c',
)

program = env.Program(target, source)

Return('program')
