package main

import (
	"fmt"
	"reflect"
	"testing"
)

func TestBellman(t *testing.T) {
	graph_normal := []map[int]int{
		map[int]int{1: 1},
		map[int]int{2: 3, 3: 1},
		map[int]int{0: 1, 3: 5},
		map[int]int{},
	}

	graph_cycle := []map[int]int{
		map[int]int{1: 1},
		map[int]int{2: -3, 3: 1},
		map[int]int{0: 1, 3: 5},
		map[int]int{},
	}

	testGraph := func(t testing.TB, graph []map[int]int, want_dist int, want_path []int) {
		t.Helper()

		got_dist, got_path := Bellman(graph, 0, len(graph)-1)
		if want_dist != got_dist || !reflect.DeepEqual(want_path, got_path) {
			t.Errorf("want dist %d got dist %d\nwant path %v got path %v",
				want_dist, got_dist, want_path, got_path)
		}
	}

	msg := fmt.Sprintf("testing graph %v\n", graph_normal)
	t.Run(msg, func(t *testing.T) {
		testGraph(t, graph_normal, 2, []int{1, 3})
	})

	msg = fmt.Sprintf("testing graph %v\n", graph_cycle)
	t.Run(msg, func(t *testing.T) {
		testGraph(t, graph_cycle, -1, []int{})
	})
}

func TestDijkstra(t *testing.T) {
	graph_normal := []map[int]int{
		map[int]int{1: 1},
		map[int]int{2: 3, 3: 1},
		map[int]int{0: 1, 3: 5},
		map[int]int{},
	}
	want := 2
	got := Dijkstra(graph_normal, 0, 3)

	if want != got {
		t.Errorf("want dist %d got dist %d", want, got)
	}
}
