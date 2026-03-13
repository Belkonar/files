# Thoughts

Put this on any dialog (maybe make a custom dialog class for it). It'll make sure to close
the app if the proper windows are closed and only dialogs are left.

```cpp
setAttribute(Qt::WA_QuitOnClose, false);
```

All windows also need this.

```cpp
setAttribute(Qt::WA_DeleteOnClose);
```

It ensures that the window cleans up after itself, so you can do this and you don't need
to track anything.

```cpp
(new MyWindow()).show();
```
