data <- read.table(file="testResults.txt", sep=" ", header=FALSE)
colnames(data) <- c("pass","n","depth","processes","real","user","sys")
data
data12 <- data[ which(data$n == 12 & data$pass == 0), ]
data12_1 <- data[ which(data$processes == 1 ), ]
data12_2 <- data[ which(data$processes == 2 ), ]
data12_3 <- data[ which(data$processes == 4 ), ]

plot(data[, 6], main = "Correlation plot")

plot(data12_2[,2], data12_1[,6])
lines(data[,3], col = 'red')
lines(data[,4], col = 'green')
lines(data[,6], col = 'blue')

