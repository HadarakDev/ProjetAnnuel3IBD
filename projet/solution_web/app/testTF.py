import numpy as np

from utilsImage import *

pathDataSet = """D:/CloudStation/Cours/3IBD/projetAnnuel/projet/dataset/test/"""
width = 490
height = 357
color = 1

if __name__ == "__main__":

    datasetX, datasetY = get_pixels_from_dataset(pathDataSet, width, height, color)

    print(datasetX.shape)
    print(datasetY)
