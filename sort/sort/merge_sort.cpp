#include "merge_sort.h"

static void merge_sort_array(int a[], int first, int mid, int last, int temp[])
{
    int i =  first;
    int j = mid + 1;
    int k = 0;

    while(i <= mid && j <= last)
    {
        if(a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while(i <= mid)
        temp[k++] = a[i++];

    while(j <= last)
        temp[k++] = a[j++];

    for(int i = 0; i < k; ++i)
        a[first + i] = temp[i];
}

static void merge_sort_r(int a[], int first, int last, int temp[])
{
    if(first < last)
    {
        int mid = (first + last) / 2;
        merge_sort_r(a, first, mid, temp);
        merge_sort_r(a, mid + 1, last, temp);
        merge_sort_array(a, first, mid, last, temp);
    }
}

bool merge_sort_recursive(int a[], int n)
{
    int *p = new int[n];
    if( !p )
        return false;

    merge_sort_r(a, 0, n - 1, p);
    delete p;
    return true;
}


bool merge_sort_iterator(int a[], int len)
{
    int left_min = 0;
    int left_max = 0;
    int right_mix = 0;
    int right_max = 0;
    int next = 0;

    int *tmp = new int[len];
    if( !tmp )
        return false;

    for(int i = 1; i < len; i *= 2)
    {
        for(left_min = 0; left_min < len - i; left_min = right_max)
        {
            right_mix = left_max = left_min + i;
            right_max = left_max + i;

            if(right_max > len)
                right_max = len;

            next = 0;

            while(left_min < left_max && right_mix < right_max)
            {
                tmp[next++] = a[left_min] < a[right_mix] ? a[left_min++] : a[right_mix++];
            }

            while(left_min < left_max)
                a[--right_mix] = a[--left_max];

            while(next > 0)
                a[--right_mix] = tmp[--next];
        }

    }

    delete tmp;
    return true;
}



























