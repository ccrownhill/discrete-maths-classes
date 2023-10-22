package main

import (
	"fmt"
	"reflect"
	"testing"
)

func TestSorts(t *testing.T) {
	testInputs := [][]int{
		{3, 4, 1, 5, 2},
		{10, 1, 300, 301, 22},
	}

	desiredOutputs := [][]int{
		{1, 2, 3, 4, 5},
		{1, 10, 22, 300, 301},
	}

	testSortSingle := func(t testing.TB, want, input []int, sortFn func([]int) []int) {
		got := sortFn(input)
		if !reflect.DeepEqual(want, got) {
			t.Errorf("input %v -> got %v want %v", input, got, want)
		}
	}

	testSortAll := func(t testing.TB, sortFn func([]int) []int) {
		for i := range testInputs {
			fmt.Printf("%v, %v\n", desiredOutputs[i], testInputs[i])
			testSortSingle(t, desiredOutputs[i], testInputs[i], sortFn)
		}
	}

	t.Run("Test sorting for insertSort", func(t *testing.T) {
		testSortAll(t, insertSort)
	})

	t.Run("Test sorting for mergeSort", func(t *testing.T) {
		testSortAll(t, mergeSort)
	})
}
