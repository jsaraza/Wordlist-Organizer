// a1_main.cpp

//
// You can change this file in any way you like.
//
// Thoroughly test your Wordlist class to make sure it is correct.
//

#include "Wordlist.h"
#include "test.h"

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

void test_Wordlist()
{
    Test("test_Wordlist");

    Wordlist lst;
    assert(!lst.is_frozen());
    assert(lst.length() == 0);
    assert(!lst.contains("hello"));

    lst.add_word("hello");
    lst.add_word("test");
    lst.add_word("yes");

    assert(lst.length() == 3);

    assert(lst.contains("hello"));
    assert(lst.contains("test"));
    assert(lst.contains("yes"));

    lst.add_word("hello");

    assert(lst.length() == 3);

    lst.remove_word("beeeeeep");

    assert(lst.length() == 3);

    assert(lst.get_word(0) == "hello");
    assert(lst.get_word(1) == "test");
    assert(lst.get_word(2) == "yes");

    assert(lst.first_word() == "hello");
    assert(lst.last_word() == "yes");

    lst.remove_word("hello");

    assert(lst.length() == 2);
    assert(!lst.contains("hello"));

    assert(lst.first_word() == "test");
    assert(lst.last_word() == "yes");

    lst.add_word("apple");
    lst.add_word("bear");

    vector<string *> v = lst.get_sorted_index();

    assert(lst.is_frozen());

    vector<string> vCopy;

    for (string *s : v)
    {
        vCopy.push_back(*s);
    }

    sort(vCopy.begin(), vCopy.end());

    for (int i = 0; i < v.size(); i++)
    {
        assert(*v.at(i) == vCopy.at(i));
    }

    cout << "All Done!" << endl;

    //
    // Add more test cases here. Use assert or if-statements to automatically
    // check the correctness of your code.
    //

} // test_Wordlist

int main()
{
    test_Wordlist();
    // read_from_terminal();
}
