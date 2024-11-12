#Ejemplo eficiente de estimación por regresión

Foto <- c(10, 12, 7, 13, 13, 6, 17, 16, 15, 10, 14, 12, 10, 5, 12, 10, 10, 9, 6, 11, 7, 9, 11, 10, 10)
Foto

Campo <- c(15, 14, 9, 14, 8, 5, 18, 15, 13, 15, 11, 15, 12, 8, 13, 9, 11, 12, 9, 12, 13, 11, 10, 9, 8)
Campo

#Estadísticas descriptivas

summary(Foto)
summary(Campo)

desvest_Foto = sd(Foto)
desvest_Foto

desvest_Campo = sd(Campo)
desvest_Campo

#Tenemos variable dependiente(Campo) e independiente(Foto)

modelo <- lm(Campo~Foto)
modelo                    #Campo = 5.0593 + 0.6718*Foto

#ANOVA (Análisis de la varianza)

anova(modelo)

#como el pivalium(Pr(>F)) es muy pequeño entonces existe una relación lineal entre Foto y Campo

plot(Foto, Campo)


Y = 5.0593 + 0.6718*Foto
plot(Foto, Y)

#La estimación por regresión de la media es

Estimador = 5.06 + 0.613*11.3
Estimador



#####################################################################################################################
#Cuando R>0.8 y 0.8>R>0.5, se dice que la relación es mejor y moderada, respectivamente
#Otro ejemplo

X <- c(1,2,3,4,5,6,7,8,9,10)
Y <- c(-100,100,500,-900,454,54,-852,114,5,-9)

#Estadísticas descriptivas

summary(X)
summary(Y)

desvest_X = sd(X)
desvest_X

desvest_Y = sd(Y)
desvest_Y

#Tenemos variable dependiente(Campo) e independiente(Foto)

modelo <- lm(Y~X)
modelo                    #Campo = 4.333 - 12.315*Foto

#ANOVA (Análisis de la varianza)

anova(modelo)

#En este ejemplo no hay relación lineal pues Pr(>F) = 0.8275

X <- c(1,2,3,4,5,6,7,8,9,10)
Y <- c(1,2,3,4,5,6,7,8,9,10)

#Estadísticas descriptivas

summary(X)
summary(Y)

desvest_X = sd(X)
desvest_X

desvest_Y = sd(Y)
desvest_Y

#Tenemos variable dependiente(Campo) e independiente(Foto)

modelo <- lm(Y~X)
modelo                    #Campo = 4.333 - 12.315*Foto

#ANOVA (Análisis de la varianza)

anova(modelo)

#En este ejemplo no hay relación lineal pues Pr(>F) = 0.8275
