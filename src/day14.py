import re

Target_Time = 2503

def get_distance(time, speed, duration, rest):
    mod = duration + rest
    tt = time // mod
    result = speed * duration * tt
    rr = time % mod    
    if rr > duration:
        result += speed * duration
    else:
        result += speed * rr
    return result

f = open("../input/day14-input.txt", "r")
input = f.readlines()

rr = re.compile(r"(\w+) can fly (\d+) km/s for (\d+).* must rest for (\d+) seconds.")
rules = [mm[0] for mm in [rr.findall(line) for line in input]] 

# Part 1
dists = [get_distance(Target_Time, int(r[1]), int(r[2]), int(r[3])) for r in rules]
print("Part 1: ", max(dists)) 

# Part 2
stats = [0 for line in input]
t = 0
while t < Target_Time:
    t += 1
    furthest = 0
    furthestIndex = -1
    i = 0
    for r in rules:
        dist = get_distance(t, int(r[1]), int(r[2]), int(r[3]))
        if dist > furthest:
            furthest = dist 
            furthestIndex = i
        i += 1
    stats[furthestIndex] += 1

print("Part 2: ", max(stats))

