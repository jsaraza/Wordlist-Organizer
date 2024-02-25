## Word Lists Organizer

The project is to create a class called `Wordlist` that stores words without any
duplicates. When it's done, you'll be able to add and remove words from it, and
also create an index of all its words in alphabetical order.

`Wordlist` uses a **doubly-linked list** as its underlying representation.
Vectors, arrays, or other container data structures are avoided in this project, except
for one case described below: the method `get_sorted_index()`, which returns a
`vector<string*>`.

## Getting Started

[a1_main.cpp](a1_main.cpp). In `main` you should call the testing code for your
`Wordlist` class.

> **Note** You can download all the files for this assignment in a single .zip
> Click on the green "Code" button, and then click on "Download ZIP".

### Implement the Methods in Wordlist_base

The implementation of `Wordlist` in [Wordlist.h](Wordlist.h). It will
publicly inherit from `Wordlist_base`, and use the `Node` `struct` (given in
`Wordlist`) to implement a doubly-linked list.

[Wordlist.h](Wordlist.h) has the class `Wordlist` where it implements all
the virtual methods listed in the `Wordlist_base` class (in
[Wordlist_base.h](Wordlist_base.h)).

### Implement Constructors, and a Destructor

In addition to the virtual methods listed in `Wordlist_base`, in your `Wordlist`
class there is a _default constructor_ that takes no parameters and creates an
empty `Wordlist` object:

```cpp
//
// Pre-condition:
//     none
// Post-condition:
//     Creates an empty Wordlist object.
// Performance:
//     It should always take a very small, constant amount of time.
//
Wordlist();
```

You would use it like this:

```cpp
Wordlist lst;

// ... lst is an empty Wordlist object ...
```

There is also a _copy constructor_ that takes another `Wordlist` as input, and
initializes the new `Wordlist` to contain copies of all the strings in the other
`Wordlist`.

```cpp
//
// Pre-condition:
//     other is a valid Wordlist object
// Post-condition:
//     Creates a new Wordlist object that is a copy of other; other is not modified
//     in any way, and other and the new object do not share any values. If other
//     is frozen, then the new object is also frozen.
// Performance:
//     The running-time should be proportional to the number of words in other.
//
Wordlist(const Wordlist& other);
```

There is also another constructor that takes the name of a text file as input, and
initializes the list by adding all the words in the file to the list. For
simplicity, you can assume that the file is a text file that always exists:

```cpp
//
// Pre-condition:
//     filename is the name of a text file that exists
// Post-condition:
//     Creates a new Wordlist object that contains all the words in the file
//     filename. If the file contains duplicate words, then the new Wordlist
//     object will contain only one copy of each word.
// Performance:
//     The number of calls to add_word should be proportional to the
//     length of other (or better).
// Note:
//     For this constructor a "word" is defined as the string return by the
//     >> operator. See the read_from_terminal() function for example of how
//     to use >> to read words.
//
Wordlist(const string& filename);
```

Destructor for `Wordlist` that de-allocates all the nodes in the list.
Note that in `Wordlist_base` the destructor is called `~Wordlist_base()`,
and another in `Wordlist` called `~Wordlist()`.

### Frozen and Unfrozen Wordlists

A `Wordlist` is either **frozen** or **unfrozen**. Initially, a `Wordlist` is
_unfrozen_, and any method can be called on it.

When the `get_sorted_index()` method is called, the `Wordlist` automatically
becomes _frozen_. This means that it can no longer be modified: calling
`add_word()` or `remove_word()` on a frozen lists causes them to throw a
`runtime_error` exception. All other methods work the same as on an _unfrozen_
list.

The reason for this feature is that by freezing the list after calling
`get_sorted_index()` we can guarantee that the pointers in the returned vector
are always valid as long as the list still exists.

> **Note** Think about whether or not you
> believe this freezing feature is a good one. Maybe it is too inconvenient, or
> makes some code more complicated to write? But if you don't use freezing, then
> how could you be sure that the pointers in the returned vector are always
> pointing to valid values?

