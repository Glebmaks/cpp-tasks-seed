#ifndef SORTING_H
#define SORTING_H

#include <iterator>
#include <utility>

#include "collvalue.h"

// Bubble Sort

template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end)
    {
        return;
    }

    for (Iterator last = end; last != begin; --last)
    {
        bool swaped = false;

        for (Iterator it = begin; std::next(it) != last; ++it)
        {
            Iterator next_it = std::next(it);
            if (*next_it < *it)
            {
                using std::swap;
                swap(*it, *next_it);
                swaped = true;
            }
        }

        if (!swaped)
        {
            break;
        }
    }
}

// Quick Sort

template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    if (begin == end || std::next(begin) == end)
    {
        return;
    }

    Iterator left = begin;
    Iterator right = std::prev(end);
    auto pivot = *std::next(begin, std::distance(begin, end) / 2);

    while (left <= right)
    {
        while (*left < pivot)
        {
            ++left;
        }

        while (pivot < *right)
        {
            --right;
        }

        if (left <= right)
        {
            using std::swap;
            swap(*left, *right);
            ++left;

            if (right == begin)
            {
                break;
            }
            --right;
        }
    }

    if (begin < right + 1)
    {
        quick_sort(begin, right + 1);
    }
    if (left < end)
    {
        quick_sort(left, end);
    }
}

#endif // SORTING_H