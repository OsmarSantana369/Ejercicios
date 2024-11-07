#Ejemplo estimador de razón

#Supongamos que 20 alumnos hicieron un examen y obtuvieron las sigs. calificaciones

x <- c(6, 6.2, 7, 8, 9, 7.5, 5, 5.5, 6.6, 4.4)

length(x)

#Pensemos que este examen se hizo sin haber estudiado, ahora a estos 10 alumnos se les instruyó
#un nuevo método de estudio y después del método volvieron a realizar el examen y se obtuvo

y <- x + 0.5
y

#Estimador de razón

sumax = sum(x)
sumay = sum(y)
estimador_razon = sumay/sumax
estimador_razon

