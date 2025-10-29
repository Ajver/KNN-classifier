import pandas as pd
import matplotlib.pyplot as plt


map_data = pd.read_csv("../data/classification_map.csv", header=None)
source_data = pd.read_csv("../data/train_data.csv")

classes = map_data.iloc[:, 2].unique()
class_to_color = {cls: idx for idx, cls in enumerate(classes)}
map_colors = map_data.iloc[:, 2].map(class_to_color)
src_data_colors = source_data.iloc[:, 2].map(class_to_color)

print(classes)

ax = plt.subplots()[1]
ax.scatter(map_data.iloc[:, 1], map_data.iloc[:, 0], marker="s", c=map_colors, cmap='viridis', alpha=0.4)

ax.scatter(source_data.iloc[:, 1], source_data.iloc[:, 0], c=src_data_colors, cmap='viridis')

plt.show()

