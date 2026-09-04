# Philosophers

[![Build](https://github.com/C1STA/philosophers/actions/workflows/build.yml/badge.svg?branch=main)](https://github.com/C1STA/philosophers/actions/workflows/build.yml)

A multithreaded simulation of the dining philosophers problem, written in C
with POSIX threads and mutexes.

Philosophers is a concurrency project from the 42 curriculum. Each philosopher
alternates between eating, sleeping, and thinking while sharing a limited set
of forks. The simulation must avoid deadlocks, detect starvation precisely, and
stop without producing messages after a death.

## Concurrency model

Each philosopher runs in its own thread. A dedicated supervisor thread observes
the time of the last meal and the optional meal quota.

- Each fork is protected by its own mutex.
- Odd and even philosophers acquire forks in opposite orders, breaking the
  circular-wait condition that can cause a deadlock.
- Each philosopher owns a meal mutex protecting its last-meal timestamp and
  completed-meal counter.
- A shared stop mutex synchronizes the simulation state.
- A print mutex serializes output and prevents state messages after a death.
- All threads wait for a shared start timestamp before entering the simulation.

## Build and run

```bash
make -C philo
./philo/philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meal_quota]
```

Times are expressed in milliseconds and every argument must be a strictly
positive integer. The optional final argument stops the simulation once every
philosopher has eaten at least that many times.

Example with five philosophers and a meal quota:

```bash
./philo/philo 5 800 200 200 5
```

Example in which starvation is expected:

```bash
./philo/philo 4 310 200 200
```

Each output line contains the elapsed time, the one-based philosopher ID, and
the new state:

```text
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
```

## Validation

The GitHub Actions workflow builds with `-Wall -Wextra -Werror`, checks invalid
input handling, and runs representative single-philosopher, starvation, and
meal-quota scenarios.

Useful local checks:

```bash
valgrind --leak-check=full ./philo/philo 5 800 200 200 5
valgrind --tool=helgrind ./philo/philo 5 800 200 200 5
```

The exact version submitted to 42 is available through the `42-submission` tag.
