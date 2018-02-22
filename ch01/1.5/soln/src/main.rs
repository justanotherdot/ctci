use std::cmp;

#[derive(Debug, PartialEq)]
enum EditType {
    Replace,
    Insert,
    Delete,
}

#[derive(Debug, PartialEq)]
enum EditDistanceType {
    SameStr,
    SingularDiff(EditType),
    PluralDiff,
}

fn lev_distance(s: &String, t: &String, i: usize, j: usize) -> usize {
    if cmp::min(i, j) == 0 {
        return cmp::max(i, j);
    } else {
        let indicator;
        if s.get((i-1)..i) == t.get((j-1)..j) {
            indicator = 0;
        } else {
            indicator = 1;
        }
        let a = lev_distance(s, t, i-1, j)+1; // Deletion.
        let b = lev_distance(s, t, i, j-1)+1; // Insertion.
        let c = lev_distance(s, t, i-1, j-1)+indicator; // Replacement or same.

        // Alternative, heavy-duty way compare three-way min is to bring in something like a
        // BTreeSet, do the insertions, and then pull out the element from an iterator.
        // e.g.
        //
        // use std::collections::BTreeSet;
        //
        // let mut set = BTreeSet::new();
        // set.insert(a);
        // set.insert(b);
        // set.insert(c);
        // let min = set.iter().next().unwrap();
        // return min;
        //
        if a >= b && a >= c {
            return cmp::min(b, c);
        } else if b >= a && b >= c {
            return cmp:: min(a, c);
        } else {
            return cmp:: min(a, b);
        }
    }
}

fn cmp(s: String, t: String) -> EditDistanceType {
    let slen = s.chars().count();
    let tlen = t.chars().count();
    let diff_count = lev_distance(&s, &t, slen, tlen);

    if diff_count == 0 {
        return EditDistanceType::SameStr;
    } else if slen == tlen && diff_count == 1 {
        return EditDistanceType::SingularDiff(EditType::Replace);
    } else if diff_count == 1 {
        if slen > tlen {
            return EditDistanceType::SingularDiff(EditType::Delete);
        } else {
            return EditDistanceType::SingularDiff(EditType::Insert);
        }
    } else {
        return EditDistanceType::PluralDiff;
    }
}

fn main() {
    let examples = vec![
        (
            "kitten".to_string(),
            "sitting".to_string(),
            EditDistanceType::PluralDiff
        ),
        (
            "hello".to_string(),
            "goodbye".to_string(),
            EditDistanceType::PluralDiff
        ),
        (
            "hello".to_string(),
            "heplo".to_string(),
            EditDistanceType::SingularDiff(EditType::Replace)
        ),
        (
            "hello".to_string(),
            "hellop".to_string(),
            EditDistanceType::SingularDiff(EditType::Insert)
        ),
        (
            "hellop".to_string(),
            "hello".to_string(),
            EditDistanceType::SingularDiff(EditType::Delete)
        ),
        (
            "hello".to_string(),
            "hello".to_string(),
            EditDistanceType::SameStr
        ),
        (
            "".to_string(),
            "".to_string(),
            EditDistanceType::SameStr
        ),
        (
            "helplo".to_string(),
            "hello".to_string(),
            EditDistanceType::SingularDiff(EditType::Delete)
        ),
        (
            "hello".to_string(),
            "helplo".to_string(),
            EditDistanceType::SingularDiff(EditType::Insert)
        ),
        (
            "abc".to_string(),
            "cba".to_string(),
            EditDistanceType::PluralDiff
        ),
        (
            "gaga".to_string(),
            "bpf".to_string(),
            EditDistanceType::PluralDiff
        ),
    ];

    for &(ref e0, ref e1, ref exp) in examples.iter() {
        let rv = cmp(e0.to_string(), e1.to_string());
        println!("Examples: '{}', '{}'. result `{:?}' vs. expected `{:?}'", e0, e1, rv, exp);
        assert!(rv == *exp);
    }
}
