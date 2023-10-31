# Programming concepts

This section of the cppgfx documentation contains many code example with the intention
of teaching you how to do certain things. When learning programming, you will at one point
encounter many of these problems and even if you don't, it's worth it to read through
them to get a better understanding of what is happening.

## Table of Contents

 - [Objects in Motion](#1-objects-in-motion)
   - [Continuous motion](#11-continuous-motion)

## 1. Objects in motion

### 1.1 Continuous motion

#### Problem

At some point in time you will want to move an object around the screen. The simplest
way is to move the object a specific amount of pixels every frame. A more advanced
method is by giving the object a velocity and acceleration.

```cpp
void update() {
    object.position.x += object.velocity.x;
    object.position.y += object.velocity.y;
}
```

But all of these variants are flawed: The actual speed of the object is dependent on
the framerate. In reality, the framerate will always fluctuate due to non-constant 
system load. This has the effect that the object will move faster and slower depending
on how much work the computer has to do. Not great for games.

In this case, the position will change by Velocity-units per frame, most likely **pixels/frame**.
But the rate of frames is not constant in the real world.

#### Solution

The solution is to use the elapsed frame time as a measure of how far to move the object.

The `frameTime` variable can be used for this job. It represents the time that has elapsed since
the last frame, in seconds. 

Example:

```cpp
void update() {
    object.position.x += object.velocity.x * frameTime;
    object.position.y += object.velocity.y * frameTime;
}
```

Now, every frame, the velocity is multiplied with the time since the last frame. If a lot of time passed 
since the last frame, it moves a lot, and if only little time passed, the object only moves a little bit.
This has the effect that the object will move the same distance every second, no matter how many frames 
are rendered.

The unit of the actual speed of the object now successfully changed from **pixels/frame** to **pixels/second**.

#### Conclusion

Whenever you want steady motion for something, remember to always compensate for time since you can never
be sure at what rate your function is called. The `frameTime` variable is your friend.
