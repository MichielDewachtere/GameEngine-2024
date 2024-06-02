# Real Engine

Real Engine consists of two projects, RealCore and Real2D. RealCore contains all the core functionalities such as input handling, scene management, etc., while Real2D contains everything related to 2D graphics.

The engine utilizes various design patterns as described in the book [Game Programming Patterns by Robert Nystrom](https://gameprogrammingpatterns.com), such as the Component Pattern, Command Pattern, and many more. Let's explore some of them.

## Components

To create an object in the engine, you need to create a game object in the scene. That game object can be enhanced with components, which add logic to the object. RealCore and Real2D provide several base components, like a transform component, sprite component, text component, and so on. These engine components are initialized with a struct that can be customized further. A component either derives from the class `Component` or `DrawableComponent`. The latter has a render function that is called by the renderer.

## Commands

The input manager uses the Command Pattern. To create an action bound to input, an input map is needed where different commands can be added, either bound to gamepad input and/or mouse/keyboard input. These commands can be derived from the base `Command` class or the `GameObjectCommand` class, which requires an extra argument, the game object to which the command needs to be bound. For example, a move command can be bound to the player game object.

## Observer

A class can have a subject as a public variable of a custom type. This subject can notify all listeners. To add a component or any other object as a listener, it has to derive from `Observer` of the same type as the subject. Then, the object needs to call the `subject<T>::AddObserver` function to add itself as an observer. Don't forget to remove it when necessary. This pattern is very handy and is used in different places throughout the engine. For example, the scene manager sends a notification when a new scene is either loaded or exited, passing the event (loaded/exit) and a pointer to the relevant scene.

## Other Patterns Used

The Dirty Flag Pattern is also used in certain cases. This is mostly used to prevent the update function from executing when nothing has changed. The flag is set to true when something relevant has changed, enabling the update function to operate again.

The Service Locator Pattern is a safe and more flexible alternative to the Singleton Pattern. RealEngine applies this pattern only to the audio system for now. The locator has a pointer to the active audio system, and when something happens or crashes, it always returns a pointer to the null service, which doesn't do anything but prevents the game from crashing. This pattern also makes it easy for the user to add their own audio system if they want to use a different library, for example. It can easily be added to the locator and set as active.
