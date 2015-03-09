#include <iostream>

#include "merge_sort.h"

void traverse(int a[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        std::cout << a[i] << " ";
    }

    std::cout << std::endl;
}

int main()
{
    int a[] = { 4, 1, 6, 3, 9, 2 , 7};
    int n = sizeof(a) / sizeof(int);

    std::cout << "src data : " << std::endl;
    traverse(a, n);

    merge_sort_recursive(a, n);
    std::cout << "meger sort recursive data : " << std::endl;
    traverse(a, n);

    int b[] = { 4, 11, 6, 3, 9, 2 , 7};
    std::cout << "src data : " << std::endl;
    traverse(b, n);

    merge_sort_iterator(b, n);
    std::cout << "meger sort iterator sort data : " << std::endl;
    traverse(b, n);
}
