package main

import (
	"fmt"
	"reflect"
	"testing"
)

func TestRodCut(t *testing.T) {
	prices := []int{1, 5, 8, 9, 10, 17, 17, 20, 24, 30}
	testSingle := func(t testing.TB, l, want int, fn func(int, []int) int) {
		t.Helper()
		got := fn(l, prices)
		if got != want {
			t.Errorf("got %d want %d", got, want)
		}
	}

	testReconstruct := func(t testing.TB, l, want_val int, rec_options [][]int,
		fn func(int, []int) (int, []int)) {
		t.Helper()
		got_val, got_rec := fn(l, prices)
		is_wrong_rec := true
		for _, v := range rec_options {
			if reflect.DeepEqual(v, got_rec) {
				is_wrong_rec = false
				break
			}
		}
		if got_val != want_val || is_wrong_rec {
			t.Errorf("got val %d want %d and\ngot reconstruction %v want for example %v",
				got_val, want_val, got_rec, rec_options[0])
		}
	}

	wanted := []int{1, 5, 8, 10, 13, 17, 18, 22, 25, 30}

	wanted_reconstructed := [][][]int{
		{{1}},
		{{2}},
		{{3}},
		{{2, 2}},
		{{2, 3}},
		{{6}},
		{{1, 6}, {2, 2, 3}},
		{{2, 6}},
		{{3, 6}},
		{{10}},
	}

	for i := 0; i < len(wanted); i++ {
		msg := fmt.Sprintf("testing bottom up length %d", i)
		t.Run(msg, func(t *testing.T) {
			testSingle(t, i+1, wanted[i], RodCutBotUp)
		})
		msg = fmt.Sprintf("testing divide and conquer length %d", i)
		t.Run(msg, func(t *testing.T) {
			testSingle(t, i+1, wanted[i], RodCutDivConq)
		})
		msg = fmt.Sprintf("testing top down length %d", i)
		t.Run(msg, func(t *testing.T) {
			testSingle(t, i+1, wanted[i], RodCutTopDown)
		})

		msg = fmt.Sprintf("testing with reconstruction for length %d", i)
		t.Run(msg, func(t *testing.T) {
			testReconstruct(t, i+1, wanted[i], wanted_reconstructed[i],
				RodCutReconstruct)
		})
	}
}
