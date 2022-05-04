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

data1 <- data[ which(data$processes == 1 ), ]
data2 <- data[ which(data$processes == 2 ), ]
data4 <- data[ which(data$processes == 4 ), ]
data8 <- data[ which(data$processes == 8 ), ]
data16 <- data[ which(data$processes == 16 ), ]
data24 <- data[ which(data$processes == 24), ]
data32 <- data[ which(data$processes == 32 ), ]
data40 <- data[ which(data$processes == 40 ), ]
data48 <- data[ which(data$processes == 48 ), ]
data56 <- data[ which(data$processes == 56 ), ]
data64 <- data[ which(data$processes == 64 ), ]

plot(data1[, 1], data1[, 4], col='red', type = "l", main="Time to compute N queens problem on a HPC", xlab="N", ylab="Time (seconds)")
lines(data2[, 1], data2[, 4], col='blue')
lines(data4[, 1], data4[, 4], col='green')
legend(10, 1000, legend=c("1 cores", "2 cores", "4 cores"),
       col=c("red", "blue", "green"), lty=1:1, cex=1)

plot(data1[, 1], data1[, 4], col='red', type = "l", main="Time to compute N Queens problem", xlab="N", ylab="Time (seconds)")
lines(data2[, 1], data2[, 4], col='blue')
lines(data4[, 1], data4[, 4], col='green')
legend(4, 95, legend=c("Depth 0", "Depth 1"),
       col=c("red", "blue"), lty=1:1, cex=1)

data16 <- data[ which(data$n == 16 ), ]
data16 <- data16[order(data16$processes),] 

data15 <- data[ which(data$n == 15 ), ]
data15 <- data15[order(data15$processes),] 

plot(data16[, 3], data16[, 4], col='red', type = "l", main="Time to compute 16-Queens problem", xlab="Number of Processors", ylab="Time (seconds)")


data2 <- read.table(file="newtestResultsBitHPC.txt", sep=" ", header=FALSE)
colnames(data2) <- c("n","depth","processes","real","user")

data <- read.table(file="newtestResultsHPC.txt", sep=" ", header=FALSE)
colnames(data) <- c("n","depth","processes","real","user")

data16 <- data2[ which(data2$n == 16 ), ]
data16 <- data16[order(data16$processes),] 

data162 <- data[ which(data$n == 16 ), ]
data162 <- data162[order(data162$processes),] 

data16
plot(data162[, 3], data162[, 4], col='red', type = "l", main="Time to compute 16-Queens problem", xlab="Number of Processors", ylab="Time (seconds)")
lines(data16[, 3], data16[, 4], col='blue')

data16 <- data2[ which(data2$processes == 32 ), ]
data16 <- data16[order(data16$processes),] 

data162 <- data[ which(data$processes == 32 ), ]
data162 <- data162[order(data162$processes),] 
data16
data162


databit1 <- data2[ which(data2$processes == 1 ), ]
databit1 <- databit1[order(databit1$processes),] 
databit1

