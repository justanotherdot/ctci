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

fn diff_count(s: String, t: String, slen: usize, tlen: usize) -> i64 {
    let max_string;
    let min_string;
    if slen > tlen {
        max_string = s;
        min_string = t;
    } else {
        max_string = t;
        min_string = s;
    }

    let mut diff_count = 0;
    for (i, c0) in max_string.chars().enumerate() {
        let rc1 = min_string.get(i..(i+1));
        match rc1 {
            Some(c1) => {
                if c0.to_string() != c1 {
                    diff_count += 1;
                }
            }
            None => {
                diff_count += 1;
            }
        }
    }
    return diff_count;
}

fn cmp(s: String, t: String) -> EditDistanceType {
    let slen = s.chars().count();
    let tlen = t.chars().count();
    if slen == tlen {
        if s == t {
            return EditDistanceType::SameStr;
        } else {
            let diff_count = diff_count(s, t, slen, tlen);
            if diff_count == 1 {
                return EditDistanceType::SingularDiff(EditType::Replace);
            } else {
                return EditDistanceType::PluralDiff;
            }
        }
    } else {
        let len_delta;
        if slen > tlen {
            len_delta = slen - tlen;
        } else {
            len_delta = tlen - slen;
        }

        let dcount = diff_count(s, t, slen, tlen);
        if len_delta == 1 && dcount == 1 {
            if slen > tlen {
                return EditDistanceType::SingularDiff(EditType::Delete)
            } else {
                return EditDistanceType::SingularDiff(EditType::Insert)
            }
        } else {
            return EditDistanceType::PluralDiff;
        }
    }
}

fn main() {
    let examples = vec![
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
        println!("Examples: '{}', '{}'. result `{:?}'", e0, e1, rv);
        assert!(rv == *exp);
    }
}
