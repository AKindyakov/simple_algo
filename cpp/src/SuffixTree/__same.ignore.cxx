#pragma once
#include <vector>
#include <climits>
 
const int CHAR_CODE_LIMIT = 256;
const int INFINITY = INT_MAX / 2; // +бесконечность. Используется как последний символ строки.
 
struct _suffix_tree_node;
struct _suffix_tree_edge {
    _suffix_tree_node *from, *to;
    int start_pos, end_pos;
    char first_char;
};

// Мы храним рёбра в массиве т.к. это немного упрощает код и увеличивает
// быстродействие,
// // но для экономии памяти можно хранить их в map<char, _suffix_tree_edge>

struct _suffix_tree_node {
    _suffix_tree_node *suffix_link;
    _suffix_tree_edge edges[CHAR_CODE_LIMIT], parent_edge;
    _suffix_tree_node();
};
 
struct _suffix_tree_position {
    _suffix_tree_edge edge;
    int offset;
};
 
class suffix_tree {
protected:
    _suffix_tree_node *joker, *root;
private:
    _suffix_tree_position cur;

    // поиск суффикса строки, соотв. текущей позиции
    _suffix_tree_position get_suffix(_suffix_tree_position position);
    
    // построить новую вершину и суффиксные ссылки
    _suffix_tree_node* split_edge(_suffix_tree_position position);
    void destroy_node(_suffix_tree_node *node);

public:
    std::vector<char> str; // т.к. в текст буквы добавляются динамически
    suffix_tree();  // инициализация
    void add_letter(char ch); // добавить символ в конец текста
    void add_string(char *str); 

    // Наибольший суффикс каждого префикса параметра str, который 
    // встречается в исходном тексте (greatest common suffix)
    std::vector<std::pair<int, int> > gcs(char *str);

    ~suffix_tree();
};

#include "suffix_tree.h"
#include <cassert>
 
_suffix_tree_node::_suffix_tree_node()
{
    for (int i = 0; i < CHAR_CODE_LIMIT; i++)
    {
        edges[i].from = this;
        edges[i].to   = NULL;
        edges[i].start_pos  = -1;
        edges[i].end_pos    = 0;
        edges[i].first_char = i;
    }
}
 
suffix_tree::suffix_tree()
{
    // инициализация
    joker = new _suffix_tree_node;
    root  = new _suffix_tree_node;
    joker->suffix_link = NULL;
    joker->edges[0].to = joker;
    joker->parent_edge = joker->edges[0];
    for (int i = 1; i < CHAR_CODE_LIMIT; i++)
    {
        joker->edges[i].to   = root;
 
    }
    root->parent_edge = joker->edges[1];
    root->suffix_link = joker;
    cur.edge = joker->edges[1];
    cur.offset = 0;
}
 
void suffix_tree::add_letter(char ch) {
    while (true)
    {
        if (cur.edge.end_pos == cur.offset)
        {
            // Находимся в узле
            if (cur.edge.to->edges[ch].to == NULL)
            {
in_a_node:
                // некуда ходить. добавляем лист
                cur.edge.to->edges[ch].to = new _suffix_tree_node;
                cur.edge.to->edges[ch].first_char = ch;
                cur.edge.to->edges[ch].start_pos = str.size();
                cur.edge.to->edges[ch].end_pos   = INFINITY;
                if (cur.edge.from == joker) break;
                cur = get_suffix(cur);
            } else
            {
                // просто ходим по правильному ребру
                cur.edge = cur.edge.to->edges[ch];
                cur.offset = cur.edge.start_pos + 1;
                break;
            }
        } else
        {
            // Мы на ребре
            if (str[cur.offset] == ch)
            {
                // идём дальше
                cur.offset ++;
                break;
            } else
            {
                // создаём вершину...
                _suffix_tree_node *new_node = split_edge(cur);
                cur.edge = new_node->parent_edge;
                // и сводим задачу к уже разобранной
                goto in_a_node;
            }
        }
    }
    str.push_back(ch);
}
 
