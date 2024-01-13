import matplotlib.pyplot as plt

classes = ['A', 'B', 'C', 'D']
valores = [3, 7, 1, 4]

plt.bar(classes, valores, color='blue')
plt.xlabel('Classes')
plt.ylabel('Quantidades')
plt.title('Gráfico de Barras Experimental')
plt.show()
