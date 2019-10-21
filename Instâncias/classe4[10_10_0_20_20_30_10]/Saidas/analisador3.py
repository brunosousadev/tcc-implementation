import csv
x = 100
total  = []
while x != 500:
	#print(x)
	name_file  = "[resultados]["+str(x)+"_"+str(x)+"_"+str(x)+"].csv"
	acumulador = []
	contador  = 0
	with open(name_file, 'r') as ficheiro:
		reader = csv.reader(ficheiro)
		for linha in reader:
			if linha[0] != "id":
				#print(linha[16])
				if linha[16] == "Viável":
					contador = contador+1
		#print(contador)
		total.append([x,contador,30-contador])
	x= x+ 100

out_file = csv.writer(open("taxa_de_viabilidade.csv", "a"))
for x in total:
	out_file.writerow([x[0],x[1],x[2]])
	#print(x)