_suffix_tree_position suffix_tree::get_suffix(_suffix_tree_position position)
{
    _suffix_tree_node *cur = position.edge.from->suffix_link;
    if (cur == NULL)
    {
        // мы в корне
        return position;
    }
    int cur_offset = position.edge.start_pos;
    // опускаемся вниз по дереву ровно столько сколько нужно. одна итерация цикла - спуск по одному ребру.
    while (true)
    {
        _suffix_tree_position res;
        _suffix_tree_edge cur_edge = cur->edges[str[cur_offset]];
        cur_offset += cur_edge.end_pos - cur_edge.start_pos;
        if (cur_offset >= position.offset)
        {
            res.edge = cur_edge;
            res.offset = position.offset - cur_offset + cur_edge.end_pos - cur_edge.start_pos + cur_edge.start_pos;
            return res;
        }
        cur = cur_edge.to;
    }
}
 
_suffix_tree_node* suffix_tree::split_edge(_suffix_tree_position position)
{
    if (position.edge.end_pos == position.offset)
        return position.edge.to;
    // разбиваем ребро на 2
    _suffix_tree_node *new_node = new _suffix_tree_node;
    _suffix_tree_edge new_edge;
    new_edge.start_pos  = position.offset;
    new_edge.end_pos    = position.edge.end_pos;
    new_edge.first_char = str[position.offset];
    new_edge.from       = new_node;
    new_edge.to         = position.edge.to;
    new_node->edges[str[position.offset]] = new_edge;
    position.edge.end_pos = position.offset;
    position.edge.to      = new_node;
    new_node->parent_edge = position.edge.from->edges[position.edge.first_char] = position.edge;
    // строим суффиксную ссылку. Если вершины в нужном месте нет - применяем ту же процедуру.
    new_node->suffix_link = split_edge(get_suffix(position));
    return new_node;
}
 
suffix_tree::~suffix_tree()
{
    delete joker;
    destroy_node(root);
}
 
void suffix_tree::destroy_node(_suffix_tree_node *node)
{
    // удалить узел и всех его потомков
    if (node == NULL) return;
    for (int i = 0; i < CHAR_CODE_LIMIT; i++)
    {
        destroy_node(node->edges[i].to);
    }
    delete node;
}
 
void suffix_tree::add_string(char *str)
{
    while (*str)
    {
        add_letter(*str);
        str++;
    }
}
 
std::vector<std::pair<int, int> > suffix_tree::gcs(char *str)
{
    std::vector<std::pair<int, int> > res;
    int L = strlen(str);
    _suffix_tree_position cur;
    cur.edge = joker->edges[1];
    cur.offset = 0;
    int d = 0; // текущая "глубина"
    for (int i = 0; i < L; i++)
    {
        while (true)
        {
            if (cur.edge.end_pos == cur.offset)
            {
                // мы в вершине
                if (cur.edge.to->edges[str[i]].to != NULL)
                {
                    cur.edge = cur.edge.to->edges[str[i]];
                    cur.offset = cur.edge.start_pos + 1;
                    break;
                }
                if (cur.edge.from == joker)
                {
                    // добрались до корня. особый случай т.к. cur.edge.start_pos не м.б. cur.offset
                                        // следовательно мы не можем находиться в джокере
                    d --;
                    break;
                }
                cur = get_suffix(cur);
                d--;
            }
            else
            {
                // на ребре
                if ((cur.offset >= (int)this->str.size()) || (this->str[cur.offset] != str[i]))
                {
                    cur = get_suffix(cur);
                    d--;
                }
                else
                {
                    cur.offset ++;
                    break;
                }
            }
        }
        d++;
        res.push_back(std::make_pair(d, cur.offset));
    }
    return res;
}

// Пример использования
// Вот такой код может использоваться для решения задачи Анитиплагиат II.
// Единственный недостаток - он не укладывается в ограничение по памяти. 
// Если уменьшить CODE_CHAR_LIMIT до 128 - уже уложится.
#include "suffix_tree.h"
#include <cstdio>
 
char str1[1000000], str2[1000000];
 
int main(void)
{
    suffix_tree tree;
    scanf("%s%s", str1, str2);
    tree.add_string(str1);
    std::vector<std::pair<int, int> > v = tree.gcs(str2);
    int len = (int)v.size();
    int l, n, m;
    l = n = m = 0;
    for (int i = 0; i < len; i++)
    {
        if (v[i].first > l)
        {
            l = v[i].first;
            n = v[i].second - l;
            m = i - l + 1;
        }
    }
    printf("%d %d %d\n", l, n, m);
    return 0;
}
