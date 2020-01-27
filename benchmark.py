import os
import itertools

algorithms = ['fib', 'bin', 'adj', 'kru']
#algorithms = ['kru']
densities = [0.1, 0.3, 0.7, 1.0]
#densities = [0.15, 0.5, 0.85 ]
#densities = [1.0]
cardinalities = [100, 300, 500, 700, 1000, 2000, 3000, 5000, 7000]
#cardinalities = [200, 400, 800, 1500, 2500, 4000, 6000]
cardinalities = [10, 30 , 70]
#os.system('rm scores.txt')


for i, case in enumerate(itertools.product(cardinalities, densities)):
    os.system('./createGraph {} {}'.format(case[0], case[1]))
    print('Created graph {} out of {}'.format(i, len(densities) * len(cardinalities)))
    for alg in algorithms:
        with open('scores.txt', 'a+') as fo:
            os.system('./MST {}'.format(alg))
            with open('score.txt', 'r') as fi:
                score = fi.readline()
                fo.write('{} {} {} {}'.format(case[0], case[1], alg, score))

