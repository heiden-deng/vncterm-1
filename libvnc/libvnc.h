
#ifndef _LIBVNC_LIBVNC_H
#define _LIBVNC_LIBVNC_H

/* VNC Authentication */
#define AUTHCHALLENGESIZE 16

struct DisplayState {
    uint8_t *data;
    int linesize;
    int depth;
    int bgr; /* BGR color order instead of RGB. Only valid for depth == 32 */
    int width;
    int height;
    int graphic_mode;
    void *opaque;

    void (*dpy_update)(struct DisplayState *s, int x, int y, int w, int h);
    void (*dpy_resize)(struct DisplayState *s, int w, int h);
    void (*dpy_refresh)(struct DisplayState *s);
    void (*dpy_copy)(struct DisplayState *s, int src_x, int src_y, int dst_x, int dst_y, int w, int h);
    void (*dpy_set_server_text)(struct DisplayState *s, char *text);

    void *hw_opaque;
    void (*hw_update)(void *);
    void (*hw_invalidate)(void *);
    int (*hw_refresh)(struct DisplayState *);

    void *mouse_opaque;
    int (*mouse_is_absolute)(void *);
    void (*mouse_event)(int, int, int, int, void *);

    void (*kbd_put_keycode)(int);
    void (*kbd_put_keysym)(int);

    void *(*init_timer)(void (*)(void *), void *);
    uint64_t (*get_clock)(void);
    int (*set_timer)(void *, uint64_t);

    int (*set_fd_handler)(int, int (*)(void *), void (*)(void *),
			  void (*)(void *), void *);
};
typedef struct DisplayState DisplayState;

struct sockaddr_in;
int vnc_display_init(DisplayState *ds, int display, int find_unused,
		     struct sockaddr_in *addr, char *title,
		     char *keyboard_layout);


/* keyboard/mouse support */
#define MOUSE_EVENT_LBUTTON 0x01
#define MOUSE_EVENT_RBUTTON 0x02
#define MOUSE_EVENT_MBUTTON 0x04

/* keysym is a unicode code except for special keys (see QEMU_KEY_xxx
   constants) */
#define QEMU_KEY_ESC1(c) ((c) | 0xe100)
#define QEMU_KEY_BACKSPACE  0x007f
#define QEMU_KEY_UP         QEMU_KEY_ESC1('A')
#define QEMU_KEY_DOWN       QEMU_KEY_ESC1('B')
#define QEMU_KEY_RIGHT      QEMU_KEY_ESC1('C')
#define QEMU_KEY_LEFT       QEMU_KEY_ESC1('D')
#define QEMU_KEY_HOME       QEMU_KEY_ESC1(1)
#define QEMU_KEY_END        QEMU_KEY_ESC1(4)
#define QEMU_KEY_PAGEUP     QEMU_KEY_ESC1(5)
#define QEMU_KEY_PAGEDOWN   QEMU_KEY_ESC1(6)
#define QEMU_KEY_DELETE     QEMU_KEY_ESC1(3)

#define QEMU_KEY_CTRL_UP         0xe400
#define QEMU_KEY_CTRL_DOWN       0xe401
#define QEMU_KEY_CTRL_LEFT       0xe402
#define QEMU_KEY_CTRL_RIGHT      0xe403
#define QEMU_KEY_CTRL_HOME       0xe404
#define QEMU_KEY_CTRL_END        0xe405
#define QEMU_KEY_CTRL_PAGEUP     0xe406
#define QEMU_KEY_CTRL_PAGEDOWN   0xe407

#endif /* _LIBVNC_LIBVNC_H */