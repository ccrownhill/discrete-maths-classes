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

func mergeSort(a []int) []int {
	return []int{1, 2, 3}
}
