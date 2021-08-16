# 42-dining-philosophers

42 Unix project. Solution of classical synchronization problem about [dining philosophers](https://en.wikipedia.org/wiki/Dining_philosophers_problem) where each philosopher is a thread and mutexes are used to prevent deadlocks.\
The code is written in accordance with The Norm (42 coding style).

⚠️ On slow hardware or if CPU is highly loaded during execution the perfomance may differ form expected one.\
Also the project was written and tested on Mac OS, so the result on others OS may differ as well.

##  usage

In the root of repository run `make` and launch as follows:\
`./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number of meals]`
* *number_of_philosophers* - number of philosophers and forks
* *time_to_die (ms)* - philosopher dies if he doesn't start eating time_to_die after start of his last meal or the beginning of simulation
* *time_to_eat (ms)* and *time_to_sleep (ms)* - how much time does it take for a philosopher to eat and sleep, respectively
* *number of meals* - optional parameter, simulation stops if all philosophers eat at least such amount of times

If *number of meals* isn't specified simulation stops at the death of any philosopher.\
Runing with number of philosophers > 200 and time_to_die or time_to_eat or time_to_sleep less than 60 ms may cause underfined behaviour.

Example test cases:
* 1 800 200 200 - dies, no second fork
* 5 800 200 200 - no one dies, never stops
* 5 800 200 200 7 - stops after each philosopher eat at least 7 times
* 4 410 200 200 - no one dies, never stops
* 4 310 200 100 - stops because of death of one philosopher
* 200 1000 200 200 - no one dies (but depends)

***Makefile***
* *`make`* -- compiles `philo` executable.
* *`clean`* -- deletes object files.
* *`fclean`* -- deletes object files and `philo`.
* *`re`* -- runs `fclean` and recompiles.