#define gml extern "C" double
#if defined(__linux__)
#include <cstring>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
gml gmx11_set_caption(const char * caption)
{
    Display *display;
    Window root;
    Atom net_wm_name;
    Atom utf8_string;
    XEvent xev;

    display = XOpenDisplay(NULL);
    if (display == NULL) {
        return 0;
    }

    root = DefaultRootWindow(display);
    
    net_wm_name = XInternAtom(display, "_NET_WM_NAME", False);
    utf8_string = XInternAtom(display, "UTF8_STRING", False);
    if(net_wm_name == None || utf8_string == None) {
        XCloseDisplay(display);
        return 0;
    }
    XStoreName(display, root, caption);
    XChangeProperty(display, root, net_wm_name, utf8_string, 8,
                    PropModeReplace, (const unsigned char *)caption, strlen(caption));

    XFlush(display);
    XCloseDisplay(display);
    return 1;
}
#endif