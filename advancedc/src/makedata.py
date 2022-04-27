#!/usr/bin/env python3
from random import choice
from typing import List, Tuple

FILENAME = "/usr/share/dict/propernames"
DOMAINS = [
    "hotmail.com", "gmx.de", "gmail.com", "yahoo.com", "web.de",
    "example.com", "yahoo.fr", "yahoo.de", "yahoo.it"
]

def make_data(ncount=512) -> List[Tuple]:
    names = open(FILENAME, "r").readlines()
    # print(names)
    size = len(names)
    print(f"size = {size}")
    data = []
    for _ in range(ncount):
        i = choice(list(range(size)))
        j = choice(list(range(size)))
        fname = names[i].strip("\n").strip()
        lname = names[j].strip("\n").strip()
        domain = choice(DOMAINS)
        email = f"{fname.lower()}.{lname.lower()}@{domain}".strip()
        data.append((fname, lname, email))
    return data


def main():
    data = make_data();
    
    with open("../persondata.txt", "w") as fp:
        for item in data:
            print(f"{item}")
            fname, lname, email = item
            fp.write(f"{fname}, {lname}, {email}\n")
    print(f"len(data) = {len(data)}")
    print(f"len(set(data)) = {len(set(data))}")
    


if __name__ == "__main__":
    main()
