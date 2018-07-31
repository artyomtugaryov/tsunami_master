TEMPLATE = subdirs
SUBDIRS += \
    TMlib \
    TsunamiManager \
    GUI \
    PlotLib \
    tests

TMlib.subdir = src/TMlib
TsunamiManager.subdir  = src/TsunamiManager
GUI.subdir  = src/GUI
PlotLib.subdir = src/PlotLib
tests.subdir  = tests

GUI.depends = TMlib TsunamiManager PlotLib
tests.depends = TMlib
TsunamiManager.depends = TMlib PlotLib
TMlib.depends = PlotLib
