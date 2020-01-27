import matplotlib.pyplot as plt
import matplotlib
import pickle

reprAlgorithms= ['Naive Prim',
               'Binary heap Prim',
               'Fibonacci heap Prim',
                ]

#reprAlgorithms= ['time with initialization','time without initialization']
reprAlgorithms= ['Naive Prim', 'Prim with a Binary Heap','Prim with a Fibonacci heap', 'Kruskal']
#algorithms = ['adj', 'bin', 'fib','kru']
algorithms = ['adj', 'bin', 'fib']
densities = [0.1, 0.3, 0.7, 1.0]
#cardinalities = [10, 30, 100, 300, 1000, 3000, 10000, 30000]
#cardinalities = [10, 30, 70, 100, 300, 700, 1000, 2000, 3000, 7000]
cardinalities = [300, 700, 1000, 2000, 3000, 5000, 7000]
xticks = [300, 1000, 3000, 7000]
#xticks = [10, 30, 100, 300, 1000, 3000, 7000]

scores = {}
scores2 = {}

with open('scores.txt', 'r') as f:
    for line in f:
        cardinality, density, alg, score, score2 = line.split()
        scores2[(alg, float(density), int(cardinality))] = float(score2)
        scores[(alg, float(density), int(cardinality))] = float(score)

for density in densities:
    plt.plot(cardinalities, list(map(lambda x: scores[('kru', density , x)], cardinalities)),
             label=density,
             marker='o',
             linestyle='-')
plt.grid()
plt.xlabel('Cardinality [number of vertices]')
plt.ylabel('Time [s]')
plt.xscale('log')
plt.xticks(xticks)
plt.legend()
plt.title('Kruskal algorithm')
plt.show()



fig, axs = plt.subplots(2, 2)
plt.subplots_adjust(hspace=0.4)
axs = axs.flat
for i, density in enumerate(densities):
    axs[i].grid()
    for j, alg in enumerate(algorithms):
#        axs[i].plot(list(range(10)), list(map(lambda x: x**i, list(range(10)))))
        axs[i].plot(cardinalities,
                    list(map(lambda x: scores[(alg, density, x)], cardinalities)),
                    label=reprAlgorithms[j],
                    marker='o',
                    linestyle='-')
        #axs[i].plot(cardinalities,
        #            list(map(lambda x: scores2[(alg, density, x)], cardinalities)),
        #            label=reprAlgorithms[j+1],
        #            marker='o',
        #            linestyle='-')
        axs[i].set_xscale('log')
        axs[i].set_xticks(xticks)
        axs[i].get_xaxis().set_major_formatter(matplotlib.ticker.ScalarFormatter())
        print(list(map(lambda x: scores[(alg, density, x)], cardinalities)))

    axs[i].set(title='Density of edges: {}'.format(density),
               xlabel='Cardinality [number of vertices]',
               ylabel='Time [s]',)
    axs[i].legend()

plt.show()
