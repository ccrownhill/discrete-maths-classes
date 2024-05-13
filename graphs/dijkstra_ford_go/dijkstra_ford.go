package main

type MinVert interface {
	GetMin() (int, int)
	RemoveMin()
	Add(vert, dist int)
}

type MinList struct {
	items [][]int
}

func (ml *MinList) GetMin() (int, int) {
	return ml.items[len(ml.items)-1][0], ml.items[len(ml.items)-1][1]
}

func (ml *MinList) RemoveMin() {
	if len(ml.items) > 0 {
		ml.items = ml.items[:len(ml.items)-1]
	}
}

func (ml *MinList) Add(vert, dist int) {
	if len(ml.items) == 0 || dist < ml.items[len(ml.items)-1][1] {
		ml.items = append(ml.items, []int{vert, dist})
	} else {
		ml.items = append(ml.items, ml.items[len(ml.items)-1])
		i := len(ml.items) - 2
		for ; i >= 0 && dist > ml.items[i][1]; i-- {
		}
		ml.items[i+1] = []int{vert, dist}
	}
}

func Dijkstra(graph []map[int]int, from, to int) int {
	// map of distances from "from" to all other nodes
	dist := make(map[int]int)
	// fill map with distances of adjacent nodes
	ml := MinList{[][]int{}}
	for vert, d := range graph[from] {
		dist[vert] = d
		ml.Add(vert, d)
	}

	for v, d := ml.GetMin(); v != to; {
		ml.RemoveMin()
		for i := 0; i < len(graph); i++ {
			dist_v_to_i, is_in_map := graph[v][i]
			if i == from || !is_in_map {
				continue
			}
			tmpDist := d + dist_v_to_i
			orig_dist_to_i, is_finite := dist[i]

			if !is_finite || tmpDist < orig_dist_to_i {
				dist[i] = tmpDist
				ml.Add(i, tmpDist)
			}
		}
		break
	}

	return dist[to]
}

func Bellman(graph []map[int]int, from, to int) (int, []int) {
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
