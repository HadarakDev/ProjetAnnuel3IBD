def getMLResults(pathImg, pathImgCrop, modele=None):
    results = {}
    results["models"] = []
    results["models"].append({"nom": "Modele lineaire", "implement": "NA", "framework": "NA"})
    results["models"].append({"nom": "PMC", "implement": "NA", "framework": "NA"})
    results["models"].append({"nom": "RBF", "implement": "NA", "framework": "NA"})
    results["models"].append({"nom": "SVM", "implement": "NA", "framework": "NA"})
    return results