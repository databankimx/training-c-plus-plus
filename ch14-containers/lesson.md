## Ch14 · Containers

Arrays hold a fixed number of values, and most programs need something more flexible. This chapter covers the standard containers that store collections: vectors, which grow and keep their order, and maps, which find values by key. It ends with the choice between them, and a look at the hash table behind the unordered map.

The steps are:

* [Vectors](#goto/01-vectors): growing a list with `push_back`, reading elements safely with `at`, and looping over a vector.
* [Maps](#goto/02-maps): storing values under keys, counting with a map, and why a map's keys are sorted.
* [Unordered maps](#goto/03-unordered-maps): the hash table behind `std::unordered_map`, and what it gives up in exchange for speed.
* [Choosing a container](#goto/04-choosing-containers): comparing arrays, vectors, and maps, and how a program can use several at once.
* [Summary](#goto/05-summary): a recap of the chapter and a short quiz. The homework is listed under the chapter.

---

*The explanations in this chapter are new. The tutorial does not cover the standard containers.*
