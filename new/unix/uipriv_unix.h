// 22 april 2015
#define GLIB_VERSION_MIN_REQUIRED GLIB_VERSION_2_32
#define GLIB_VERSION_MAX_ALLOWED GLIB_VERSION_2_32
#define GDK_VERSION_MIN_REQUIRED GDK_VERSION_3_4
#define GDK_VERSION_MAX_ALLOWED GDK_VERSION_3_4
#include <gtk/gtk.h>

// thanks ebassi in irc.gimp.net/#gtk+
#define _UI_EXTERN __attribute__((visibility("default"))) extern
#include "../ui.h"
#include "../ui_unix.h"
#include "../uipriv.h"