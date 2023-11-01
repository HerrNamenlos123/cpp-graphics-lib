# Programming concepts

This section of the cppgfx documentation contains many code example with the intention
of teaching you how to do certain things. When learning programming, you will at one point
encounter many of these problems and even if you don't, it's worth it to read through
them to get a better understanding of what is happening.

This document tries to teach you programming concepts, and solutions using modern C++.  
Many of the proposed solutions are not applicable if you program using plain C and you
will have to write the algorithms by hand.

## Table of Contents

 - [Console prints and String formatting](#console-prints-and-string-formatting)
 - [Data structures and algorithms](#data-structures-and-algorithms)
   - [Iterating over arrays](#iterating-over-arrays) 
   - [Removing multiple elements from an array](#removing-multiple-elements-from-an-array)
 - [Objects in Motion](#objects-in-motion)
   - [Continuous motion](#continuous-motion)

## Console prints and String formatting

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

cppgfx uses spdlog, which in turn uses [fmt](https://github.com/fmtlib/fmt) under the hood. fmt is a string formatting library that 
implement Python-like string formatting. 

To find out how to format something, google how to do it in Python. The syntax is equivalent.

cppgfx provides the `print()` and `println()` functions, which will print formatted string to the console.
`print()` will only print the formatted string and `println()` will additionally print a new-line character
in order to move into the next line.

Example:
```cpp
print("Hello world!");      
// -> "Hello world!"

print("Hello {}", 5);       
// -> "Hello 5"

print("{} loves using {} {} times a week", "Tom", "cppgfx", 5);       
// -> "Tom loves using cppgfx 5 times a week"

print("{}/{} is {}, but {}/{} is {}, because of integer division", 7.0, 2.0, 7.0/2.0, 7, 2, 7/2);
// -> "7.0/2.0 is 3.5, but 7/2 is {}, because of integer division"

float height = 50.2f;
int count = 128;
std::string message = "Hello";
print("Height = {}, count = {}, message = {}", height, count, message);
// -> "Height = 50.2, count = 128, message = Hello"

float pi = 3.1415926535f;
print("For me, pi is {:.02f}", pi);     // Number of digits after floating point
// -> "For me, pi is 3.14"

int hexValue = 0x03A9;
print("The value is {}", hexValue); 
// -> "The value is 937"
print("The value is {:x}", hexValue); 
// -> "The value is 3a9"
print("The value is {:X}", hexValue); 
// -> "The value is 3A9"
print("The value is {:06X}", hexValue); 
// -> "The value is 0003A9"
print("The value is 0x{:04X}", hexValue); 
// -> "The value is 0x03A9"
```

To find out how to format something, google how to do it in Python. The syntax is equivalent.
[Here is the original fmt documentation](https://fmt.dev/latest/api.html), but it is not so easy to read.

One last thing to note is that everything you can do with the print functions, can also be done
with `fmt::format()`, which is the function behind print. The difference is it returns the formatted
string instead of printing to the console.

```cpp
std::string date = fmt::format("{:02}.{:02}.{:04}", day(), month(), year());
// Example -> date = "01.10.2023"
println("The date is {}", date);
```

## Data structures and algorithms

### Iterating over arrays

This is as easy as it sounds. Here is the simplest method:

```cpp
std::vector<int> array = { 5, -6, 87, -12, 65 };

for (int i = 0; i < array.size(); i++) {
    println("[{}] = {}", i, array[i]);
}
```

### Removing multiple elements from an array

Be careful! Removing multiple elements from an array sounds very trivial, but the devil is in the details.

#### Problem

Say you have a vector of objects and you want to remove all objects that match a certain condition. For example,
you have an array of cars, and you want to remove all cars that have less than 100Hp. Easy, right?

```cpp
std::vector<Car> cars = { Car(120), Car(80), Car(67), Car(150), Car(90) };
for (size_t i = 0; i < cars.size(); i++) {
    if (cars[i].horsepower < 100) {
        cars.erase(cars.begin() + i);
    }
}
```

`array.erase(array.begin() + index)` can be used to remove an element from an array.

This loop has a significant flaw. The issue is that we are iterating over a container while
modifying it. In this example, the first car is stronger, so we keep it. Now i is 1 (the second car), 
and it is weak, so we remove it. But now the third car shifts forward in place of the second car, leaving 
the array at length 4. Next, we look at the third car, which has 150Hp since it was shifted forwards. See, 
the third car was missed. But even worse when we look at the fourth car, we remove it too, and when we try
to look at the fifth car (since the length was originally five), we get an out of bounds error since the
array is only 3 elements long anymore.

This is why you should never modify a container while iterating over it.

#### Solution

One possible solution is to additionally move the index back to the front:

```cpp
std::vector<Car> cars = { Car(120), Car(80), Car(67), Car(150), Car(90) };
for (size_t i = 0; i < cars.size(); i++) {
    if (cars[i].horsepower < 100) {
        cars.erase(cars.begin() + i);
        i--;  // We just removed a car, so we also need to go a step back to not miss a car
    }
}
```

This solves the issue.

Another way using modern C++ functions:

```cpp
std::vector<Car> cars = { Car(120), Car(80), Car(67), Car(150), Car(90) };
cars.erase(std::remove_if(cars.begin(), cars.end(), [](Car& car) { return car.horsepower < 100; }), cars.end());
```

This is very advanced and you should only use if you understand it. What happens is that we call
`std::remove_if`, which takes the iterator `cars.begin()`, which is a pointer to the beginning of the array,
and `cars.end()`, which is a pointer to the end of the array. Lastly, it takes in a lambda function, which
is called for every element in the array. You must return true if you want to remove the element, and false
if you want to keep it. At the very end, we call `cars.erase` which takes the result of `std::remove_if` and
the iterator `cars.end()` which is a pointer to the end of the array.

```cpp
std::vector<Car> cars = { Car(120), Car(80), Car(67), Car(150), Car(90) };

cars.erase(     // This function erases the elements if we tell it how
        std::remove_if(     // This defines which elements to remove
                cars.begin(), // An iterator which points to the beginning of the array
                cars.end(),   // An iterator which points to the element one past the end of the array
                [](Car& car) {  // And an inline lambda function, which takes a reference to a Car as a parameter
                    return car.horsepower < 100;    // And returns a boolean, whether to remove this element or not 
                }               // This lambda is called for every element that is checked
        ), 
        cars.end()
);
```

This function does all of this index-shifting internally and we do not need to care about it. We can
elevate our level of problem-solving to another level by not specifying WHAT to do and HOW to remove 
elements, instead we only provide a condition and the rest is done automatically.

## Objects in motion

### Continuous motion

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
