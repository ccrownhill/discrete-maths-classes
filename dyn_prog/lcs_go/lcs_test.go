package main

import (
	"testing"
)

func TestLcs(t *testing.T) {
	testSingle := func(t testing.TB, w1, w2, want string) {
		t.Helper()

		got := Lcs(w1, w2)

		if want != got {
			t.Errorf("for w1 '%s' and w2 '%s' want '%s' but got '%s'", w1, w2, want, got)
		}
	}
	t.Run("as and bs", func(t *testing.T) {
		w1 := "aabaababaa"
		w2 := "ababaaabb"

		want := "ababaaa"

		testSingle(t, w1, w2, want)
	})

	t.Run("hallo and mail", func(t *testing.T) {
		w1 := "hallo"
		w2 := "mail"

		want := "al"

		testSingle(t, w1, w2, want)
	})
}
