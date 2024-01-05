import cv2
import numpy as np
from sklearn.cluster import KMeans

imagem = cv2.imread('ultrassound/cropped/503311001.bmp')
altura, largura = imagem.shape[:2]

# Convertendo a imagem para um array de pixels
pixels = imagem.reshape((imagem.shape[0] * imagem.shape[1], 3))

# Aplicando K-means para agrupar os pixels em 5 clusters
kmeans = KMeans(n_clusters=5)
kmeans.fit(pixels)

# Substituindo os pixels pelos valores dos centroides
segmented_img = kmeans.cluster_centers_[kmeans.labels_]
segmented_img = segmented_img.reshape(imagem.shape)

# Convertendo para escala de cinza para aplicar o detector de bordas
gray_img = cv2.cvtColor(segmented_img.astype(np.uint8), cv2.COLOR_BGR2GRAY)

# Aplicando o detector de bordas Canny
edges = cv2.Canny(gray_img, 100, 200)

# Mostrando a imagem original e as bordas detectadas
cv2.imshow('Imagem Original', imagem)
cv2.imshow('Bordas Detectadas', edges)
cv2.waitKey(0)
cv2.destroyAllWindows()
