#Parametres

#2x + 3
trainX = [[1,1], [1,2], [1,3], [1,4], [1,5], [1,6], [1,7], [1,8], [1,9], [1,10]]
trainY = [4.897, 7.094, 9.064, 11.049, 12.859, 15.054, 17.005, 18.852, 20.864, 23.065]

XToPredict = [1,11]


# NE PAS TOUCHER
arrayWeight = []							# poids
sampleCount = len(trainX)					# number exemples
inputCountPerSample = len(trainX[0])		# number caracteristique par exemple
sizeArrayWeight = inputCountPerSample + 1 	# ajout du biais 

XToPredictSize = len(XToPredict)

#tranforme en double
for el in trainX:
	el = list(map(float, el))

trainY = list(map(float, trainY))
XToPredict = list(map(float, XToPredict))


