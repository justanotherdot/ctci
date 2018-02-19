package main

import (
	"fmt"
)

type pair struct {
	rune  rune
	count int
}

type example struct {
	input    string
	expected string
}

func main() {
	examples := []string{
		"",
		"taco",
		"octa",
		"baaaaby",
		"bbbaaaaby",
		"bbbaaaabyyyy",
		"goodbye",
		"This is a relatively long sentence compared to the other examples",
		"          this has a lot of whitespace",
	}

	for _, example := range examples {
		fmt.Println(huffman(example))
		//fmt.Printf("Groupings for '%s'\n", example)
		// for _, x := range xs {
		// 	fmt.Printf("%c %d\n", x.rune, x.count)
		// }
	}
}

func huffman(s string) string {
	rv := ""
	ps := groupRunes(s)

	// Give back the original string if all counts are just one.
	// Or, iow, no compression took place.
	allOnes := true
	for _, p := range ps {
		if p.count > 1 {
			allOnes = false
		}
	}

	if !allOnes {
		for _, p := range ps {
			if p.count == 1 {
				rv += fmt.Sprintf("%c", p.rune)
			} else {
				rv += fmt.Sprintf("%c%d", p.rune, p.count)
			}
		}
	} else {
		rv = s
	}

	return rv
}

func groupRunes(s string) []pair {
	rv := make([]pair, 0)
	skip := 0
	for i, r0 := range s {
		// XXX Nasty hack to skip the next j many runes.
		if skip > 0 {
			skip -= 1
			continue
		}

		var p pair
		p.rune = r0
		for _, r1 := range s[i:] {
			if r0 == r1 {
				p.count++
			} else {
				break
			}
		}

		// XXX Nasty hack to skip next j many runes.
		skip = p.count - 1

		rv = append(rv, p)
	}
	return rv
}
