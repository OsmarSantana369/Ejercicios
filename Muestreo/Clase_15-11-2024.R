#valores de la tabla 
acres92 <- c(175209, 138135, 56102, 45356, 89228, 96194, 57253, 210692, 
             78772, 343115, 19556, 15660, 55827, 58727) # Primeros y últimos datos como ejemplo
acres87 <- c(179311, 143515, 59061.8, 52536.2, 105586, 118293, 65414.2, 226517, 
             85201, 357751, 21369, 15176, 55635, 58727)

# Crear el data frame con los datos visibles
datos <- data.frame(acres92, acres87)

# Ajustar el modelo de regresión lineal
modelo <- lm(acres92 ~ acres87, data = datos)

# Resumen del modelo para obtener coeficientes y estadísticos
summary_modelo <- summary(modelo)

# Análisis de varianza
anova_modelo <- anova(modelo)

# Cálculos adicionales
ecm_raiz <- sqrt(mean(residuals(modelo)^2))        # Error Cuadrático Medio (Raíz)
media_dep <- mean(datos$acres92, na.rm = TRUE)     # Media de la variable dependiente
cv <- (ecm_raiz / media_dep) * 100                 # Coeficiente de variación
r_cuadrada <- summary_modelo$r.squared             # R-cuadrada
r_cuadrada_adj <- summary_modelo$adj.r.squared     # R-cuadrada ajustada

# imprimir los resultados basados en los valores elegidos 
cat("Análisis de varianza:\n")
cat("Fuente\tGrados de libertad\tSuma de cuadrados\tMedia cuadrática\tValor F\tProb > F\n")
cat(sprintf("Modelo\t%d\t\t%.2f\t\t%.2f\t\t%.2f\t%.4f\n", anova_modelo$Df[1], anova_modelo$`Sum Sq`[1], anova_modelo$`Mean Sq`[1], anova_modelo$`F value`[1], anova_modelo$`Pr(>F)`[1]))
cat(sprintf("Error\t%d\t\t%.2f\t\t%.2f\n", anova_modelo$Df[2], anova_modelo$`Sum Sq`[2], anova_modelo$`Mean Sq`[2]))
cat(sprintf("Total\t%d\t\t%.2f\n\n", sum(anova_modelo$Df), sum(anova_modelo$`Sum Sq`)))

cat(sprintf("ECM Raíz: %.4f\n", ecm_raiz))
cat(sprintf("Dep media: %.4f\n", media_dep))
cat(sprintf("CV: %.4f\n", cv))
cat(sprintf("R-cuadrada: %.4f\n", r_cuadrada))
cat(sprintf("R-cuadrada ajustada: %.4f\n\n", r_cuadrada_adj))

# Estimación de parámetros
cat("Estimaciones de parámetros:\n")
cat("Variable\tGrados de libertad\tEstimación\tError estándar\tT para H_0: Parámetro=0\tProb |T| > 0\n")
coeficientes <- summary_modelo$coefficients
for (i in 1:nrow(coeficientes)) {
  nombre_var <- rownames(coeficientes)[i]
  estimacion <- coeficientes[i, 1]
  error_estandar <- coeficientes[i, 2]
  t_valor <- coeficientes[i, 3]
  prob_t <- coeficientes[i, 4]
  cat(sprintf("%s\t\t1\t\t%.4f\t\t%.4f\t\t%.4f\t\t\t%.4f\n", nombre_var, estimacion, error_estandar, t_valor, prob_t))
}

table(acres87)