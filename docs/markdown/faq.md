# FAQ

### What the heck is this App class? Why not just global functions like in Processing?

There are many ways to let a user write functions. For example, in Processing there are a few global functions and 
you simply write global variables at the top of the file. The problem with doing this is that you have no control
over the lifetime. 

Global variables outlive the main function and are automatically cleaned up after the main function has returned. This
is usually not an issue for trivially destructible types. But when the global object is a complex type like an
SFML framebuffer or an SFML GPU texture, they have access to underlying resources like OpenGL handles.

This would mean that at the end of the main function, the resources are cleaned up and handles are returned to the operating
system, then the main function returns, and only then are the global variables destructed. Which means the SFML types
might try to access the OpenGL handles, which are no longer valid, causing a crash. This is why global variables are
generally dangerous and should be avoided. No variable should outlive the scope of the main function.

A simple solution to this is to create a class that holds all the global variables and functions. This class is then 
constructed, called and destructed within the scope of the main function. This way, all the resources are automatically 
cleaned up before the main function returns and everything is fine.

This is the reason you should not ever write a global variable in cppgfx, instead make it part of the App class.

### Can I write anything outside of the App class?

Yes, you can write as many classes and functions outside of the main App class, except global variables. See above why
you should avoid global variables.

If you must access the app instance from outside, you can use the prefix `App::Get().` to access any public members.
```cpp
// Inside of the App class:
setTitle("Hello World");

// Equivalent outside of App:
App::Get().setTitle("Hello World");
```

`App::Get().` will always point to the last `cppgfx::App` instance constructed (which should be the only one).
Keep in mind that this points to the `cppgfx::App` parent class itself and not the class you derived from it. Thus,
this can only be used to access built-in functions, but not any custom functions and variables you wrote yourself.