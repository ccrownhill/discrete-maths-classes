package main

func RodCutBotUp(l int, p []int) int {
	v := make([]int, l+1)
	v[0] = 0
	for i := 1; i < l+1; i++ {
		v[i] = 0
		for j := 1; j <= i; j++ {
			val := p[j-1] + v[i-j]
			if val > v[i] {
				v[i] = val
			}
		}
	}
	return v[len(v)-1]
}

// this is not actually dynamic programming it is a divide and conquer algorithm
// because it does not employ memoization
func RodCutDivConq(l int, p []int) int {
	if l == 0 {
		return 0
	}
	if l == 1 {
		return p[0]
	}

	max := 0
	for j := 1; j < l+1; j++ {
		val := p[j-1] + RodCutDivConq(l-j, p)
		if val > max {
			max = val
		}
	}

	return max
}

func RodCutTopDown(l int, p []int) int {
	v := make([]int, l+1)
	v[0] = 0
	v[1] = p[0]

	return RodCutTopDownRec(l, p, v)
}

func RodCutTopDownRec(l int, p []int, v []int) int {
	if v[l] != 0 || l == 0 {
		return v[l]
	}

	max := 0
	for i := 1; i < l+1; i++ {
		val := p[i-1] + RodCutTopDownRec(l-i, p, v)
		if val > max {
			max = val
		}
	}
	v[l] = max
	return max
}

func RodCutReconstruct(l int, p []int) (int, []int) {
	v := make([][]int, l+1)
	for i, _ := range v {
		v[i] = make([]int, 2)
	}

	v[0] = []int{0, 0}
	for i := 1; i < l+1; i++ {
		v[i][0] = 0
		for j := 1; j <= i; j++ {
			val := p[j-1] + v[i-j][0]
			if val > v[i][0] {
				v[i] = []int{val, j}
			}
		}
	}
	var rec []int

	for cut, length := v[len(v)-1][1], l; cut != 0; cut = v[length][1] {
		rec = append(rec, cut)
		length = length - cut
	}
	return v[len(v)-1][0], rec
}
