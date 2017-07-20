TEMPLATE = subdirs
SUBDIRS += \
    TMlib \
    TsunamiManager \
    GUI \
    tests

TMlib.subdir = src/TMlib
TsunamiManager.subdir  = src/TsunamiManager
GUI.subdir  = src/GUI
tests.subdir  = tests

GUI.depends = TMlib TsunamiManager
tests.depends = TMlib TsunamiManager
TsunamiManager.depends = TMlib
