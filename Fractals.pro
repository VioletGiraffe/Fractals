TEMPLATE = subdirs

SUBDIRS += app math cpputils cpp-template-utils fractals

cpputils.depends = cpp-template-utils

math.depends = cpputils

fractals.depends = math

app.depends = math cpputils fractals
