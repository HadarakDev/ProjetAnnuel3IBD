def printRes(tab):
	for el in tab:
		print (el)

def truncate(n, size):
	return float(str(n)[:size+2])

def matrixToArray(matrix):
	ret = []
	for el in matrix:
		ret.extend(el)
	return ret, len(ret)

def convertListToString(list):
	ret = ""
	for el in list:
		ret += el
		ret += ','
	#ret += '\0'
	return ret