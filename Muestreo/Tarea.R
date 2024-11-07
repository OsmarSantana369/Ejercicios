library(readxl)
Muestreobase <- read_excel("C:/Users/GabDomDal/Desktop/Ejercicios/Muestreo/Muestreobase.xlsx")
View(Muestreobase)

data <- data.frame(Muestreobase)

Añoant <- data$X2023
Añoant
Municipio <- data$cve_municipio
Municipio

media = mean(Añoant)
media

varianza = var(Añoant)
varianza

desvest = sqrt(varianza)
desvest

coefvar = desvest/media

hist(x = Municipio, y = Añoant)

plot(Municipio, Añoant)

N = length(Añoant)
N

#Prueba piloto de 25

Prueba = sample(Añoant, 4, replace = FALSE)
Prueba

mediaP = mean(Prueba)
mediaP

varP = var(Prueba)
varP

total = sum(Prueba)
total

#Obtención del tamaño de muestra

n0 = ((qnorm(0.05)^2)*(varP)^2)/(150^2)
n0

n1 = n0/(1 + (n0/N))
n1

n = ceiling(n1)
n

#Muestreo

Muestra <- sample(Añoant, n)
Muestra

mediaest = mean(Muestra)
mediaest

totalest = sum(Muestra)
totalest

varest = var(Muestra)
varest

#Intervalos de confianza para la media

intinf = mediaest + qnorm(0.05,0,1)*sqrt(((varest^2)/n)*(1 - n/N))
intinf

intsup = mediaest - qnorm(0.05,0,1)*sqrt(((varest^2)/n)*(1 - n/N))
intsup

