# ============================================
# R PROGRAM: BAR CHART AND SCATTER PLOT
# ============================================

# 1. BAR CHART
sales <- c(100, 150, 200, 120)
products <- c("A", "B", "C", "D")

cat("----- BAR CHART -----\n")
cat("Product Sales:\n")

for (i in 1:length(products)) {
  cat(products[i], "=", sales[i], "\n")
}

cat("Highest Sales =", max(sales), "\n")
cat("Product with Highest Sales =", products[which.max(sales)], "\n")

barplot(sales,
        names.arg = products,
        main = "Product Sales",
        xlab = "Products",
        ylab = "Sales")


# 2. SCATTER PLOT
price <- c(10, 20, 30, 40, 50)
sales2 <- c(15, 25, 35, 45, 60)

cat("\n----- SCATTER PLOT -----\n")
cat("Price and Sales:\n")

for (i in 1:length(price)) {
  cat("Price =", price[i], 
      " Sales =", sales2[i], "\n")
}

cat("Correlation between Price and Sales =",
    cor(price, sales2), "\n")

plot(price, sales2,
     main = "Price vs Sales",
     xlab = "Price",
     ylab = "Sales",
     pch = 19)