import pandas as pd
import matplotlib.pyplot as plt


data = pd.read_csv("../data/classification_map.csv", header=None)
print(data)

classes = data.iloc[:, 2].unique()
class_to_color = {cls: idx for idx, cls in enumerate(classes)}
colors = data.iloc[:, 2].map(class_to_color)

print(classes)

ax = plt.subplots()[1]
scatter = ax.scatter(data.iloc[:, 1], data.iloc[:, 0], marker="s", c=colors, cmap='viridis')
# ax.legend(scatter.legend_elements()[0], classes)
plt.show()

