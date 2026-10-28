# ============================================
# BUSINESS ANALYTICS - BASIC R PROGRAM
# Vector, Conditional Statement, For Loop,
# and Data Frame
# ============================================

# 1. Create a Vector
marks <- c(85, 90, 78, 88, 95)

cat("----- VECTOR OPERATIONS -----\n")

cat("Marks: ")
print(marks)

cat("Number of marks:", length(marks), "\n")


# 2. Conditional Statement
marks1 <- 75

cat("\n----- CONDITIONAL STATEMENT -----\n")

cat("Mark:", marks1, "\n")

if (marks1 >= 50) {
  print("Result: Pass")
} else {
  print("Result: Fail")
}


# 3. For Loop
cat("\n----- FOR LOOP -----\n")

cat("Numbers from 1 to 5:\n")

for (i in 1:5) {
  print(i)
}


# 4. Create a Data Frame
name <- c("A", "B", "C")
marks2 <- c(80, 90, 75)

data <- data.frame(name, marks2)

cat("\n----- DATA FRAME -----\n")

print(data)

cat("\nTotal Students:", nrow(data), "\n")