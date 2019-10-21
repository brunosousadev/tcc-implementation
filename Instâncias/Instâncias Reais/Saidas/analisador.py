import csv

start = 1
end = 7
first_part ="<td align=center>"
second_part ="</td>"

acumulador = []
valor  = input("Digite o numero")
pasta  = valor+"_"+valor+"_"+valor
for item in range(start,end+1):
	name_file = pasta+"/"+str(item)+"_informacoesFinais_.html"	
	aux  = []
	aux.append(item)
	try:
		with open(name_file, 'r') as in_f:
			for line in in_f:
				if first_part in line:
					line = line.replace(first_part,"")
					line = line.replace(second_part,"")
					if "\n" in line:
						line = line[:-1]					

					aux.append(line)					

		acumulador.append(aux)

	except IOError:
		print("[ Erro ao abrir arquivo] "+name_file)

out_file = csv.writer(open("[resultados]["+pasta+"].csv", "a"))
for x in acumulador:		
	out_file.writerow([x[0],x[1],x[2],x[3],x[4],x[5],x[6],x[7],x[8],x[9],x[10],x[11],x[12],x[13],x[14],x[15],x[16]])
