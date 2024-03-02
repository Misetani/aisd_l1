#include <gtest/gtest.h>

#include "../list.h"
#include "../array_exception.h"

List<int> populate(int size) {
    List<int> list;
    for (int i = 0; i < size; ++i) {
        list.append(i);
    }

    return list;
}

// add is a name for the group of tests
// and positive is a name for this specific test
TEST(populating_a_list, using_append) {
    List<int> list;
    int size = 10;
    for (int i = 0; i < size; ++i) {
        list.append(i);
    }

    EXPECT_EQ(size, list.get_size());

    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(i, list.get(i));
    }
}

TEST(populating_a_list, using_insert) {
    List<int> list;
    int size = 10;
    for (int i = 0; i < size; ++i) {
        list.insert(i, i);
    }

    EXPECT_EQ(size, list.get_size());

    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(i, list.get(i));
    }

    list.insert(10, 10);
    EXPECT_EQ(11, list.get_size());
    EXPECT_EQ(10, list.get(10));
}

TEST(copying_a_list, using_copy_constructor) {
    List<int> list = populate(10);

    List<int> copy(list);

    EXPECT_EQ(list.get_size(), copy.get_size());

    for (int i = 0; i < list.get_size(); ++i) {
        EXPECT_EQ(list.get(i), copy.get(i));
    }
}

TEST(clearing_a_list, using_clear) {
    List<int> list = populate(10);

    list.clear();

    EXPECT_EQ(0, list.get_size());

    EXPECT_THROW(list.get(0), Array_exception);
}

TEST(checking_a_list, using_is_empty) {
    List<int> list = populate(10);

    EXPECT_FALSE(list.is_empty());

    list.clear();

    EXPECT_TRUE(list.is_empty());
}

TEST(checking_a_list, using_contains) {
    List<int> list = populate(10);

    EXPECT_TRUE(list.contains(5));
    EXPECT_FALSE(list.contains(10));
    EXPECT_FALSE(list.contains(-1));
    EXPECT_FALSE(list.contains(100));
}

TEST(getting_a_value, using_get) {
    List<int> list = populate(10);

    EXPECT_EQ(5, list.get(5));
    EXPECT_EQ(0, list.get(0));
    EXPECT_EQ(9, list.get(9));
    EXPECT_THROW(list.get(10), Array_exception);
}

TEST(setting_a_value, using_set) {
    List<int> list = populate(10);

    EXPECT_TRUE(list.set(5, 10));
    EXPECT_EQ(10, list.get(5));

    EXPECT_FALSE(list.set(10, 10));
    EXPECT_FALSE(list.set(-1, 10));

    EXPECT_EQ(0, list.get(0));

    EXPECT_EQ(9, list.get(9));
}

TEST(getting_a_position, using_index_of) {
    List<int> list = populate(10);

    EXPECT_EQ(5, list.index_of(5));
    EXPECT_EQ(0, list.index_of(0));
    EXPECT_EQ(9, list.index_of(9));
    EXPECT_EQ(-1, list.index_of(10));
    EXPECT_EQ(-1, list.index_of(-1));
}

TEST(removing_elements, using_remove) {
    List<int> list = populate(10);

    EXPECT_TRUE(list.remove(5));
    EXPECT_EQ(9, list.get_size());

    EXPECT_TRUE(list.remove(0));
    EXPECT_EQ(8, list.get_size());

    EXPECT_TRUE(list.remove(9));
    EXPECT_EQ(7, list.get_size());

    EXPECT_FALSE(list.remove(10));
    EXPECT_EQ(7, list.get_size());

    EXPECT_FALSE(list.remove(-1));
    EXPECT_EQ(7, list.get_size());
}

TEST(removing_elements, using_remove_at) {
    List<int> list = populate(10);

    EXPECT_TRUE(list.remove_at(5));
    EXPECT_EQ(9, list.get_size());

    EXPECT_TRUE(list.remove_at(0));
    EXPECT_EQ(8, list.get_size());

    EXPECT_FALSE(list.remove_at(9));
    EXPECT_EQ(8, list.get_size());

    EXPECT_TRUE(list.remove_at(7));
    EXPECT_EQ(7, list.get_size());

    EXPECT_FALSE(list.remove_at(7));
    EXPECT_EQ(7, list.get_size());

    EXPECT_FALSE(list.remove_at(-1));
    EXPECT_EQ(7, list.get_size());

    EXPECT_FALSE(list.remove_at(10));
    EXPECT_EQ(7, list.get_size());
}

TEST(error_handling, get_index_out_of_bounds) {
    List<int> list = populate(10);

    EXPECT_THROW(list.get(-1), Array_exception);
    EXPECT_THROW(list.get(10), Array_exception);
}

TEST(error_handling, insert_index_out_of_bounds) {
    List<int> list = populate(10);

    EXPECT_FALSE(list.insert(-1, 10));
    EXPECT_FALSE(list.insert(11, 10));
}

TEST(iterator_tests, using_begin_and_end) {
    List<int> list = populate(10);

    List<int>::Iterator it = list.begin();
    List<int>::Iterator end = list.end();

    int i = 0;
    while (it != end) {
        EXPECT_EQ(*it, list.get(i));
        ++it;
        ++i;
    }
}

TEST(iterator_tests, using_begin_and_end2) {
    List<int> list = populate(10);

    List<int>::Iterator it = list.begin();
    List<int>::Iterator end = list.end();

    int i = 0;
    while (true) {
        if (it == end) {
            break;
        }

        EXPECT_EQ(*it, list.get(i));
        ++it;
        ++i;
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}