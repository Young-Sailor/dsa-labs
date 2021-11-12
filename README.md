# Лабораторные работы по дисциплине «Структуры и алгоритмы обработки данных»
## Бинарные деревья поиска. Хеш-таблицы.
### Постановка задачи
Требуется реализовать на языке **C** две библиотеки для работы с бинарным деревом
поиска (**binary search tree**) и хеш-таблицей (**hash table**). В обоих случаях ключом является
строка (**char[]**), а значением — целое число (**uint32_t**).
Функции для работы с бинарным деревом поиска должны быть помещены в файлы
**bstree.c** (реализация функций) и **bstree.h** (объявление функций). В файлах необходимо реализовать следующие функции:
```
struct bstree *bstree_create(char *key, int value)
void bstree_add(struct bstree *tree, char *key, int value)
struct bstree *bstree_lookup(struct bstree *tree, char *key)
struct bstree *bstree_delete(struct bstree *tree, char *key)
struct bstree *bstree_min(struct bstree *tree)
struct bstree *bstree_max(struct bstree *tree)
```
Функции для работы с хеш-таблицей должны быть помещены в файлы **hashtab.c** (реализация функций) и **hashtab.h** (объявление функций). В файлах необходимо реализовать
следующие функции:
```
unsigned int hashtab_hash(char *key)
void hashtab_init(struct listnode **hashtab)
void hashtab_add(struct listnode **hashtab, char *key, int value)
struct listnode *hashtab_lookup(struct listnode **hashtab, char *key)
void hashtab_delete(struct listnode **hashtab, char *key)
```
Целью работы является проведение экспериментального исследования эффективности бинарных деревьев поиска и хеш-таблиц. Результат выполнения работы — реализованные функции для работы с бинарным деревом поиска и хеш-таблицей, выполненные согласно распределению заданий эксперименты, заполненные таблицы и построенные графики.
### Экспериментальное исследование. Сравнение эффективности поиска элементов в бинарном дереве поиска и хеш-таблице в среднем случае (average case)
Требуется заполнить [таблицу](https://docs.google.com/spreadsheets/d/1k1Q3OJrL5WEunr1aYhx9qpdH80Rpf4RWjfAPlhxHvh0/edit?usp=sharing) и построить графики зависимости времени t выполнения операции поиска (**lookup**) элемента в бинарном дереве поиска и хеш-таблице от числа n элементов, добавленных в словарь.
Для создания набора ключей можно использовать любой текстовый файл с большим числом слов. Скрипт, преобразующий текстовый файл в упорядоченный список уникальных слов, представлен в репозитории в папке **scripts**. В качестве искомого ключа следует выбирать случайное слово, которое уже было добавлено в словарь.
Для поиска в словаре случайного слова, уже добавленного туда, можно заранее загрузить слова из исходного текстового файла в массив или связный список.
## Самобалансирующиеся деревья поиска. АВЛ-деревья (AVL trees).
### Задание на работу
Реализовать функции для работы с АВЛ-деревьями (**AVL trees**):
```
struct avltree *avltree_add(struct avltree *root, int key, char *value)
struct avltree *avltree_lookup(struct avltree *root, int key)
struct avltree *avltree_delete(struct avltree *root, int key)
struct avltree *avltree_min(struct avltree *root)
struct avltree *avltree_max(struct avltree *root)
void avltree_free(struct avltree *root)
void avltree_print_dfs(struct avltree *root, int level)
```
Вставить в АВЛ-дерево ~50000 элементов, заранее отсортированных в порядке возрастания/убывания. Используя функцию **avltree_lookup**, продемонстрировать логарифмическую зависимость
высоты дерева от количества добавленных в него узлов ([построить график](https://docs.google.com/spreadsheets/d/1ayLNHlFXmYQaVEilcPmVGEpLRbw--hm-lhpjLAT__GE/edit?usp=sharing)). Продемонстрировать алгоритм удаления узлов из дерева. Описать алгоритмы поворотов АВЛ-дерева. Доказать утверждение о высоте АВЛ-дерева.
## Фибоначчиевы кучи.
### Задание на работу
Реализовать функции для работы с фибоначчиевыми кучами (**Fibonacci heaps**):
```
struct fibheap *fibheap_insert(struct fibheap *heap, int key, char *value)
struct fibheap *fibheap_min(struct fibheap *heap)
struct fibheap *fibheap_union(struct fibheap *heap1, struct fibheap *heap2)
struct fibheap *fibheap_delete_min(struct fibheap *heap)
struct fibheap *fibheap_decrease_key(struct fibheap *heap, struct fibheap *node, int newkey)
struct fibheap *fibheap_delete(struct fibheap *heap, int key)
```
