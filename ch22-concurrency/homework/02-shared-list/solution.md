## Solution: Shared list

Each `push_back` is wrapped in its own `lock_guard`, so the lock is held only while the vector is changed. Both threads take the same mutex, so the vector never sees two changes at once. Without the lock, two `push_back` calls can overlap, and an element or the size can be lost, which is the data race from the mutexes step.

The order of the values depends on which thread gets the lock first, so the vector can hold 1, 6, 2, 7, and so on in any interleaving. The size and the sum don't depend on that order. Every value is added exactly once, so the size is 10 and the sum is 55 every time.

The sum is computed after both joins, in `main` alone, so it doesn't need the lock. That's the same reasoning as the split-sum exercise: once the threads have finished, nothing else changes the vector.

For the first extension, sorting after the joins is safe without the lock, because no other thread is running. Calling `std::sort` on the vector while a thread could still change it would be a race again. The rule is that shared data is safe to use without a lock only when no thread can change it.

For the second extension, a race on `push_back` can corrupt the vector's internal bookkeeping, so the size may be wrong, or the program may crash. The program often appears to work, because the threads usually take turns by chance. That's why a race is a bug even when testing doesn't reveal it.
