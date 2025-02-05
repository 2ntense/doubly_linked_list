#include <check.h>
#include "../src/linkedlist.h"

START_TEST(test_dll_new_list)
{
    list_t *test_list;
    test_list = dll_new_list();

    ck_assert_int_eq(test_list->size, 0);
    ck_assert_ptr_eq(test_list->head, NULL);
    ck_assert_ptr_eq(test_list->tail, NULL);

    dll_free_list(test_list);
}
END_TEST

START_TEST(test_dll_new_node)
{
    node_t *test_node;
    test_node = dll_new_node(111, NULL, NULL);

    ck_assert_int_eq(test_node->data, 111);
    ck_assert_ptr_eq(test_node->next, NULL);
    ck_assert_ptr_eq(test_node->prev, NULL);

    dll_free_node(test_node);
}
END_TEST

START_TEST(test_dll_is_empty)
{
    list_t *test_list;
    test_list = dll_new_list();

    int is_empty = dll_is_empty(test_list);
    ck_assert_int_eq(is_empty, 1);

    dll_append(0, test_list);
    is_empty = dll_is_empty(test_list);
    ck_assert_int_eq(is_empty, 0);

    dll_clear(test_list);
    is_empty = dll_is_empty(test_list);
    ck_assert_int_eq(is_empty, 1);

    dll_free_list(test_list);
}
END_TEST

START_TEST(test_dll_push)
{
    list_t *test_list;
    test_list = dll_new_list();

    ck_assert_int_eq(test_list->size, 0);
    ck_assert_ptr_eq(test_list->head, NULL);
    ck_assert_ptr_eq(test_list->tail, NULL);

    node_t *first_node = dll_push(111, test_list);
    ck_assert_int_eq(test_list->size, 1);

    dll_push(222, test_list);
    ck_assert_int_eq(test_list->size, 2);

    dll_push(333, test_list);
    ck_assert_int_eq(test_list->size, 3);

    dll_push(444, test_list);
    ck_assert_int_eq(test_list->size, 4);

    node_t *last_node = dll_push(555, test_list);
    ck_assert_int_eq(test_list->size, 5);

    ck_assert_ptr_eq(test_list->head, first_node);
    ck_assert_ptr_eq(test_list->tail, last_node);

    dll_free_list(test_list);
}
END_TEST

START_TEST(test_dll_pop)
{
    list_t *test_list;
    test_list = dll_new_list();

    dll_push(111, test_list);
    dll_push(222, test_list);
    dll_push(333, test_list);
    dll_push(444, test_list);
    dll_push(555, test_list);

    ck_assert_int_eq(test_list->size, 5);

    ck_assert_int_eq(dll_pop(test_list), 555);
    ck_assert_int_eq(test_list->size, 4);

    ck_assert_int_eq(dll_pop(test_list), 444);
    ck_assert_int_eq(test_list->size, 3);

    ck_assert_int_eq(dll_pop(test_list), 333);
    ck_assert_int_eq(test_list->size, 2);

    ck_assert_int_eq(dll_pop(test_list), 222);
    ck_assert_int_eq(test_list->size, 1);

    ck_assert_int_eq(dll_pop(test_list), 111);
    ck_assert_int_eq(test_list->size, 0);

    ck_assert_ptr_eq(test_list->head, NULL);
    ck_assert_ptr_eq(test_list->tail, NULL);

    ck_assert_int_lt(dll_pop(test_list), 0);
    ck_assert_int_lt(dll_pop(test_list), 0);
    ck_assert_int_lt(dll_pop(test_list), 0);

    dll_free_list(test_list);
}
END_TEST

