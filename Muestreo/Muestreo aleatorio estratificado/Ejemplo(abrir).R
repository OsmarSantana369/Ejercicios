#Ejemplo de muestreo aleatorio estratificado

#En el archivo MEX_01.xls se presenta las características principales de las
#unidades económicas según municipio, sector, subsector y rama de actividad,
#en el Estado de México durante el año 1998

#El objetivo de este programa será estimar las remuneraciones en el Estado de
#México para el año 1998.

#Para esto se considerará la remuneración total por cada rama de actividad
#y por municipio, es decir, la remuneración de cualquier rama de actividad en
#un municipio del Estado, es una unidad de la población total. De esta manera,
#las ramas de actividad serán la estratificación de la población total.

#Para manipular de forma más eficiente la información, se creó el archivo 
#REMEDOMEX, que solo contiene las variables y datos de interés:

library(readxl)
library(dplyr)
REMEDOMEX <- read_excel("REMEDOMEX.XLSX")   #Para cargar el archivo
View(REMEDOMEX)                             #Para visualizarlo

#Se crea un dataframe del archivo REMEDOMEX
remuneraciones <- data.frame(REMEDOMEX)   

#Creando un vector (Ramas) que contenga el nombre de cada una de las ramas de
#actividad:
rama <- select(remuneraciones, RAMA)
tbl <- table(rama)
Ramas <- names(tbl[tbl > 1])

#Estos vectores servirán para construir la tabla con los estimadores de cada
#estrato
N_i = c()
n_i = c()
y_i = c()
s_i2 = c()
t_i = c()
Vt_i = c()

#Se calculan los estimadores para una muestra aleatoria en cada estrato:
for (x in Ramas) {
    #Se filtran las remuneraciones que corresponden a x(una rama en específico)
    remuneracionx <- filter(remuneraciones, RAMA %in% c(x))
    N = length(remuneracionx$REMUNERACIONES)   #Tamaño del estrato (N_i)
    n = sample(2:N, size = 1)                  #Tamaño de la muestra (n_i)
    
    #Obteniendo la muestra del estrato x de tamaño n:
    muestrax = sample(remuneracionx$REMUNERACIONES, size = n, replace = F)
    mediax = mean(remuneracionx$REMUNERACIONES)        #Media de la muestra (X_i)
    varianzax = (1/(n-1))*sum((muestrax - mediax)^2)   #Varianza de la muestra (s_i^2)
    txest = N*mediax                                   #Población total estimada del estrato x (t_i)
    varianzatxest = (N^2)*(1-(n/N))*(varianzax/n)      #Varianza del estimador t_i (V(t_i))
    
    N_i = c(N_i, N)
    n_i = c(n_i, n)
    y_i = c(y_i, mediax)
    s_i2 = c(s_i2, varianzax)
    t_i = c(t_i, txest)
    Vt_i = c(Vt_i, varianzatxest)
} 

Tabla <- data.frame(Ramas, N_i, n_i, y_i, s_i2, t_i, Vt_i)
View(Tabla)

cat("En base a la tabla se concluye que la muestra que se tomó de la población total es de:") 
sum(n_i)
cat("de un total de")
sum(N_i)
cat("La estimación de la población total (las remuneraciones en el Estado de México para el año 1998) es:")
sum(t_i)
cat("siendo la población total real de:")
sum(remuneraciones$REMUNERACIONES)
cat("con una media de:")
sum(t_i)/sum(N_i)
cat("con varianza:")
sum(Vt_i)/(sum(N_i)^2)
cat("Un intervalo de confianza del 95% para la estimación de las las remuneraciones en el Estado de México para el año 1998 es:")
c(sum(t_i)-1.96*sqrt(sum(Vt_i)), sum(t_i)+1.96*sqrt(sum(Vt_i)))
