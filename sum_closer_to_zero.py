# find a pair, which yields a sum that is closer to 0
mylist = [1, 65, -10, -70]
minm = max(mylist)
for i in range(len(mylist)):
    for j in range(i + 1, len(mylist)):
        if (abs(mylist[i] + mylist[j]) <= abs(minm)):
            minm = mylist[i] + mylist[j]
            low = mylist[i]
            high = mylist[j]
print(f"{minm} is closest to zero by adding {low} and {high}")
