from building import *
Import('rtconfig')

src   = []
cwd   = GetCurrentDir()

# add HMIgui src files.
if GetDepend('PKG_USING_HMIGUI'):
    src += Glob('src/cmd_queue.c')
    src += Glob('src/hmi_driver.c')
    src += Glob('src/hmi_uart.c')

if GetDepend('PKG_USING_HMIGUI_SAMPLE'):
    src += Glob('sample/hmigui_sample.c')

# add HMIgui include path.
path  = [cwd + '/inc']

# add src and include to group.
group = DefineGroup('HMIgui', src, depend = ['PKG_USING_HMIGUI'], CPPPATH = path)

Return('group')