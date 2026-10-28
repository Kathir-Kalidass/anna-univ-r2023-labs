# Arithmetic Operations
a <- 20
b <- 10

cat("a =", a, "\n")
cat("b =", b, "\n")

cat("a + b =", a + b, "\n")
cat("a - b =", a - b, "\n")
cat("a * b =", a * b, "\n")
cat("a / b =", a / b, "\n")
cat("a %% b =", a %% b, "\n")
cat("a ^ b =", a ^ b, "\n")

# Vector Summary Operations
x <- c(10, 20, 30, 40, 50)

cat("x =", x, "\n")

cat("max(x) =", max(x), "\n")
cat("min(x) =", min(x), "\n")
cat("sum(x) =", sum(x), "\n")
cat("mean(x) =", mean(x), "\n")

# Math Functions on a Scalar
x <- 25.6789

cat("x =", x, "\n")

cat("sqrt(x) =", sqrt(x), "\n")
cat("round(x, 2) =", round(x, 2), "\n")

# Measures of Central Tendency (Mean, Median, Mode)
x <- c(10, 20, 20, 30, 40)

cat("x =", x, "\n")

cat("mean(x) =", mean(x), "\n")
cat("median(x) =", median(x), "\n")

mode_value <- names(sort(table(x), decreasing = TRUE))[1]
cat("mode =", mode_value, "\n")

# Measures of Dispersion (Standard Deviation & Variance)
x <- c(10, 20, 30, 40, 50)

cat("x =", x, "\n")

cat("sd(x) =", sd(x), "\n")
cat("var(x) =", var(x), "\n")