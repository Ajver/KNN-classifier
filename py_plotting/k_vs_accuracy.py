import pandas as pd
import matplotlib.pyplot as plt


data = pd.read_csv("../data/k_vs_accuracy.csv")
data = data.to_numpy()
print(data.shape)

ax = plt.subplots()[1]
scatter = ax.plot(data[:, 0], data[:, 1], "-o")
plt.show()

