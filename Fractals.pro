TEMPLATE = subdirs

SUBDIRS = app math cpputils cpp-template-utils fractals ocl

cpputils.depends = cpp-template-utils

math.depends = cpputils

fractals.depends = math ocl

app.depends = math cpputils fractals
