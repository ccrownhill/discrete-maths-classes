package main

func Dijkstra(graph []map[int]int, from, to int) (int, []int) {
	s := make([][][]int, len(graph))
	for i, _ := range s {
		s[i] = make([][]int, len(graph))
		for j, _ := range s[i] {
			if _, is_in_map := graph[i][j]; is_in_map == true {
				s[i][j] = []int{graph[i][j], j}
			} else if i == j {
				s[i][j] = []int{0, j}
			} else {
				s[i][j] = []int{0, -1} // if next hop is -1 it means that there the distance to that node is infinity
			}
		}
	}

	n := 0
	// should converge after max len(graph) - 1 iterations but do it for
	// 1 more and if it did not converge after that, i.e. changed != true
	// then there must be a cycle in the path
	changed := true
	for v := 0; changed == true && v < len(graph); v++ {
		changed = relaxWeights(s)
		n++
	}

	if changed == true {
		return -1, []int{}
	}

	var path []int
	// reconstruct path
	for k := s[from][to][1]; k != to; k = s[k][to][1] {
		path = append(path, k)
	}
	path = append(path, to)

	return s[from][to][0], path
}

// relax all weights and return true if there was a change otherwise false
func relaxWeights(s [][][]int) bool {
	changed := false
	for i, _ := range s {
		for j, _ := range s[i] {
			for k := 0; k < 4; k++ {
				if k == i {
					continue
				}
				val := s[i][k][0] + s[k][j][0]
				// check if distance is infinite by checking for invalid next hop
				if s[i][j][1] == -1 || (s[i][k][1] != -1 && s[k][j][1] != -1 && val < s[i][j][0]) {
					s[i][j] = []int{val, k}
					changed = true
				}
			}
		}
	}
	return changed
}
