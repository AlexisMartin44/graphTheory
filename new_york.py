import re

regex = re.compile(r"\((\S*?)\s(\S*?),\s(\S*?)\s(\S*?)\)", re.MULTILINE)

sommets = {}
aretes = []

with open('CSCL_PUB_Centerline.csv') as csvfile:
	data = csvfile.read()
	matches = regex.finditer(data)

	i = 0
	for matchNum, match in enumerate(matches, start=0):
		p1 = float(match.group(1)), float(match.group(2))
		p2 = float(match.group(3)), float(match.group(4))
		if p1[1] < 40.649 or p2[1] < 40.649:
			continue
		try:
			s1 = sommets[p1]
		except:
			s1 = i
			sommets[p1] = s1
			i += 1
		try:
			s2 = sommets[p2]
		except:
			s2 = i
			sommets[p2] = s2
			i += 1
		aretes.append((s1, s2))
		if matchNum % 1000 == 0:
			print(matchNum)
	
	with open('graph_new_york.txt', "w") as output:
		minX, minY = min(sommets.keys())
		maxX, maxY = max(sommets.keys())
		sizeX, sizeY = (10000, 8000)
		propX = sizeX / (maxX - minX)
		propY = sizeY / (maxY - minY)
		print(minX, minY, maxX, maxY, propX, propY)
		output.write("0\n")
		output.write(str(len(sommets)) + "\n")
		for k, v in sommets.items():
			x = (k[0] - minX) * propX
			y = (k[1] - minY) * propY
			output.write(str(v) + " " + str(v) + " " + str(int(x)) + " " + str(int(y)) + "\n")
		print("wahhhhhhat")
		output.write(str(len(aretes)) + "\n")
		for i, v in enumerate(aretes):
			output.write(str(i) + " " + str(v[0]) + " " + str(v[1]) + "\n")
