# ft_containers

42 project, the implementation of templated classes that behave exactly like the C++ 98 STL containers.

## Final grade : 125/125

Mandatory part : 100/100

Bonus : 25/25

### The containers

The project includes the following containers :

- Vector
- List
- Map
- Stack
- Queue
- Deque (bonus)
- Multimap (bonus)
- Set (bonus)
- Multiset (bonus)

### How to use it

The containers are templated, meaning you can use them with any type, just like you would any other STL containers. Just include the .hpp corresponding to the container you want to use, and use it!

The difference is the namespace ; where you would call ``std::vector<T>``, you now call ``ft::vector<T>``.

### Testers

The testers available in the repository :

- [mli's containers_test](https://github.com/mli42/containers_test) (very useful, much recommended), to which I contributed by adding the tests for deque, multimap, set and multiset (you can find them on his repo)

- [mazoise / hbaudet's FT_CONTAINERS_TESTER](https://github.com/Mazoise/FT_CONTAINERS_TESTER)

- [llefranc / hherin's 42_Containator](https://github.com/llefranc/42_Containator)
