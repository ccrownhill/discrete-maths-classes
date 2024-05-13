package main

func Lcs(w1, w2 string) string {
	memo := make([][][]int, len(w1)+1)
	for i, _ := range memo {
		memo[i] = make([][]int, len(w2)+1)
		for j, _ := range memo[i] {
			memo[i][j] = []int{-1, -1}
		}
	}
	out := ""

	var lcs_rec func(w1, w2 string) int

	lcs_rec = func(w1, w2 string) int {
		if memo[len(w1)][len(w2)][0] != -1 {
			return memo[len(w1)][len(w2)][0]
		} else if len(w1) == 0 || len(w2) == 0 {
			memo[len(w1)][len(w2)] = []int{0, -1}
		} else if w1[len(w1)-1] == w2[len(w2)-1] {
			//out = string(w1[len(w1)-1]) + out
			memo[len(w1)][len(w2)] = []int{1 + lcs_rec(w1[0:len(w1)-1], w2[0:len(w2)-1]), 0}
		} else {
			first := lcs_rec(w1[0:len(w1)-1], w2)
			second := lcs_rec(w1, w2[0:len(w2)-1])
			if first > second {
				memo[len(w1)][len(w2)] = []int{first, 1}
			} else {
				memo[len(w1)][len(w2)] = []int{first, 2}
			}
		}
		return memo[len(w1)][len(w2)][0]
	}

	lcs_rec(w1, w2)
	i, j := len(w1), len(w2)
	for i > 0 && j > 0 {
		if memo[i][j][1] == 0 {
			out = string(w2[j-1]) + out
			i--
			j--
		} else if memo[i][j][1] == 1 {
			i--
		} else {
			j--
		}
	}
	return out
}

func max(x, y int) int {
	if x > y {
		return x
	} else {
		return y
	}
}
