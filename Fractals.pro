TEMPLATE = subdirs

SUBDIRS += app math cpputils cpp-template-utils

cpputils.depends = cpp-template-utils

math.depends = cpputils

app.depends = math cpputils
