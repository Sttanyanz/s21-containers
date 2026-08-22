# s21-containers
Implementation of the s21_containers.h. library.

### Part Information

Library implements containers `list`, `map`, `queue`, `set`, `stack`, `vector`, `array`, `multiset`.

Additionally, next functions are implemented:

| Modifiers      | Definition                                      | Containers |
|----------------|-------------------------------------------------| -------------------------------------------|
| `iterator insert_many(const_iterator pos, Args&&... args)`          | Inserts new elements into the container directly before `pos`.  | List, Vector. |
| `void insert_many_back(Args&&... args)`          | Appends new elements to the end of the container.  | List, Vector, Queue, Stack. |
| `void insert_many_front(Args&&... args)`          | Appends new elements to the top of the container.  | List. |
| `vector<std::pair<iterator,bool>> insert_many(Args&&... args)`          | Inserts new elements into the container.  | Map, Set, Multiset. |

## Makefile

The project includes a Makefile with the following targets:

| Target | Description |
|--------|-------------|
| `all` | Builds the library and tests (default target). |
| `s21_containers.a` | Builds the static library `s21_containers.a` from source files. |
| `test` | Builds and runs unit tests to verify functionality. |
| `gcov_report` | Builds tests with coverage flags (`--coverage`), runs them, and generates an HTML coverage report via `lcov`/`genhtml` in the `report/` directory. |
| `clean` | Removes all object files, libraries, test executables, coverage files, and generated reports. |
