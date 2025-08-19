# Modelo de regresión lineal
# Osmar Dominique Santana Reyes

data(mtcars)
head(mtcars)

# El modelo representa el consumo de combustible (mpg) en función del peso del vehículo (wt)
modelo <- lm(mpg ~ wt, data = mtcars)
summary(modelo)

plot(mtcars$wt, mtcars$mpg, main = "Consumo de Combustible en función del peso del vehículo",
     xlab = "Peso", ylab = "Consumo", pch = 1, col = "red")
abline(modelo, col = "blue", lwd = 3)