### Testing Code

You can use the `read_from_terminal()` function in [a1_main.cpp](a1_main.cpp) to
help test your code. For example, [small.txt](small.txt) contains:

```
This is
a test
or is this
a test?

```

When you run:

```cpp
// ...

void read_from_terminal()
{
    Wordlist lst;
    string w;
    while (cin >> w)
    {
        lst.add_word(w);
    }

    // print the words in sorted order
    vector<string *> index = lst.get_sorted_index();
    for (int i = 0; i < index.size(); i++)
    {
        cout << (i + 1) << ". " << *index[i] << endl;
    }
}

int main()
{
    read_from_terminal();
}
```

You should get this output:

```
❯ ./a1_main < small.txt
1. This
2. a
3. is
4. or
5. test
6. test?
7. this
```

Notice that _case matters_, e.g. `"This"` and `"this"` count as _different_
words. Also, punctuation _matters_, e.g. `"test"` and `"test?"` are different.

Here's another example using the file [sonnet30.txt](sonnet30.txt):

```bash
❯ ./a1_main < sonnet30.txt
1. All
2. And
3. But
4. For
5. I
6. The
7. Then
8. When
9. Which
10. a
11. account
12. afresh
13. an
14. and
15. are
16. as
17. at
18. before.
19. can
20. cancell’d
21. dateless
22. dear
23. death’s
24. drown
25. end.
26. expense
27. eye,
28. flow,
29. fore-bemoaned
30. foregone,
31. friend,
32. friends
33. from
34. grievances
35. grieve
36. heavily
37. hid
38. if
39. in
40. lack
41. long
42. losses
43. love’s
44. many
45. moan
46. moan,
47. my
48. new
49. night,
50. not
51. of
52. old
53. on
54. o’er
55. paid
56. past,
57. pay
58. precious
59. remembrance
60. restor’d
61. sad
62. sessions
63. sigh
64. sight:
65. silent
66. since
67. sorrows
68. sought,
69. summon
70. sweet
71. tell
72. the
73. thee,
74. thing
75. things
76. think
77. thought
78. time’s
79. to
80. unused
81. up
82. vanish’d
83. wail
84. waste:
85. weep
86. while
87. with
88. woe
89. woe,
90. woes
```

Checking output manually is hard to do with long lists, so here is another handy
trick:

```bash
❯ ./a1_main < sonnet30.txt > sonnet30_sorted_output.txt
```

The expression `> sonnet30_sorted_output.txt` re-directs everything `a1_main`
writes to `cout` into the file
[sonnet30_sorted_output.txt](sonnet30_sorted_output.txt). You can view
[sonnet30_sorted_output.txt](sonnet30_sorted_output.txt) in a text editor, or by
running these commands:

```bash
❯ cat sonnet30_sorted_output.txt
... contents of sonnet30_sorted_output.txt ...

❯ more sonnet30_sorted_output.txt
... contents of sonnet30_sorted_output.txt a page at a time ...
```

Another useful command is `diff fileA fileB`, which finds differences between
text files `fileA` and `fileB`. You can use it to check the output of your
program. For example, if you run [sonnet30.txt](sonnet30.txt) through
`read_from_terminal()` and save the output to `my_sonnet30_sorted_output.txt`,
then you can check your output like this:

```bash
> diff my_sonnet30_sorted_output.txt sonnet30_sorted_output.txt

```

If the files have the same content, then nothing is printed. Otherwise, all
differences are printed.

Here's one more example. The file [tiny_shakespeare.txt](tiny_shakespeare.txt)
has over 200,000 words:

```bash
❯ ./a1_main < tiny_shakespeare.txt > tiny_shakespeare_sorted_output.txt
```

The file
[tiny_shakespeare_sorted_output.txt](tiny_shakespeare_sorted_output.txt) lists
25,670 unique words in alphabetical order.
