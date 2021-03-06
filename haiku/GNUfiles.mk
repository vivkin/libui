# 22 april 2015

CXXFILES += \
	haiku/alloc.cpp \
	haiku/area.cpp \
	haiku/box.cpp \
	haiku/button.cpp \
	haiku/checkbox.cpp \
	haiku/combobox.cpp \
	haiku/control.cpp \
	haiku/datetimepicker.cpp \
	haiku/draw.cpp \
	haiku/entry.cpp \
	haiku/group.cpp \
	haiku/label.cpp \
	haiku/main.cpp \
	haiku/menu.cpp \
	haiku/multilineentry.cpp \
	haiku/progressbar.cpp \
	haiku/radiobuttons.cpp \
	haiku/separator.cpp \
	haiku/singlechild.cpp \
	haiku/slider.cpp \
	haiku/spinbox.cpp \
	haiku/stddialogs.cpp \
	haiku/tab.cpp \
	haiku/text.cpp \
	haiku/util.cpp \
	haiku/window.cpp

HFILES += \
	haiku/uipriv_haiku.hpp

# TODO split into a separate file or put in GNUmakefile.libui somehow?

# flags for the Haiku API
LDFLAGS += \
	-lbe

# flags for building a shared library
LDFLAGS += \
	-shared

# flags for warning on undefined symbols
LDFLAGS += \
	-Wl,--no-undefined -Wl,--no-allow-shlib-undefined

# flags for setting soname
# TODO is this correct for Haiku?
LDFLAGS += \
	-Wl,-soname,$(NAME)$(SUFFIX).$(SOVERSION)
