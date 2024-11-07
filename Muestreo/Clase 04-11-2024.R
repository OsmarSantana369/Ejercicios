# Clase 4-11-2024
#Propociones

#Supongamos que se quiere conocer la proporción de personas que estána  favor de cierta ley.
#Para ello se tiene una población de 5000 personas, pero consideramos una muestra de 25 personas
#Para las personas de la muestra, se les preguntó si están a favor o en contra de la ley,
# considerando 1 si están a favor y 0 si están en contra

muestra <- sample(c(0, 1), size = 25, replace = T)   #Sin comillas los números son números y con comillas son caracteres
muestra    # los resultados de los y_i

N = 5000   #Tamaño de la población

n = length(muestra)   #tamaño de la muestra
n

suma = sum(muestra)   #suma de los y_i's
#Estimador para la proporción de personas a favor

estproporcion = suma/n
estproporcion

#Porcentaje total

porcentaje_total = N*estproporcion   #Porcentaje de las 5000 personas
 
#Intervalo de confianza

varianza = N/(N-1)*estproporcion*(1-estproporcion)
varianza

# Confianza 98%, alpha/2 = 0.01

z = qnorm(0.01,0,1)
z

#Intervalo de confianza

limite_inferior = estproporcion + z*sqrt(varianza/n)
limite_inferior

limite_superior = estproporcion - z*sqrt(varianza/n)
limite_superior

#Se espera que el verdadero de la proporción se encuentre entre (0.1029411, 0.5370589)

limite_inferior*N   #Limite inferior en personas
limite_superior*N   #Limite superior en personas

#En términos de personas, esperamos que las que estén a favor sean entre 515 y 2685