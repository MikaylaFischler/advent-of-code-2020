import re


def parse_passports(file):
    passports = []
    current = ""

    line = file.readline()
    while len(line) > 0:
        if len(line) == 1:
            passports.append(current)
            current = ""
        else:
            current = current + " " + line.replace('\n', '')
        line = file.readline()

    # append final passport if no new line at eof
    if current != "":
        passports.append(current)

    return passports


def extract(passport, key):
    data = passport.split(' ')

    for i in range(0, len(data)):
        if data[i].count(key) == 1:
            return data[i].split(':')[1]

    return None


def part_1(passports):
    present_passports = []
    valid_count = 0

    for i in range(0, len(passports)):
        # bulky but whatever
        ok = passports[i].count('byr') == 1
        extract(passports[i], 'byr')
        ok &= passports[i].count('iyr') == 1
        ok &= passports[i].count('eyr') == 1
        ok &= passports[i].count('hgt') == 1
        ok &= passports[i].count('hcl') == 1
        ok &= passports[i].count('ecl') == 1
        ok &= passports[i].count('pid') == 1
        # ignore cid because we are hackers now apparently

        if ok:
            valid_count += 1
            present_passports.append(passports[i])

    return valid_count, present_passports


def part_2(passports):
    valid_count = 0

    for i in range(0, len(passports)):
        passport = passports[i]

        valid = 1920 <= int(extract(passport, 'byr')) <= 2002
        valid &= 2010 <= int(extract(passport, 'iyr')) <= 2020
        valid &= 2020 <= int(extract(passport, 'eyr')) <= 2030

        hgt = extract(passport, 'hgt')
        if hgt.count('cm') == 1:
            valid &= 150 <= int(hgt.replace('cm', '')) <= 193
        elif hgt.count('in') == 1:
            valid &= 59 <= int(hgt.replace('in', '')) <= 76
        else:
            valid = False

        valid &= re.search("#[a-fA-F0-9]{6}", extract(passport, 'hcl')) != None

        ecl = extract(passport, 'ecl')
        colors = ('amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth')
        count = 0

        for c in range(0, len(colors)):
            count += ecl.count(colors[c])

        valid &= count == 1

        valid &= len(extract(passport, 'pid')) == 9

        if valid:
            valid_count += 1

    return valid_count


if __name__ == "__main__":
    input_file = open("input.txt")
    all_passports = parse_passports(input_file)
    p1_count, all_fields_present = part_1(all_passports)
    print("part 1: %d" % p1_count)
    print("part 2: %d" % part_2(all_fields_present))