START_TEST(test_dll_clear)
{
    list_t *test_list;
    test_list = dll_new_list();

    ck_assert_int_eq(test_list->size, 0);
    ck_assert_ptr_eq(test_list->head, NULL);
    ck_assert_ptr_eq(test_list->tail, NULL);

    dll_clear(test_list);

    ck_assert_int_eq(test_list->size, 0);
    ck_assert_ptr_eq(test_list->head, NULL);
    ck_assert_ptr_eq(test_list->tail, NULL);

    for (int i = 0; i < 5; i++)
    {
        dll_push(i, test_list);
    }

    ck_assert_int_eq(test_list->size, 5);

    dll_clear(test_list);

    ck_assert_int_eq(test_list->size, 0);
    ck_assert_ptr_eq(test_list->head, NULL);
    ck_assert_ptr_eq(test_list->tail, NULL);

    dll_free_list(test_list);
}
END_TEST

START_TEST(test_dll_prepend)
{
    list_t *test_list;
    test_list = dll_new_list();

    node_t *n0 = dll_prepend(111, test_list);
    ck_assert_ptr_eq(test_list->head, n0);
    ck_assert_ptr_eq(test_list->tail, n0);
    ck_assert_int_eq(test_list->size, 1);
    ck_assert_int_eq(test_list->head->data, 111);
    ck_assert_int_eq(test_list->tail->data, 111);

    node_t *n1 = dll_prepend(222, test_list);
    ck_assert_ptr_eq(test_list->head, n1);
    ck_assert_ptr_eq(test_list->tail, n0);
    ck_assert_int_eq(test_list->size, 2);
    ck_assert_int_eq(test_list->head->data, 222);
    ck_assert_int_eq(test_list->tail->data, 111);

    dll_free_list(test_list);
}
END_TEST

START_TEST(test_dll_insert)
{
    list_t *test_list;
    test_list = dll_new_list();
    ck_assert_ptr_ne(test_list, NULL);

    node_t *n0 = dll_insert(0, 111, test_list);
    ck_assert_ptr_ne(n0, NULL);
    ck_assert_int_eq(test_list->size, 1);
    ck_assert_ptr_eq(test_list->head, n0);
    ck_assert_ptr_eq(test_list->tail, n0);
    ck_assert_int_eq(n0->data, 111);
    ck_assert_ptr_eq(n0->next, NULL);
    ck_assert_ptr_eq(n0->prev, NULL);

    node_t *head_node = dll_insert(0, 222, test_list);
    ck_assert_ptr_eq(test_list->head, head_node);
    ck_assert_ptr_eq(test_list->tail, n0);
    ck_assert_int_eq(test_list->size, 2);
    ck_assert_int_eq(head_node->data, 222);
    ck_assert_ptr_eq(head_node->prev, NULL);
    ck_assert_ptr_eq(head_node->next, n0);
    ck_assert_int_eq(n0->data, 111);
    ck_assert_ptr_eq(n0->prev, head_node);
    ck_assert_ptr_eq(n0->next, NULL);

    node_t *n1 = dll_insert(1, 333, test_list);
    ck_assert_int_eq(test_list->size, 3);
    ck_assert_ptr_eq(test_list->head, head_node);
    ck_assert_ptr_eq(test_list->tail, n0);
    ck_assert_int_eq(head_node->data, 222);
    ck_assert_ptr_eq(head_node->prev, NULL);
    ck_assert_ptr_eq(head_node->next, n1);
    ck_assert_int_eq(n0->data, 111);
    ck_assert_ptr_eq(n0->prev, n1);
    ck_assert_ptr_eq(n0->next, NULL);
    ck_assert_int_eq(n1->data, 333);
    ck_assert_ptr_eq(n1->next, n0);
    ck_assert_ptr_eq(n1->prev, head_node);

    node_t *tail_node = dll_insert(3, 444, test_list);
    ck_assert_int_eq(test_list->size, 4);
    ck_assert_ptr_eq(test_list->head, head_node);
    ck_assert_ptr_eq(test_list->tail, tail_node);
    ck_assert_int_eq(head_node->data, 222);
    ck_assert_ptr_eq(head_node->prev, NULL);
    ck_assert_ptr_eq(head_node->next, n1);
    ck_assert_int_eq(n0->data, 111);
    ck_assert_ptr_eq(n0->prev, n1);
    ck_assert_ptr_eq(n0->next, tail_node);
    ck_assert_int_eq(n1->data, 333);
    ck_assert_ptr_eq(n1->next, n0);
    ck_assert_ptr_eq(n1->prev, head_node);
    ck_assert_int_eq(tail_node->data, 444);
    ck_assert_ptr_eq(tail_node->next, NULL);
    ck_assert_ptr_eq(tail_node->prev, n0);

    dll_free_list(test_list);
}
END_TEST

