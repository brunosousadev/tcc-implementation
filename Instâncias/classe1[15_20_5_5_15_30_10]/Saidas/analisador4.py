import csv
x = 100
total  = []
x = int(input("Digite o valor"))

name_file  = "[resultados]["+str(x)+"_"+str(x)+"_"+str(x)+"].csv"
acumulador = []
out_file = csv.writer(open("["+str(x)+"]relacao_quebras.csv", "a"))
with open(name_file, 'r') as ficheiro:
    reader = csv.reader(ficheiro)
    for linha in reader:
    	if linha[0] != "id":
    		out_file.writerow([linha[0],linha[7],linha[8],linha[14],linha[15]])
    		#print([linha[0],linha[7],linha[8],linha[14],linha[15]])
    		#acumulador.append([linha[0],linha[16]])	    		    	
    #print(acumulador)
    #print("")
#total.append(acumulador)	
#print(acumulador)