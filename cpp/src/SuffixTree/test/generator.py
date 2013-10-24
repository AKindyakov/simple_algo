import random
fl = open("test.txt", 'w')

fl.write(str(2)+'\n');
pop = ['a','b','c','d','f','g','h','i','j','l','k','m','n','o','p','q','r','s','t','u','v','w','x','y','z']

for i in range(2):
    ss = ""
    for k in range(100000):
        s = random.choice(pop);
        ss += s
    fl.write(ss+'\n');

fl.close()
