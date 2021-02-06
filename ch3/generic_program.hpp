#pragma once

// // テンプレート
// template <typename T>
// void selection_sort(T data[], int n)
// {
//     for (int i = 0; i < n; ++i)
//     {
//         int min_index = i;
//         for (int j = i; j < n; ++j)
//         {
//             if (data[j] < data[min_index])
//             {
//                 min_index = j;
//             }
//         }
//         T tmp = data[min_index];
//         data[min_index] = data[i];
//         data[i] = tmp;
//     }
// }

// ポインタアクセス
template <typename T>
void selection_sort(T* data, int n)
{
    for (int i = 0; i < n; ++i)
    {
        int min_index = i;
        for (int j = i; j < n; ++j)
        {
            if (*(data + j) < *(data + min_index))
            {
                min_index = j;
            }
        }
        T tmp = *(data + min_index);
        *(data + min_index) = *(data + i);
        *(data + i) = tmp;
    }
}

// ポインタアクセス(完)
template <typename T>
void selection_sort(T* first, T* last)
{
    for (T* p = first; p != last; ++p)
    {
        T* min_pos = p;
        for (T* q = p; q != last; ++q)
        {
            if (*q < *min_pos)
            {
                min_pos = q;
            }
        }
        T tmp = *min_pos;
        *min_pos = *p;
        *p = tmp; // 最小値が代入される
    }
}

// イテレータ化
template <typename Iterator>
void selection_sort(Iterator first, Iterator last)
{
    for (Iterator p = first; first != last; ++p)
    {
        Iterator min_pos = p;
        for (Iterator q = p; q != last; ++q)
        {
            if (*q < *min_pos)
            {
                min_pos = q;
            }
        }
        auto tmp = *min_pos;
        *min_pos = *p;
        *p = tmp;
    }
}

// イテレータ化＋比較関数オブジェクト
template <typename Iterator, typename Compare>
void selection_sort(Iterator first, Iterator last, Compare comp)
{
    for (Iterator p = first; p != last; ++p)
    {
        Iterator min_pos = p;
        for (Iterator q = p; q != last; ++q)
        {
            if (comp(*q, *min_pos))
            {
                min_pos = q;
            }
        }
        auto tmp = *min_pos;
        *min_pos = *p;
        *p = tmp;
    }
}