START_TEST(test_dll_contains)
{
    list_t *test_list;
    test_list = dll_new_list();

    int contains = dll_contains(0, test_list);
    ck_assert_int_eq(contains, INT_MIN);

    dll_append(0, test_list);
    contains = dll_contains(0, test_list);
    ck_assert_int_eq(contains, 0);

    dll_append(1, test_list);
    contains = dll_contains(0, test_list);
    ck_assert_int_eq(contains, 0);

    contains = dll_contains(1, test_list);
    ck_assert_int_eq(contains, 1);

    contains = dll_contains(2, test_list);
    ck_assert_int_eq(contains, INT_MIN);

    dll_free_list(test_list);
}
END_TEST

START_TEST(test_dll_get)
{
    list_t *test_list;
    test_list = dll_new_list();

    int res = dll_get(0, test_list);
    ck_assert_int_eq(res, INT_MIN);
    res = dll_get(1, test_list);
    ck_assert_int_eq(res, INT_MIN);

    dll_append(111, test_list);
    dll_append(222, test_list);
    dll_append(333, test_list);
    dll_append(444, test_list);
    dll_append(555, test_list);

    res = dll_get(0, test_list);
    ck_assert_int_eq(res, 111);

    res = dll_get(1, test_list);
    ck_assert_int_eq(res, 222);

    res = dll_get(4, test_list);
    ck_assert_int_eq(res, 555);

    res = dll_get(5, test_list);
    ck_assert_int_eq(res, INT_MIN);

    dll_free_list(test_list);
}
END_TEST

START_TEST(test_dll_get_first)
{
    list_t *test_list;
    test_list = dll_new_list();

    int res = dll_get_first(test_list);
    ck_assert_int_eq(res, INT_MIN);

    dll_append(111, test_list);
    res = dll_get_first(test_list);
    ck_assert_int_eq(res, 111);

    dll_append(222, test_list);
    res = dll_get_first(test_list);
    ck_assert_int_eq(res, 111);

    dll_prepend(333, test_list);
    res = dll_get_first(test_list);
    ck_assert_int_eq(res, 333);

    dll_free_list(test_list);
}
END_TEST

START_TEST(test_dll_get_last)
{
    list_t *test_list;
    test_list = dll_new_list();

    int res = dll_get_last(test_list);
    ck_assert_int_eq(res, INT_MIN);

    dll_append(111, test_list);
    res = dll_get_last(test_list);
    ck_assert_int_eq(res, 111);

    dll_append(222, test_list);
    res = dll_get_last(test_list);
    ck_assert_int_eq(res, 222);

    dll_prepend(333, test_list);
    res = dll_get_last(test_list);
    ck_assert_int_eq(res, 222);

    dll_free_list(test_list);
}
END_TEST

Suite *linkedlist_suite()
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Linked List");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_dll_new_list);
    tcase_add_test(tc_core, test_dll_new_node);
    tcase_add_test(tc_core, test_dll_is_empty);
    tcase_add_test(tc_core, test_dll_get);
    tcase_add_test(tc_core, test_dll_get_first);
    tcase_add_test(tc_core, test_dll_get_last);
    tcase_add_test(tc_core, test_dll_push);
    tcase_add_test(tc_core, test_dll_pop);
    tcase_add_test(tc_core, test_dll_clear);
    tcase_add_test(tc_core, test_dll_prepend);
    tcase_add_test(tc_core, test_dll_insert);
    tcase_add_test(tc_core, test_dll_contains);

    suite_add_tcase(s, tc_core);

    return s;
}

int main()
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = linkedlist_suite();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}