import pandas as pd
import matplotlib.pyplot as plt


data = pd.read_csv("../data/test_data.csv")
print(data)

classes = data["BmiClass"].unique()
class_to_color = {cls: idx for idx, cls in enumerate(classes)}
colors = data["BmiClass"].map(class_to_color)

print(classes)

ax = plt.subplots()[1]
scatter = ax.scatter(data["Weight"], data["Height"], c=colors, cmap='viridis')
ax.legend(scatter.legend_elements()[0], classes)
plt.show()

