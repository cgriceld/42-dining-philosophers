# 42-dining-philosophers

42 Unix project. Solution of classical synchronization problem about [dining philosophers](https://en.wikipedia.org/wiki/Dining_philosophers_problem) where each philosopher is a thread and mutexes are used to prevent deadlocks.

Runing with number of philosophers more than 200 is underfined behaviour.

Example test cases:
* 1 800 200 200 - dies, no second fork
* 5 800 200 200 - no one dies, never stops
* 5 800 200 200 7 - stops after each philosopher eat at least 7 times
* 4 410 200 200 - no one dies, never stops
* 4 310 200 100 - stops because of death of one philosopher