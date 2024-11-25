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
data <- data.frame(REMEDOMEX)   

#Creando un vector (ramas) que contenga el nombre de cada una de las ramas de
#actividad:
rama <- select(data, RAMA)
tbl <- table(rama)
ramas <- names(tbl[tbl > 1])

for (x in ramas) {
    x
    vectram <- filter(remuneraciones, RAMA %in% c(x))
} 
