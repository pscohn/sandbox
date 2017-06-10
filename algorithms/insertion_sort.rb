def insertion_sort_reverse(array)
  j = 1
  while j < array.count
    key = array[j]
    i = j - 1
    while array[i] < key && i >= 0 # only difference here
      array[i + 1] = array[i]
      i -= 1
    end
    array[i + 1] = key
    j += 1
  end
  array
end

def insertion_sort(array)
  j = 1
  while j < array.count
    key = array[j]
    i = j - 1
    while array[i] > key && i >= 0
      array[i + 1] = array[i]
      i -= 1
    end
    array[i + 1] = key
    j += 1
  end
  array
end

print insertion_sort([6, 5, 1, 2, 0, 9]), "\n"
