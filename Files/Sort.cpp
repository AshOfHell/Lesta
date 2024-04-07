int Sort(std::vector<int>& values, int l, int r)
{
    int x = values[r];
    int less = l;

    for (int i = l; i < r; ++i)
    {
        if (values[i] <= x)
        {
            std::swap(values[i], values[less]);
            ++less;
        }
    }
    std::swap(values[less], values[r]);
    return less;
}

void QuickSort(std::vector<int>& values, int l, int r)
{
    if (l < r)
    {
        int q = Sort(values, l, r);
        QuickSort(values, l, q - 1);
        QuickSort(values, q + 1, r);
    }
}

void QuickSort(std::vector<int>& values)
{
    if (!values.empty()) {
        QuickSort(values, 0, values.size() - 1);
    }
}
