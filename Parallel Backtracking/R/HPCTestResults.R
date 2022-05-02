data <- read.table(file="newtestResults.txt", sep=" ", header=FALSE)
colnames(data) <- c("n","depth","processes","real","user")

data5 <- data[ which(data$depth == 6 ), ]

data51 <- data5[ which(data5$processes == 1 ), ]
data52 <- data5[ which(data5$processes == 2 ), ]
data54 <- data5[ which(data5$processes == 4 ), ]


plot(data51[, 1], data51[, 4], col='red', type = "l", main="Time to compute N queens problem", xlab="N", ylab="Time (seconds)")
lines(data52[, 1], data52[, 4], col='blue')
lines(data54[, 1], data54[, 4], col='green')
legend(7, 95, legend=c("1 cores", "2 cores", "4 cores"),
       col=c("red", "blue", "green"), lty=1:1, cex=1)

data14 <- data[ which(data$n == 13 ), ]
data14 <- data14[ which(data14$depth > 0 ), ]
data141 <- data14[ which(data14$processes == 1 ), ]
data142 <- data14[ which(data14$processes == 2 ), ]

plot(data141[, 2], data141[, 4], col='red', type = "l", main="Time to compute 14 Queens problem", xlab="Depth", ylab="Time (seconds)")
lines(data142[, 2], data142[, 4], col='blue')
legend(2, 95, legend=c("1 cores", "2 cores"),
       col=c("red", "blue"), lty=1:1, cex=1)

data1 <- data[ which(data$processes == 2 ), ]
data1 <- data1[ which(data1$n > 6 ), ]
data10 <- data1[ which(data1$depth == 0 ), ]
data11 <- data1[ which(data1$depth == 1 ), ]
data12 <- data1[ which(data1$depth == 2 ), ]

plot(data10[, 1], data10[, 4], col='red', type = "l", main="Time to compute 14 Queens problem", xlab="N", ylab="Time (seconds)")
lines(data11[, 1], data11[, 4], col='blue')
lines(data12[, 1], data12[, 4], col='green')
legend(4, 95, legend=c("Depth 0", "Depth 1"),
       col=c("red", "blue"), lty=1:1, cex=1)

data <- read.table(file="newtestResultsHPC.txt", sep=" ", header=FALSE)
colnames(data) <- c("n","depth","processes","real","user")

