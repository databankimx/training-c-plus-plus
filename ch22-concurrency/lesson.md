## Ch22 · Concurrency

Modern programs use several processors at once, and threads are how a C++ program puts that work to use. Running work at the same time brings its own hazards: two threads changing the same data can lose updates, and two threads waiting on each other can stop altogether. This chapter covers starting and joining threads, protecting shared data with a mutex, and the habits that keep threaded code correct.

The steps are:

* [Threads](#goto/01-threads): starting a thread with `std::thread`, and waiting for it with `join`.
* [Mutexes](#goto/02-mutexes): protecting shared data with a lock, and `std::lock_guard`.
* [Summary](#goto/03-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*The examples and explanations are new. The thread and mutex types are from the standard library's thread support.*
