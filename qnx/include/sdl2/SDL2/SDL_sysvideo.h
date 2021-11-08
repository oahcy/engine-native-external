/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2021 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef SDL_sysvideo_h_
#define SDL_sysvideo_h_

#include "SDL_messagebox.h"
#include "SDL_shape.h"
#include "SDL_thread.h"
#include "SDL_metal.h"



/* The SDL video driver */

typedef struct SDL_WindowShaper SDL_WindowShaper;
typedef struct SDL_ShapeDriver SDL_ShapeDriver;
typedef struct SDL_VideoDisplay SDL_VideoDisplay;
typedef struct SDL_VideoDevice SDL_VideoDevice;

/* Define the SDL window-shaper structure */
struct SDL_WindowShaper
{
    /* The window associated with the shaper */
    SDL_Window *window;

    /* The user's specified coordinates for the window, for once we give it a shape. */
    Uint32 userx,usery;

    /* The parameters for shape calculation. */
    SDL_WindowShapeMode mode;

    /* Has this window been assigned a shape? */
    SDL_bool hasshape;

    void *driverdata;
};

/* Define the SDL shape driver structure */
struct SDL_ShapeDriver
{
    SDL_WindowShaper *(*CreateShaper)(SDL_Window * window);
    int (*SetWindowShape)(SDL_WindowShaper *shaper,SDL_Surface *shape,SDL_WindowShapeMode *shape_mode);
    int (*ResizeWindowShape)(SDL_Window *window);
};

typedef struct SDL_WindowUserData
{
    char *name;
    void *data;
    struct SDL_WindowUserData *next;
} SDL_WindowUserData;

/* Define the SDL window structure, corresponding to toplevel windows */
struct SDL_Window
{
    const void *magic;
    Uint32 id;
    char *title;
    SDL_Surface *icon;
    int x, y;
    int w, h;
    int min_w, min_h;
    int max_w, max_h;
    Uint32 flags;
    Uint32 last_fullscreen_flags;

    /* Stored position and size for windowed mode */
    SDL_Rect windowed;

    SDL_DisplayMode fullscreen_mode;

    float opacity;

    float brightness;
    Uint16 *gamma;
    Uint16 *saved_gamma;        /* (just offset into gamma) */

    SDL_Surface *surface;
    SDL_bool surface_valid;

    SDL_bool is_hiding;
    SDL_bool is_destroying;
    SDL_bool is_dropping;       /* drag/drop in progress, expecting SDL_SendDropComplete(). */

    SDL_WindowShaper *shaper;

    SDL_HitTest hit_test;
    void *hit_test_data;

    SDL_WindowUserData *data;

    void *driverdata;

    SDL_Window *prev;
    SDL_Window *next;
};
#define FULLSCREEN_VISIBLE(W) \
    (((W)->flags & SDL_WINDOW_FULLSCREEN) && \
     ((W)->flags & SDL_WINDOW_SHOWN) && \
     !((W)->flags & SDL_WINDOW_MINIMIZED))

/*
 * Define the SDL display structure.
 * This corresponds to physical monitors attached to the system.
 */
struct SDL_VideoDisplay
{
    char *name;
    int max_display_modes;
    int num_display_modes;
    SDL_DisplayMode *display_modes;
    SDL_DisplayMode desktop_mode;
    SDL_DisplayMode current_mode;
    SDL_DisplayOrientation orientation;

    SDL_Window *fullscreen_window;

    SDL_VideoDevice *device;

    void *driverdata;
};

/* Forward declaration */
struct SDL_SysWMinfo;

/* Define the SDL video driver structure */
#define _THIS   SDL_VideoDevice *_this

typedef struct VideoBootStrap
{
    const char *name;
    const char *desc;
    SDL_VideoDevice *(*create) (int devindex);
} VideoBootStrap;

/* Not all of these are available in a given build. Use #ifdefs, etc. */
extern VideoBootStrap COCOA_bootstrap;
extern VideoBootStrap X11_bootstrap;
extern VideoBootStrap DirectFB_bootstrap;
extern VideoBootStrap WINDOWS_bootstrap;
extern VideoBootStrap WINRT_bootstrap;
extern VideoBootStrap HAIKU_bootstrap;
extern VideoBootStrap PND_bootstrap;
extern VideoBootStrap UIKIT_bootstrap;
extern VideoBootStrap Android_bootstrap;
extern VideoBootStrap PSP_bootstrap;
extern VideoBootStrap VITA_bootstrap;
extern VideoBootStrap RPI_bootstrap;
extern VideoBootStrap KMSDRM_bootstrap;
extern VideoBootStrap KMSDRM_LEGACY_bootstrap;
extern VideoBootStrap DUMMY_bootstrap;
extern VideoBootStrap Wayland_bootstrap;
extern VideoBootStrap NACL_bootstrap;
extern VideoBootStrap VIVANTE_bootstrap;
extern VideoBootStrap Emscripten_bootstrap;
extern VideoBootStrap QNX_bootstrap;
extern VideoBootStrap OFFSCREEN_bootstrap;
extern VideoBootStrap OS2DIVE_bootstrap;
extern VideoBootStrap OS2VMAN_bootstrap;

extern SDL_VideoDevice *SDL_GetVideoDevice(void);
extern int SDL_AddBasicVideoDisplay(const SDL_DisplayMode * desktop_mode);
extern int SDL_AddVideoDisplay(const SDL_VideoDisplay * display, SDL_bool send_event);
extern void SDL_DelVideoDisplay(int index);
extern SDL_bool SDL_AddDisplayMode(SDL_VideoDisplay *display, const SDL_DisplayMode * mode);
extern int SDL_GetIndexOfDisplay(SDL_VideoDisplay *display);
extern SDL_VideoDisplay *SDL_GetDisplay(int displayIndex);
extern SDL_VideoDisplay *SDL_GetDisplayForWindow(SDL_Window *window);
extern void *SDL_GetDisplayDriverData( int displayIndex );
extern SDL_bool SDL_IsVideoContextExternal(void);

extern void SDL_GL_DeduceMaxSupportedESProfile(int* major, int* minor);

extern int SDL_RecreateWindow(SDL_Window * window, Uint32 flags);
extern SDL_bool SDL_HasWindows(void);

extern void SDL_OnWindowShown(SDL_Window * window);
extern void SDL_OnWindowHidden(SDL_Window * window);
extern void SDL_OnWindowResized(SDL_Window * window);
extern void SDL_OnWindowMinimized(SDL_Window * window);
extern void SDL_OnWindowRestored(SDL_Window * window);
extern void SDL_OnWindowEnter(SDL_Window * window);
extern void SDL_OnWindowLeave(SDL_Window * window);
extern void SDL_OnWindowFocusGained(SDL_Window * window);
extern void SDL_OnWindowFocusLost(SDL_Window * window);
extern void SDL_UpdateWindowGrab(SDL_Window * window);
extern SDL_Window * SDL_GetFocusWindow(void);

extern SDL_bool SDL_ShouldAllowTopmost(void);

extern float SDL_ComputeDiagonalDPI(int hpix, int vpix, float hinches, float vinches);

extern void SDL_ToggleDragAndDropSupport(void);

#endif /* SDL_sysvideo_h_ */

/* vi: set ts=4 sw=4 expandtab: */
