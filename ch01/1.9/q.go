package main

import (
	"fmt"
	"strings"
)

func substr(needle string, s string) bool {
	if len(needle) == len(s) {
		if strings.Contains(needle, s) {
			return true
		} else {
			// Test all substrs as slices.
		}
		return strings.Contains(needle, s)
	}
	return true
}

// Single call to substr.
// is rotation based on a single call to isSubStr
func main() {
	rv := substr("abc", "abc")
	fmt.Println(rv)
}
