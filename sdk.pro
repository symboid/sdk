TEMPLATE = subdirs

SUBDIRS = \
    elementum \
    krono \
    ephemeris \
    astro \
    gazetta \
    hosting \
    dox \
    test \
    test_elementum \
    launcher \
    basics

test_elementum.file = elementum/test/test_elementum.pro

elementum.depends = basics
krono.depends = elementum
ephemeris.depends = elementum
astro.depends = elementum
gazetta.depends = elementum
hosting.depends = elementum basics
dox.depends = elementum
test.depends = elementum
test_elementum.depends = elementum
test_elementum.depends = test
launcher.depends = basics

HEADERS = \
    sdk_config.h
