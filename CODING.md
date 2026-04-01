# Coding Guidelines

As I'm going to be

Each custom widget should have a delegating function for setting up the widget called
`init`. This should be called by the constructor and should be consistent in it's layout.
It should have these sections in this order (with comments notating the sections).

1. Settings
   Get a `QSettings` object and pull the settings we need.
1. Internal attributes
   Specifically for assigning initial settings on the widget itself.
1. Actions
   If no actions are used, this can be removed.
1. Widget initialization
1. Layouts
1. Widget configuration
1. Regular slots
1. Action slots

