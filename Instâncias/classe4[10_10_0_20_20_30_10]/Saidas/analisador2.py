#name_file  = "[resultados][100_100_100].csv"
import csv
x = 100
total  = []
while x != 500:
	#print(str(x))		
	name_file  = "[resultados]["+str(x)+"_"+str(x)+"_"+str(x)+"].csv"
	acumulador = []
	with open(name_file, 'r') as ficheiro:
	    reader = csv.reader(ficheiro)
	    for linha in reader:
	    	if linha[0] != "id":
	    		acumulador.append([linha[0],linha[16]])	    		    	
	x= x+ 100
	total.append(acumulador)	
	#print(acumulador)

print("")
out_file = csv.writer(open("relacao_viavel.csv", "a"))

for x in range(27):
	#print([x,total[0][x][1],total[1][x][1],total[2][x][1],total[3][x][1]])
	out_file.writerow([(x+1),total[0][x][1],total[1][x][1],total[2][x][1],total[3][x][1]])
	
print("")
