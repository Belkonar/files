# Thoughts

Put this on any dialog (maybe make a custom dialog class for it). It'll make sure to close
the app if the proper windows are closed and only dialogs are left.

```cpp
setAttribute(Qt::WA_QuitOnClose, false);
```
