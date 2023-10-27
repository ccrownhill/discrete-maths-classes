package main

func insertSort(a []int) []int {
	result := make([]int, len(a))
	copy(result, a)
	for i, key := range result[1:] {
		j := i
		for ; j >= 0 && key < result[j]; j-- {
			result[j+1] = result[j] // shift to right
		}
		result[j+1] = key
	}
	return result
}
func merge(a, b []int) []int {
	result := make([]int, len(a)+len(b))
	i, j := 0, 0
	for k := 0; k < len(result); k++ {
		if i >= len(a) {
			result[k] = b[j]
			j++
		} else {
			if j < len(b) && b[j] <= a[i] {
				result[k] = b[j]
				j++
			} else {
				result[k] = a[i]
				i++
			}
		}
	}
	return result
}

func mergeSort(a []int) []int {
	if len(a) == 1 {
		return a
	} else {
		start, end := 0, len(a)
		mid := len(a) / 2
		return merge(mergeSort(a[start:mid]), mergeSort(a[mid:end]))
	}
}
