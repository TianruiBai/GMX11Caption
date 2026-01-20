# GMX11Caption ✅

**Fix GameMaker caption encoding on Linux (X11)**

## Overview 💡
This small utility provides a single exported function `gmx11_set_caption(const char * caption)` that sets a UTF-8 window caption via X11. It was created to help GameMaker projects that need to display non-Latin text (Chinese, Japanese, etc.) as a window caption under X11.

The function sets the `_NET_WM_NAME` property with type `UTF8_STRING` (and calls the legacy `XStoreName`) so desktop environments that respect the modern property will show UTF-8 text correctly.

---

## How it works 🔧
- Opens an X11 display connection (`XOpenDisplay`).
- Targets the **root window** (`DefaultRootWindow`) and obtains the atoms `_NET_WM_NAME` and `UTF8_STRING`.
- Uses `XStoreName` (legacy) and `XChangeProperty(... _NET_WM_NAME, UTF8_STRING, ...)` to set the UTF-8 caption bytes.
- Flushes and closes the display and returns `1` on success or `0` on failure.

**Signature (C export):**

```
extern "C" double gmx11_set_caption(const char * caption);
```

Return value: `1` = success, `0` = failure (e.g., cannot open display or required atoms not available).

---

## Build (Linux, X11) 🛠️
Dependencies: `libx11` development headers (install package `libx11-dev` or similar).

Example build command:

```
g++ -O2 -fPIC -shared GMX11caption.cpp -o libgmx11caption.so -lX11
```

This produces `libgmx11caption.so` which you can ship with or load from GameMaker or other programs.

---

## Usage (from GameMaker) 🕹️
Place `libgmx11caption.so` where your game can load it (e.g., in the executable folder or proper extension folder for your GameMaker build target).

Then bind and call the function from GML using your GameMaker version's external function bindings. Example (pseudo-GML):

```gml
// Bind (API varies with GM version — check your docs for exact function names/argument types)
ext = external_define("libgmx11caption.so", "gmx11_set_caption", dll_cdecl, false, false, ty_real, ty_string);
// Call (UTF-8 string literal)
external_call(next, "窗口标题 - 中文测试");
external_free(next);
```

Note: The exact `external_define`/`external_call` usage and argument/return type constants depend on the GameMaker version. Use the correct signatures for your runtime.

---

## Limitations & Notes ⚠️
- This library targets **X11 only**. Wayland-based sessions are not affected.
- The current implementation writes to the **root window** (DefaultRootWindow). That may or may not change the visible application/window title in all desktop environments. Some DEs take titles from the active window or ignore the root name completely.
- To change a **specific application window's** title (e.g., the GameMaker game window), you should find the game window (via scanning child windows with `XQueryTree` and `XGetWMName` / `XGetWMClass`) and call `XChangeProperty` on that window rather than the root window. This repository can be extended to add that behavior.
- The function expects UTF-8 encoded input. Make sure strings passed from GameMaker are UTF-8.

---

## Suggested improvement (todo) ✨
- Add an option to target the active or named GameMaker window instead of the root window.
- Add a small example binary that demonstrates calling the function directly from C for testing.

---

## License & Contributing
Feel free to file issues or PRs. Add a license file as needed for your project.

---

If you'd like, I can add a small example program to test the `.so` or implement window-searching logic to target the GameMaker window directly. ✅
