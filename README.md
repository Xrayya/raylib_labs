# Raylib Labs

Where I conduct experiments with raylib 

## Arch Idea

### All Event Bus

so for start, there's the loop
-> app own that loop
to regulate the tick, we create universal clock
-> app own that clock
there's an event bus
-> app own that event bus

inside the loop, there's a check
if the delta time has passed the tick elapsed time treshold, it enqueue tick event to event bus

-> event bus' events handling happen after tick check
-> event bus should use queue

-> every component that want to have update based on tick should subscribe to tick event
-> the logic on subscribing should happen on init, so that no weird shit happen during construction
-> imply that components should have on init

there's layers
so there should be a layer stack
-> app own that layer stack

stack rendered using first in first rendered
-> imply that layer should have on render

layer should be able to be manipulated
-> app should own that ability
-> app should be the one that register subscriber about layer manipulation

there should be a way to manipulate layer from other component
-> meaning components should be able to produce event about layer manipulation

there should be a way to add layer in certain position
-> add layer event should have param for position/z-index

there should be a way to remove certain layer
-> remove layer event should have parameter to pin point layer
? what are the params?

if layer can be added and removed, resourced that they use should be carefully managed
-> layer should have on init and on destroy
